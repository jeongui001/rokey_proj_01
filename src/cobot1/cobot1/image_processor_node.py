from __future__ import annotations

import threading

import rclpy
from cv_bridge import CvBridge
from rclpy.callback_groups import ReentrantCallbackGroup
from rclpy.executors import MultiThreadedExecutor
from rclpy.node import Node
from sensor_msgs.msg import Image

from cobot1.vision_core.config import load_vision_config
from cobot1.vision_core.grid_projection import project_instances_to_grid
from cobot1.vision_core.mosaic import fit_image, render_cells
from cobot1.vision_core.overlay import draw_instance_overlay
from cobot1.vision_core.palette import Palette
from cobot1.vision_core.segmentation import create_segmenter
from cobot1_interfaces.srv import ProcessMosaic


class ImageProcessorNode(Node):
    """Segment an input image, make an N x N block model and calculate robot targets."""

    def __init__(self) -> None:
        super().__init__('image_processor')
        self._callback_group = ReentrantCallbackGroup()
        self._bridge = CvBridge()
        self._segmenter_lock = threading.Lock()

        self.declare_parameter('vision_config_file', '')
        self.declare_parameter('service_name', '/image/analyze')
        self.declare_parameter('fitted_topic', '/vision/source/fitted')
        self.declare_parameter('segmentation_overlay_topic', '/vision/source/segmentation_overlay')
        self.declare_parameter('mosaic_topic', '/vision/mosaic')
        self.declare_parameter('segmentation_backend_override', '')
        self.declare_parameter('segmentation_model_path_override', '')
        self.declare_parameter('segmentation_device_override', '')
        self.declare_parameter('warmup_segmenter', False)
        self.declare_parameter('grid_size', 16)

        config_file = str(self.get_parameter('vision_config_file').value)
        if not config_file:
            raise RuntimeError('Parameter vision_config_file must point to vision.yaml.')
        self._config = load_vision_config(config_file)
        self._palette = Palette.from_config(self._config)
        self._projection_config = dict(self._config.get('grid_projection', {}))

        segmenter_overrides = {
            'backend': str(self.get_parameter('segmentation_backend_override').value).strip(),
            'model_path': str(self.get_parameter('segmentation_model_path_override').value).strip(),
            'device': str(self.get_parameter('segmentation_device_override').value).strip(),
        }
        self._segmenter = create_segmenter(
            self._config, 'image_processor', segmenter_overrides
        )
        if bool(self.get_parameter('warmup_segmenter').value):
            self.get_logger().info('Warming up image-processor segmenter...')
            with self._segmenter_lock:
                self._segmenter.warmup()

        self._fitted_publisher = self.create_publisher(
            Image, str(self.get_parameter('fitted_topic').value), 1
        )
        self._segmentation_publisher = self.create_publisher(
            Image, str(self.get_parameter('segmentation_overlay_topic').value), 1
        )
        self._mosaic_publisher = self.create_publisher(
            Image, str(self.get_parameter('mosaic_topic').value), 1
        )
        self._service = self.create_service(
            ProcessMosaic,
            str(self.get_parameter('service_name').value),
            self._process_request,
            callback_group=self._callback_group,
        )

        self.get_logger().info(
            f'ImageProcessor ready: backend={self._segmenter.backend_name}, '
            f'model={self._segmenter.model_name}, service={self.get_parameter("service_name").value}'
        )

    def _process_request(
        self,
        request: ProcessMosaic.Request,
        response: ProcessMosaic.Response,
    ) -> ProcessMosaic.Response:
        try:
            source = self._bridge.imgmsg_to_cv2(request.input_image, desired_encoding='bgr8')
            grid_size = int(self.get_parameter('grid_size').value)
            mosaic_config = self._config.get('mosaic', {})
            max_grid_size = int(mosaic_config.get('max_grid_size', 64))
            if not 1 <= grid_size <= max_grid_size:
                raise ValueError(f'grid_size must be in [1, {max_grid_size}].')

            output_width = int(mosaic_config.get('default_output_width', 512))
            output_height = int(mosaic_config.get('default_output_height', 512))
            empty_rgb = self._palette.empty_entry(
                str(self._projection_config.get('empty_palette_name', 'empty'))
            ).rgb
            letterbox_bgr = (empty_rgb[2], empty_rgb[1], empty_rgb[0])
            fitted = fit_image(
                source,
                str(mosaic_config.get('fit_mode', 'center_crop')),
                letterbox_bgr=letterbox_bgr,
            )
            with self._segmenter_lock:
                segmentation = self._segmenter.infer(fitted)
            projected = project_instances_to_grid(
                fitted,
                segmentation,
                grid_size,
                self._palette,
                self._projection_config,
            )
            mosaic = render_cells(
                projected.cells,
                grid_size,
                output_width,
                output_height,
                draw_grid=bool(mosaic_config.get('draw_grid', True)),
                grid_thickness=int(mosaic_config.get('grid_line_thickness', 1)),
            )
            segmentation_overlay = draw_instance_overlay(
                fitted,
                projected.segmentation,
                alpha=float(self._projection_config.get('overlay_alpha', 0.42)),
                draw_grid_size=grid_size,
            )

            fitted_message = self._bridge.cv2_to_imgmsg(fitted, encoding='bgr8')
            fitted_message.header = request.input_image.header
            segmentation_message = self._bridge.cv2_to_imgmsg(
                segmentation_overlay, encoding='bgr8'
            )
            segmentation_message.header = request.input_image.header
            mosaic_message = self._bridge.cv2_to_imgmsg(mosaic, encoding='bgr8')
            mosaic_message.header = request.input_image.header

            response.success = True
            response.message = (
                f'Segmented {len(projected.segmentation.instances)} instances and generated '
                f'{grid_size}x{grid_size} grid with '
                f'{sum(1 for cell in projected.cells if cell.occupied)} occupied cells.'
            )
            response.colors = [cell.color for cell in projected.cells]

            self._fitted_publisher.publish(fitted_message)
            self._segmentation_publisher.publish(segmentation_message)
            self._mosaic_publisher.publish(mosaic_message)
            return response

        except Exception as exc:
            response.success = False
            response.message = str(exc)
        self.get_logger().error(response.message)
        return response


def main(args=None) -> None:
    rclpy.init(args=args)
    node = ImageProcessorNode()
    executor = MultiThreadedExecutor(num_threads=3)
    executor.add_node(node)
    try:
        executor.spin()
    except KeyboardInterrupt:
        pass
    finally:
        executor.shutdown()
        node.destroy_node()
        rclpy.shutdown()


if __name__ == '__main__':
    main()

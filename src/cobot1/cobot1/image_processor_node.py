from __future__ import annotations

import cv2
import rclpy
from cv_bridge import CvBridge
from rclpy.callback_groups import ReentrantCallbackGroup
from rclpy.executors import MultiThreadedExecutor
from rclpy.node import Node
from sensor_msgs.msg import Image

from cobot1.vision_core.config import load_vision_config
from cobot1.vision_core.grid_projection import merge_blocks, quantize_image_to_grid
from cobot1.vision_core.mosaic import (
    DEFAULT_CELL_ASPECT_HEIGHT,
    DEFAULT_CELL_ASPECT_WIDTH,
    DEFAULT_GRID_COLS,
    DEFAULT_GRID_ROWS,
    fit_image,
    preview_size_for_cell_aspect,
    render_cells,
)
from cobot1.vision_core.overlay import draw_grid_overlay
from cobot1.vision_core.palette import Palette
from cobot1_interfaces.srv import ProcessMosaic


class ImageProcessorNode(Node):
    """Quantize an input image and return a fixed 10 x 10 colour grid."""

    def __init__(self) -> None:
        super().__init__('image_processor')
        self._callback_group = ReentrantCallbackGroup()
        self._bridge = CvBridge()

        self.declare_parameter('vision_config_file', '')
        self.declare_parameter('service_name', '/image/analyze')
        self.declare_parameter('fitted_topic', '/vision/source/fitted')
        self.declare_parameter('overlay_topic', '/vision/source/overlay')
        self.declare_parameter('mosaic_topic', '/vision/mosaic')
        self.declare_parameter('grid_rows', DEFAULT_GRID_ROWS)
        self.declare_parameter('grid_cols', DEFAULT_GRID_COLS)
        self.declare_parameter('cell_aspect_width', DEFAULT_CELL_ASPECT_WIDTH)
        self.declare_parameter('cell_aspect_height', DEFAULT_CELL_ASPECT_HEIGHT)

        config_file = str(self.get_parameter('vision_config_file').value)
        if not config_file:
            raise RuntimeError('Parameter vision_config_file must point to vision.yaml.')
        self._config = load_vision_config(config_file)
        self._palette = Palette.from_config(self._config)
        self._projection_config = dict(self._config.get('grid_projection', {}))

        self._fitted_publisher = self.create_publisher(
            Image, str(self.get_parameter('fitted_topic').value), 1
        )
        self._overlay_publisher = self.create_publisher(
            Image, str(self.get_parameter('overlay_topic').value), 1
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
            'ImageProcessor ready: backend=palette_quantization, '
            f'grid={self.get_parameter("grid_cols").value}x{self.get_parameter("grid_rows").value}, '
            f'service={self.get_parameter("service_name").value}'
        )

    def _grid_settings(self) -> tuple[int, int, float, float]:
        grid_rows = int(self.get_parameter('grid_rows').value)
        grid_cols = int(self.get_parameter('grid_cols').value)
        cell_aspect_width = float(self.get_parameter('cell_aspect_width').value)
        cell_aspect_height = float(self.get_parameter('cell_aspect_height').value)
        if grid_rows < 1 or grid_cols < 1:
            raise ValueError('grid_rows and grid_cols must be at least 1.')
        if cell_aspect_width <= 0.0 or cell_aspect_height <= 0.0:
            raise ValueError('cell_aspect_width and cell_aspect_height must be positive.')
        return grid_rows, grid_cols, cell_aspect_width, cell_aspect_height

    def _process_request(
        self,
        request: ProcessMosaic.Request,
        response: ProcessMosaic.Response,
    ) -> ProcessMosaic.Response:
        try:
            source = self._bridge.imgmsg_to_cv2(request.input_image, desired_encoding='bgr8')
            grid_rows, grid_cols, cell_aspect_width, cell_aspect_height = self._grid_settings()
            mosaic_config = self._config.get('mosaic', {})
            max_grid_size = int(mosaic_config.get('max_grid_size', 64))
            if max(grid_rows, grid_cols) > max_grid_size:
                raise ValueError(
                    f'grid size must not exceed mosaic.max_grid_size={max_grid_size}.'
                )

            output_width, output_height = preview_size_for_cell_aspect(
                grid_rows,
                grid_cols,
                cell_aspect_width,
                cell_aspect_height,
                int(mosaic_config.get('default_output_height', 512)),
            )
            empty_rgb = self._palette.empty_entry(
                str(self._projection_config.get('empty_palette_name', 'empty'))
            ).rgb
            letterbox_bgr = (empty_rgb[2], empty_rgb[1], empty_rgb[0])
            fitted = fit_image(
                source,
                str(mosaic_config.get('fit_mode', 'center_crop')),
                letterbox_bgr=letterbox_bgr,
            )
            grid, cells = quantize_image_to_grid(
                fitted,
                self._palette,
                grid_rows,
                grid_cols=grid_cols,
                config=self._projection_config,
            )
            blocks = merge_blocks(grid)
            mosaic = render_cells(
                cells,
                grid_rows,
                output_width,
                output_height,
                grid_cols=grid_cols,
                draw_grid=bool(mosaic_config.get('draw_grid', True)),
                grid_thickness=int(mosaic_config.get('grid_line_thickness', 1)),
                blocks=blocks,
            )
            palette_overlay = cv2.resize(
                fitted,
                (output_width, output_height),
                interpolation=cv2.INTER_LINEAR,
            )
            palette_overlay = draw_grid_overlay(
                palette_overlay,
                cells,
                blocks,
                grid_rows,
                grid_cols,
                alpha=float(self._projection_config.get('overlay_alpha', 0.42)),
            )

            fitted_message = self._bridge.cv2_to_imgmsg(fitted, encoding='bgr8')
            fitted_message.header = request.input_image.header
            overlay_message = self._bridge.cv2_to_imgmsg(
                palette_overlay, encoding='bgr8'
            )
            overlay_message.header = request.input_image.header
            mosaic_message = self._bridge.cv2_to_imgmsg(mosaic, encoding='bgr8')
            mosaic_message.header = request.input_image.header

            response.success = True
            response.message = (
                f'Palette-quantized {grid_cols}x{grid_rows} grid with '
                f'{sum(1 for cell in cells if cell.occupied)} occupied cells and '
                f'{len(blocks)} merged block candidates; '
                f'cell aspect={cell_aspect_width:g}:{cell_aspect_height:g}.'
            )
            response.colors = [cell.color if cell.occupied else '' for cell in cells]

            self._fitted_publisher.publish(fitted_message)
            self._overlay_publisher.publish(overlay_message)
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

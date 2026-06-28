from __future__ import annotations

import os

import cv2
import rclpy
from ament_index_python.packages import get_package_share_directory
from cv_bridge import CvBridge
from rclpy.callback_groups import ReentrantCallbackGroup
from rclpy.executors import MultiThreadedExecutor
from rclpy.node import Node
from sensor_msgs.msg import Image

from cobot1.vision_core.config import load_vision_config
from cobot1.vision_core.grid_projection import merge_blocks, quantize_image_to_grid
from cobot1.vision_core.mosaic import fit_image, preview_size_for_cell_aspect, render_cells
from cobot1.vision_core.overlay import draw_grid_overlay
from cobot1_interfaces.srv import ProcessMosaic

SERVICE_NAME = '/image/analyze'
FITTED_TOPIC = '/vision/source/fitted'
OVERLAY_TOPIC = '/vision/source/overlay'
MOSAIC_TOPIC = '/vision/mosaic'
DEFAULT_GRID_ROWS = 8
DEFAULT_GRID_COLS = 16
CELL_ASPECT_WIDTH = 15.9
CELL_ASPECT_HEIGHT = 19.0


class ImageProcessorNode(Node):
    """Quantize an input image into a front-view brick grid."""

    def __init__(self) -> None:
        super().__init__('image_processor')
        self._callback_group = ReentrantCallbackGroup()
        self._bridge = CvBridge()

        config_file = os.path.join(
            get_package_share_directory('cobot1'), 'config', 'vision.yaml')
        self._config = load_vision_config(config_file)
        self._projection_config = dict(self._config.get('grid_projection', {}))
        self._block_palette: dict[str, tuple[int, int, int]] = {}
        self._empty_rgb: tuple[int, int, int] | None = None
        for item in self._config.get('palette', {}).get('entries', []):
            name = str(item['name'])
            rgb = tuple(int(value) for value in item['rgb'])
            if bool(item.get('occupied', True)):
                self._block_palette[name] = rgb
            elif self._empty_rgb is None or name == 'empty':
                self._empty_rgb = rgb
        if self._empty_rgb is None:
            raise ValueError('palette.entries requires an occupied=false entry.')

        self._fitted_publisher = self.create_publisher(Image, FITTED_TOPIC, 1)
        self._overlay_publisher = self.create_publisher(Image, OVERLAY_TOPIC, 1)
        self._mosaic_publisher = self.create_publisher(Image, MOSAIC_TOPIC, 1)
        self._service = self.create_service(
            ProcessMosaic,
            SERVICE_NAME,
            self._process_request,
            callback_group=self._callback_group,
        )

        self.get_logger().info(f'ImageProcessor ready: service={SERVICE_NAME}')

    def _process_request(
        self,
        request: ProcessMosaic.Request,
        response: ProcessMosaic.Response,
    ) -> ProcessMosaic.Response:
        try:
            source = self._bridge.imgmsg_to_cv2(request.input_image, desired_encoding='bgr8')
            grid_rows = int(request.grid_rows) if request.grid_rows > 0 else DEFAULT_GRID_ROWS
            grid_cols = int(request.grid_cols) if request.grid_cols > 0 else DEFAULT_GRID_COLS
            cell_aspect_width = CELL_ASPECT_WIDTH
            cell_aspect_height = CELL_ASPECT_HEIGHT
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
            target_aspect = (grid_cols * cell_aspect_width) / (
                grid_rows * cell_aspect_height
            )
            fit_mode = str(request.fit_mode_override).strip() or str(mosaic_config.get('fit_mode', 'center_crop'))
            fitted = fit_image(
                source,
                fit_mode,
                target_aspect=target_aspect,
                smart_crop_min_scale=float(
                    mosaic_config.get('smart_crop_min_scale', 0.80)
                ),
            )
            grid, cells = quantize_image_to_grid(
                fitted,
                self._block_palette,
                self._empty_rgb,
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
                f'Color-mask quantized {grid_cols}x{grid_rows} grid with '
                f'{sum(1 for cell in cells if cell.occupied)} occupied cells and '
                f'{len(blocks)} merged block candidates.'
            )
            response.colors = [cell.color if cell.occupied else 'empty' for cell in cells]

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

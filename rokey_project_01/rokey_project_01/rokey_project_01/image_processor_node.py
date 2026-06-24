from __future__ import annotations

import math
import threading
import uuid

import numpy as np
import rclpy
from cv_bridge import CvBridge
from geometry_msgs.msg import Point32
from rclpy.callback_groups import ReentrantCallbackGroup
from rclpy.duration import Duration
from rclpy.executors import MultiThreadedExecutor
from rclpy.node import Node
from rclpy.qos import DurabilityPolicy, QoSProfile, ReliabilityPolicy, qos_profile_sensor_data
from rclpy.time import Time
from sensor_msgs.msg import CameraInfo, Image
from tf2_ros import Buffer, TransformException, TransformListener

from rokey_project_01.vision_core.config import load_vision_config, roi_normalized
from rokey_project_01.vision_core.geometry import grid_centers_in_roi, pixel_to_base_on_axis_plane, transform_matrix
from rokey_project_01.vision_core.grid_projection import project_instances_to_grid
from rokey_project_01.vision_core.mosaic import fit_image, render_cells
from rokey_project_01.vision_core.overlay import draw_instance_overlay
from rokey_project_01.vision_core.palette import Palette
from rokey_project_01.vision_core.segmentation import create_segmenter, largest_contour_points
from rokey_project_01_interfaces.msg import BlockCell, BlockModel, SegmentationInstance
from rokey_project_01_interfaces.srv import ProcessMosaic


class ImageProcessorNode(Node):
    """Segment an input image, make an N x N block model and calculate robot targets."""

    def __init__(self) -> None:
        super().__init__('image_processor')
        self._callback_group = ReentrantCallbackGroup()
        self._bridge = CvBridge()
        self._camera_info_lock = threading.Lock()
        self._camera_info: CameraInfo | None = None
        self._segmenter_lock = threading.Lock()

        self.declare_parameter('vision_config_file', '')
        self.declare_parameter('camera_info_topic', '/front_camera/camera_info')
        self.declare_parameter('service_name', '/image/analyze')
        self.declare_parameter('fitted_topic', '/vision/source/fitted')
        self.declare_parameter('segmentation_overlay_topic', '/vision/source/segmentation_overlay')
        self.declare_parameter('mosaic_topic', '/vision/mosaic')
        self.declare_parameter('expected_model_topic', '/vision/expected_model')
        self.declare_parameter('base_frame_override', '')
        self.declare_parameter('camera_frame_override', '')
        self.declare_parameter('calibration_ready', False)
        self.declare_parameter('tf_timeout_sec', 1.0)
        self.declare_parameter('segmentation_backend_override', '')
        self.declare_parameter('segmentation_model_path_override', '')
        self.declare_parameter('segmentation_device_override', '')
        self.declare_parameter('warmup_segmenter', False)

        config_file = str(self.get_parameter('vision_config_file').value)
        if not config_file:
            raise RuntimeError('Parameter vision_config_file must point to vision.yaml.')
        self._config = load_vision_config(config_file)
        self._palette = Palette.from_config(self._config)
        self._roi = roi_normalized(self._config)
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

        workspace_config = self._config.get('workspace', {})
        self._base_frame = str(self.get_parameter('base_frame_override').value).strip() or str(
            workspace_config.get('base_frame', 'base_link')
        )
        self._camera_frame_override = str(
            self.get_parameter('camera_frame_override').value
        ).strip() or str(workspace_config.get('camera_frame', '')).strip()
        self._rectify_pixels = bool(workspace_config.get('rectify_image', True))
        self._target_offset = np.asarray(
            workspace_config.get('target_offset_xyz', [0.0, 0.0, 0.0]), dtype=np.float64
        )
        if self._target_offset.shape != (3,):
            raise ValueError('workspace.target_offset_xyz must contain three values.')

        self._tf_buffer = Buffer()
        self._tf_listener = TransformListener(self._tf_buffer, self)

        camera_info_topic = str(self.get_parameter('camera_info_topic').value)
        self.create_subscription(
            CameraInfo,
            camera_info_topic,
            self._camera_info_callback,
            qos_profile_sensor_data,
            callback_group=self._callback_group,
        )

        model_qos = QoSProfile(depth=1)
        model_qos.reliability = ReliabilityPolicy.RELIABLE
        model_qos.durability = DurabilityPolicy.TRANSIENT_LOCAL
        self._model_publisher = self.create_publisher(
            BlockModel,
            str(self.get_parameter('expected_model_topic').value),
            model_qos,
        )
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

    def _camera_info_callback(self, message: CameraInfo) -> None:
        with self._camera_info_lock:
            self._camera_info = message

    def _copy_camera_info(self) -> CameraInfo | None:
        with self._camera_info_lock:
            return self._camera_info

    def _lookup_base_from_camera(self, camera_frame: str) -> np.ndarray:
        timeout = float(self.get_parameter('tf_timeout_sec').value)
        transform = self._tf_buffer.lookup_transform(
            self._base_frame,
            camera_frame,
            Time(),
            timeout=Duration(seconds=timeout),
        )
        translation = transform.transform.translation
        rotation = transform.transform.rotation
        return transform_matrix(
            [translation.x, translation.y, translation.z],
            [rotation.x, rotation.y, rotation.z, rotation.w],
        )

    @staticmethod
    def _empty_target(cell: BlockCell) -> None:
        cell.target.header.frame_id = ''
        cell.target.point.x = math.nan
        cell.target.point.y = math.nan
        cell.target.point.z = math.nan

    @staticmethod
    def _fill_rgba(target, rgb: tuple[int, int, int]) -> None:
        target.r = rgb[0] / 255.0
        target.g = rgb[1] / 255.0
        target.b = rgb[2] / 255.0
        target.a = 1.0

    def _instance_message(self, instance) -> SegmentationInstance:
        message = SegmentationInstance()
        message.instance_id = int(instance.instance_id)
        message.class_id = int(instance.class_id)
        message.class_name = instance.class_name
        message.confidence = float(instance.score)
        x0, y0, x1, y1 = instance.bbox_xyxy
        ix0 = max(0, int(math.floor(x0)))
        iy0 = max(0, int(math.floor(y0)))
        ix1 = max(ix0, int(math.ceil(x1)))
        iy1 = max(iy0, int(math.ceil(y1)))
        message.roi.x_offset = ix0
        message.roi.y_offset = iy0
        message.roi.width = ix1 - ix0
        message.roi.height = iy1 - iy0
        message.roi.do_rectify = False
        message.centroid.x = float(instance.centroid_uv[0])
        message.centroid.y = float(instance.centroid_uv[1])
        message.centroid.z = 0.0
        message.mask_area = int(instance.area)
        max_points = int(self._projection_config.get('contour_max_points', 64))
        for x, y in largest_contour_points(instance.mask, max_points=max_points):
            point = Point32()
            point.x = x
            point.y = y
            point.z = 0.0
            message.contour.points.append(point)
        message.color = instance.color
        self._fill_rgba(message.rgba, instance.rgb)
        message.color_confidence = float(instance.color_confidence)
        return message

    def _cell_message(self, index: int, core_cell, stamp, camera_uv, point) -> BlockCell:
        cell = BlockCell()
        cell.index = index
        cell.row = core_cell.row
        cell.col = core_cell.col
        cell.color = core_cell.color
        self._fill_rgba(cell.rgba, core_cell.rgb)
        cell.occupied = core_cell.occupied
        cell.confidence = float(core_cell.confidence)
        cell.instance_id = int(core_cell.instance_id)
        cell.class_id = int(core_cell.class_id)
        cell.class_name = core_cell.class_name
        cell.instance_confidence = float(core_cell.instance_confidence)
        cell.mask_coverage = float(core_cell.mask_coverage)
        cell.overlapping_instances = int(core_cell.overlapping_instances)
        cell.source_u = float(core_cell.source_uv[0]) if core_cell.source_uv else math.nan
        cell.source_v = float(core_cell.source_uv[1]) if core_cell.source_uv else math.nan
        if core_cell.instance_centroid_uv is None:
            cell.instance_centroid_u = math.nan
            cell.instance_centroid_v = math.nan
            cell.centroid_offset_ratio = math.nan
        else:
            cell.instance_centroid_u = float(core_cell.instance_centroid_uv[0])
            cell.instance_centroid_v = float(core_cell.instance_centroid_uv[1])
            cell.centroid_offset_ratio = float(core_cell.centroid_offset_ratio)
        cell.camera_u = float(camera_uv[0])
        cell.camera_v = float(camera_uv[1])
        if point is None:
            self._empty_target(cell)
        else:
            cell.target.header.stamp = stamp
            cell.target.header.frame_id = self._base_frame
            cell.target.point.x = float(point[0])
            cell.target.point.y = float(point[1])
            cell.target.point.z = float(point[2])
        return cell

    def _process_request(
        self,
        request: ProcessMosaic.Request,
        response: ProcessMosaic.Response,
    ) -> ProcessMosaic.Response:
        try:
            source = self._bridge.imgmsg_to_cv2(request.input_image, desired_encoding='bgr8')
            grid_size = int(request.grid_size)
            mosaic_config = self._config.get('mosaic', {})
            max_grid_size = int(mosaic_config.get('max_grid_size', 64))
            if not 1 <= grid_size <= max_grid_size:
                raise ValueError(f'grid_size must be in [1, {max_grid_size}].')

            output_width = int(request.output_width) or int(
                mosaic_config.get('default_output_width', 512)
            )
            output_height = int(request.output_height) or int(
                mosaic_config.get('default_output_height', 512)
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

            workspace_config = self._config.get('workspace', {})
            if request.fixed_axis.strip():
                fixed_axis = request.fixed_axis.strip().lower()
                fixed_value = float(request.fixed_axis_value)
            else:
                fixed_axis = str(workspace_config.get('fixed_axis_default', 'x')).lower()
                fixed_value = float(workspace_config.get('fixed_axis_value_default', 0.0))
            if fixed_axis not in ('x', 'y'):
                raise ValueError('fixed_axis must be "x" or "y".')

            count = len(projected.cells)
            camera_centres = [(math.nan, math.nan)] * count
            base_points: list[np.ndarray | None] = [None] * count
            if request.compute_robot_coordinates:
                if not bool(self.get_parameter('calibration_ready').value):
                    raise RuntimeError(
                        'Robot coordinates are disabled because calibration_ready=false. '
                        'Calibrate intrinsics/extrinsics and relaunch with calibration_ready:=true.'
                    )
                camera_info = self._copy_camera_info()
                if camera_info is None:
                    raise RuntimeError('No CameraInfo has been received.')
                if camera_info.width == 0 or camera_info.height == 0 or camera_info.k[0] <= 0.0:
                    raise RuntimeError('CameraInfo is not calibrated.')
                camera_frame = self._camera_frame_override or camera_info.header.frame_id
                if not camera_frame:
                    raise RuntimeError('Camera frame is empty in both parameters and CameraInfo.')
                base_from_camera = self._lookup_base_from_camera(camera_frame)
                camera_centres = grid_centers_in_roi(
                    grid_size, self._roi, int(camera_info.width), int(camera_info.height)
                )
                distortion = None if self._rectify_pixels else camera_info.d
                for index, (u, v) in enumerate(camera_centres):
                    base_points[index] = (
                        pixel_to_base_on_axis_plane(
                            u,
                            v,
                            camera_info.k,
                            distortion,
                            base_from_camera,
                            fixed_axis,
                            fixed_value,
                        )
                        + self._target_offset
                    )

            stamp = self.get_clock().now().to_msg()
            model = BlockModel()
            model.header.stamp = stamp
            model.header.frame_id = self._base_frame if request.compute_robot_coordinates else ''
            model.model_id = str(uuid.uuid4())
            model.segmentation_backend = projected.segmentation.backend
            model.segmentation_model = projected.segmentation.model_name
            model.source_width = fitted.shape[1]
            model.source_height = fitted.shape[0]
            model.grid_size = grid_size
            model.output_width = output_width
            model.output_height = output_height
            model.fixed_axis = fixed_axis
            model.fixed_axis_value = fixed_value
            for instance in projected.segmentation.instances:
                model.instances.append(self._instance_message(instance))
            for index, core_cell in enumerate(projected.cells):
                model.cells.append(
                    self._cell_message(
                        index,
                        core_cell,
                        stamp,
                        camera_centres[index],
                        base_points[index],
                    )
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
                f'Segmented {len(model.instances)} instances and generated '
                f'{grid_size}x{grid_size} model with '
                f'{sum(1 for cell in model.cells if cell.occupied)} occupied cells.'
            )
            response.fitted_image = fitted_message
            response.segmentation_overlay = segmentation_message
            response.mosaic_image = mosaic_message
            response.model = model

            self._fitted_publisher.publish(fitted_message)
            self._segmentation_publisher.publish(segmentation_message)
            self._mosaic_publisher.publish(mosaic_message)
            self._model_publisher.publish(model)
            return response

        except TransformException as exc:
            response.success = False
            response.message = f'TF lookup failed: {exc}'
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

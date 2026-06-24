from __future__ import annotations

import copy
import math
import threading
import time
import uuid

import rclpy
from cv_bridge import CvBridge
from geometry_msgs.msg import Point32
from rclpy.callback_groups import ReentrantCallbackGroup
from rclpy.executors import MultiThreadedExecutor
from rclpy.node import Node
from rclpy.qos import DurabilityPolicy, QoSProfile, ReliabilityPolicy, qos_profile_sensor_data
from sensor_msgs.msg import CameraInfo, Image

from cobot1.vision_core.config import load_vision_config, roi_normalized
from cobot1.vision_core.geometry import grid_centers_in_roi
from cobot1.vision_core.grid_projection import project_instances_to_grid
from cobot1.vision_core.models import CellSample
from cobot1.vision_core.overlay import draw_instance_overlay, draw_workspace_overlay
from cobot1.vision_core.palette import Palette
from cobot1.vision_core.segmentation import create_segmenter, largest_contour_points
from cobot1.vision_core.verification import compare_cells, rectify_image, render_observed_mosaic, warp_workspace
from cobot1_interfaces.msg import BlockCell, BlockModel, Mismatch, SegmentationInstance
from cobot1_interfaces.srv import VerifyAssembly


_REASON_TO_MSG = {
    'MISSING': Mismatch.MISSING,
    'WRONG_COLOR': Mismatch.WRONG_COLOR,
    'EXTRA': Mismatch.EXTRA,
    'UNCERTAIN': Mismatch.UNCERTAIN,
    'MISALIGNED': Mismatch.MISALIGNED,
    'INSTANCE_CONFLICT': Mismatch.INSTANCE_CONFLICT,
}


class VerifyNode(Node):
    """Relay a rectified front-camera stream and verify assemblies with instance masks."""

    def __init__(self) -> None:
        super().__init__('verify')
        self._callback_group = ReentrantCallbackGroup()
        self._bridge = CvBridge()
        self._state_lock = threading.RLock()
        self._frame_condition = threading.Condition(self._state_lock)
        self._segmenter_lock = threading.Lock()
        self._camera_info: CameraInfo | None = None
        self._latest_frame = None
        self._latest_header = None
        self._latest_frame_rectified = False
        self._frame_sequence = 0
        self._expected_model: BlockModel | None = None
        self._last_live_publish = 0.0
        self._warned_missing_calibration = False

        self.declare_parameter('vision_config_file', '')
        self.declare_parameter('image_topic', '/front_camera/image_raw')
        self.declare_parameter('camera_info_topic', '/front_camera/camera_info')
        self.declare_parameter('expected_model_topic', '/vision/expected_model')
        self.declare_parameter('observed_model_topic', '/vision/observed_model')
        self.declare_parameter('service_name', '/verify/assembly')
        self.declare_parameter('rectified_topic', '/vision/camera/rectified')
        self.declare_parameter('rectified_camera_info_topic', '/vision/camera/camera_info')
        self.declare_parameter('live_overlay_topic', '/vision/verify/live_overlay')
        self.declare_parameter('workspace_topic', '/vision/verify/workspace')
        self.declare_parameter('segmentation_overlay_topic', '/vision/verify/segmentation_overlay')
        self.declare_parameter('live_segmentation_topic', '/vision/verify/live_segmentation')
        self.declare_parameter('verification_overlay_topic', '/vision/verify/overlay')
        self.declare_parameter('observed_mosaic_topic', '/vision/verify/observed_mosaic')
        self.declare_parameter('publish_rectified', True)
        self.declare_parameter('publish_live_overlay', True)
        self.declare_parameter('publish_live_segmentation', False)
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
        self._workspace_config = self._config.get('workspace', {})
        self._verification_config = self._config.get('verification', {})
        self._projection_config = dict(self._config.get('grid_projection', {}))
        self._rectify_enabled = bool(self._workspace_config.get('rectify_image', True))

        segmenter_overrides = {
            'backend': str(self.get_parameter('segmentation_backend_override').value).strip(),
            'model_path': str(self.get_parameter('segmentation_model_path_override').value).strip(),
            'device': str(self.get_parameter('segmentation_device_override').value).strip(),
        }
        self._segmenter = create_segmenter(self._config, 'verifier', segmenter_overrides)
        if bool(self.get_parameter('warmup_segmenter').value):
            self.get_logger().info('Warming up verifier segmenter...')
            with self._segmenter_lock:
                self._segmenter.warmup()

        model_qos = QoSProfile(depth=1)
        model_qos.reliability = ReliabilityPolicy.RELIABLE
        model_qos.durability = DurabilityPolicy.TRANSIENT_LOCAL

        self.create_subscription(
            Image,
            str(self.get_parameter('image_topic').value),
            self._image_callback,
            qos_profile_sensor_data,
            callback_group=self._callback_group,
        )
        self.create_subscription(
            CameraInfo,
            str(self.get_parameter('camera_info_topic').value),
            self._camera_info_callback,
            qos_profile_sensor_data,
            callback_group=self._callback_group,
        )
        self.create_subscription(
            BlockModel,
            str(self.get_parameter('expected_model_topic').value),
            self._expected_model_callback,
            model_qos,
            callback_group=self._callback_group,
        )

        self._rectified_publisher = self.create_publisher(
            Image, str(self.get_parameter('rectified_topic').value), 1
        )
        self._rectified_camera_info_publisher = self.create_publisher(
            CameraInfo, str(self.get_parameter('rectified_camera_info_topic').value), 1
        )
        self._live_overlay_publisher = self.create_publisher(
            Image, str(self.get_parameter('live_overlay_topic').value), 1
        )
        self._workspace_publisher = self.create_publisher(
            Image, str(self.get_parameter('workspace_topic').value), 1
        )
        self._segmentation_publisher = self.create_publisher(
            Image, str(self.get_parameter('segmentation_overlay_topic').value), 1
        )
        self._live_segmentation_publisher = self.create_publisher(
            Image, str(self.get_parameter('live_segmentation_topic').value), 1
        )
        self._verification_overlay_publisher = self.create_publisher(
            Image, str(self.get_parameter('verification_overlay_topic').value), 1
        )
        self._observed_mosaic_publisher = self.create_publisher(
            Image, str(self.get_parameter('observed_mosaic_topic').value), 1
        )
        self._observed_model_publisher = self.create_publisher(
            BlockModel, str(self.get_parameter('observed_model_topic').value), model_qos
        )

        self._service = self.create_service(
            VerifyAssembly,
            str(self.get_parameter('service_name').value),
            self._verify_request,
            callback_group=self._callback_group,
        )

        if bool(self.get_parameter('publish_live_segmentation').value):
            rate = float(self._verification_config.get('live_segmentation_rate_hz', 1.0))
            if rate > 0.0:
                self._live_segmentation_timer = self.create_timer(
                    1.0 / rate,
                    self._live_segmentation_tick,
                    callback_group=self._callback_group,
                )

        self.get_logger().info(
            f'VerifyNode ready: backend={self._segmenter.backend_name}, '
            f'model={self._segmenter.model_name}, image={self.get_parameter("image_topic").value}'
        )

    def _camera_info_callback(self, message: CameraInfo) -> None:
        with self._state_lock:
            self._camera_info = message

    def _expected_model_callback(self, message: BlockModel) -> None:
        with self._state_lock:
            self._expected_model = message
        self.get_logger().info(
            f'Cached expected model {message.model_id} ({message.grid_size}x{message.grid_size}).'
        )

    def _image_callback(self, message: Image) -> None:
        try:
            frame = self._bridge.imgmsg_to_cv2(message, desired_encoding='bgr8')
            with self._state_lock:
                camera_info = copy.deepcopy(self._camera_info)
                expected_model = copy.deepcopy(self._expected_model)

            rectified = False
            processed = frame
            if self._rectify_enabled:
                if camera_info is not None and camera_info.k[0] > 0.0:
                    processed = rectify_image(frame, camera_info.k, camera_info.d)
                    rectified = True
                    self._warned_missing_calibration = False
                elif not self._warned_missing_calibration:
                    self.get_logger().warning(
                        'rectify_image=true but calibrated CameraInfo is unavailable; '
                        'verification requests are rejected until calibration is available.'
                    )
                    self._warned_missing_calibration = True
            else:
                rectified = True

            with self._frame_condition:
                self._latest_frame = processed.copy()
                self._latest_header = copy.deepcopy(message.header)
                self._latest_frame_rectified = rectified
                self._frame_sequence += 1
                self._frame_condition.notify_all()

            if bool(self.get_parameter('publish_rectified').value) and rectified:
                rectified_message = self._bridge.cv2_to_imgmsg(processed, encoding='bgr8')
                rectified_message.header = message.header
                self._rectified_publisher.publish(rectified_message)
                if camera_info is not None:
                    rectified_info = copy.deepcopy(camera_info)
                    rectified_info.header = message.header
                    rectified_info.d = [0.0 for _ in rectified_info.d]
                    rectified_info.r = [1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0]
                    rectified_info.p = [
                        rectified_info.k[0], rectified_info.k[1], rectified_info.k[2], 0.0,
                        rectified_info.k[3], rectified_info.k[4], rectified_info.k[5], 0.0,
                        rectified_info.k[6], rectified_info.k[7], rectified_info.k[8], 0.0,
                    ]
                    self._rectified_camera_info_publisher.publish(rectified_info)

            if bool(self.get_parameter('publish_live_overlay').value):
                rate_hz = float(self._verification_config.get('live_overlay_rate_hz', 10.0))
                now = time.monotonic()
                if rate_hz <= 0.0 or now - self._last_live_publish >= 1.0 / rate_hz:
                    grid_size = (
                        int(expected_model.grid_size)
                        if expected_model is not None and expected_model.grid_size > 0
                        else int(self._verification_config.get('preview_grid_size', 8))
                    )
                    overlay = draw_workspace_overlay(processed, self._roi, grid_size)
                    overlay_message = self._bridge.cv2_to_imgmsg(overlay, encoding='bgr8')
                    overlay_message.header = message.header
                    self._live_overlay_publisher.publish(overlay_message)
                    self._last_live_publish = now
        except Exception as exc:
            self.get_logger().error(f'Camera image callback failed: {exc}')

    def _get_frame(self, wait_for_fresh: bool, timeout_sec: float):
        with self._frame_condition:
            starting_sequence = self._frame_sequence
            if wait_for_fresh:
                received = self._frame_condition.wait_for(
                    lambda: self._frame_sequence > starting_sequence,
                    timeout=timeout_sec,
                )
                if not received:
                    raise TimeoutError(
                        f'No fresh camera frame arrived within {timeout_sec:.2f} seconds.'
                    )
            if self._latest_frame is None:
                raise RuntimeError('No camera frame has been received.')
            return (
                self._latest_frame.copy(),
                copy.deepcopy(self._latest_header),
                bool(self._latest_frame_rectified),
            )

    def _live_segmentation_tick(self) -> None:
        if not self._segmenter_lock.acquire(blocking=False):
            return
        try:
            with self._state_lock:
                if self._latest_frame is None or not self._latest_frame_rectified:
                    return
                frame = self._latest_frame.copy()
                header = copy.deepcopy(self._latest_header)
                expected = copy.deepcopy(self._expected_model)
            grid_size = (
                int(expected.grid_size)
                if expected is not None and expected.grid_size > 0
                else int(self._verification_config.get('preview_grid_size', 8))
            )
            warp_size = self._warp_size(grid_size)
            workspace = warp_workspace(frame, self._roi, warp_size)
            segmentation = self._segmenter.infer(workspace)
            projected = project_instances_to_grid(
                workspace, segmentation, grid_size, self._palette, self._projection_config
            )
            overlay = draw_instance_overlay(
                workspace,
                projected.segmentation,
                alpha=float(self._projection_config.get('overlay_alpha', 0.42)),
                draw_grid_size=grid_size,
            )
            message = self._bridge.cv2_to_imgmsg(overlay, encoding='bgr8')
            message.header = header
            self._live_segmentation_publisher.publish(message)
        except Exception as exc:
            self.get_logger().warning(f'Live segmentation skipped: {exc}')
        finally:
            self._segmenter_lock.release()

    def _warp_size(self, grid_size: int) -> int:
        pixels_per_cell = int(self._verification_config.get('pixels_per_cell', 64))
        warp_size = max(grid_size, grid_size * pixels_per_cell)
        max_warp_size = int(self._verification_config.get('max_warp_size', 2048))
        if warp_size > max_warp_size:
            raise ValueError(
                f'Computed warp size {warp_size} exceeds max_warp_size={max_warp_size}.'
            )
        return warp_size

    @staticmethod
    def _fill_rgba(target, rgb: tuple[int, int, int]) -> None:
        target.r = rgb[0] / 255.0
        target.g = rgb[1] / 255.0
        target.b = rgb[2] / 255.0
        target.a = 1.0

    @staticmethod
    def _ros_cell_to_core(cell: BlockCell) -> CellSample:
        rgb = (
            int(round(max(0.0, min(1.0, cell.rgba.r)) * 255.0)),
            int(round(max(0.0, min(1.0, cell.rgba.g)) * 255.0)),
            int(round(max(0.0, min(1.0, cell.rgba.b)) * 255.0)),
        )
        centroid = None
        if math.isfinite(cell.instance_centroid_u) and math.isfinite(cell.instance_centroid_v):
            centroid = (float(cell.instance_centroid_u), float(cell.instance_centroid_v))
        source = None
        if math.isfinite(cell.source_u) and math.isfinite(cell.source_v):
            source = (float(cell.source_u), float(cell.source_v))
        camera = None
        if math.isfinite(cell.camera_u) and math.isfinite(cell.camera_v):
            camera = (float(cell.camera_u), float(cell.camera_v))
        return CellSample(
            row=int(cell.row),
            col=int(cell.col),
            color=cell.color,
            rgb=rgb,
            occupied=bool(cell.occupied),
            confidence=float(cell.confidence),
            instance_id=int(cell.instance_id),
            class_id=int(cell.class_id),
            class_name=cell.class_name,
            instance_confidence=float(cell.instance_confidence),
            mask_coverage=float(cell.mask_coverage),
            overlapping_instances=int(cell.overlapping_instances),
            source_uv=source,
            instance_centroid_uv=centroid,
            centroid_offset_ratio=float(cell.centroid_offset_ratio),
            camera_uv=camera,
        )

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
        message.centroid.x = float(instance.centroid_uv[0])
        message.centroid.y = float(instance.centroid_uv[1])
        message.mask_area = int(instance.area)
        max_points = int(self._projection_config.get('contour_max_points', 64))
        for x, y in largest_contour_points(instance.mask, max_points=max_points):
            point = Point32()
            point.x = x
            point.y = y
            message.contour.points.append(point)
        message.color = instance.color
        self._fill_rgba(message.rgba, instance.rgb)
        message.color_confidence = float(instance.color_confidence)
        return message

    def _observed_cell_message(self, index, core_cell, camera_uv, expected: BlockCell) -> BlockCell:
        observed = BlockCell()
        observed.index = index
        observed.row = core_cell.row
        observed.col = core_cell.col
        observed.color = core_cell.color
        self._fill_rgba(observed.rgba, core_cell.rgb)
        observed.occupied = core_cell.occupied
        observed.confidence = float(core_cell.confidence)
        observed.instance_id = int(core_cell.instance_id)
        observed.class_id = int(core_cell.class_id)
        observed.class_name = core_cell.class_name
        observed.instance_confidence = float(core_cell.instance_confidence)
        observed.mask_coverage = float(core_cell.mask_coverage)
        observed.overlapping_instances = int(core_cell.overlapping_instances)
        observed.source_u = float(core_cell.source_uv[0]) if core_cell.source_uv else math.nan
        observed.source_v = float(core_cell.source_uv[1]) if core_cell.source_uv else math.nan
        if core_cell.instance_centroid_uv is None:
            observed.instance_centroid_u = math.nan
            observed.instance_centroid_v = math.nan
            observed.centroid_offset_ratio = math.nan
        else:
            observed.instance_centroid_u = float(core_cell.instance_centroid_uv[0])
            observed.instance_centroid_v = float(core_cell.instance_centroid_uv[1])
            observed.centroid_offset_ratio = float(core_cell.centroid_offset_ratio)
        observed.camera_u = float(camera_uv[0])
        observed.camera_v = float(camera_uv[1])
        observed.target = copy.deepcopy(expected.target)
        return observed

    def _verify_request(
        self,
        request: VerifyAssembly.Request,
        response: VerifyAssembly.Response,
    ) -> VerifyAssembly.Response:
        try:
            with self._state_lock:
                cached_model = copy.deepcopy(self._expected_model)

            expected_model = request.expected_model if request.expected_model.cells else cached_model
            if expected_model is None or not expected_model.cells:
                raise RuntimeError(
                    'Expected model is empty. Call ProcessMosaic first or provide expected_model.'
                )
            grid_size = int(expected_model.grid_size)
            if grid_size < 1:
                raise ValueError('expected_model.grid_size must be positive.')
            if len(expected_model.cells) != grid_size * grid_size:
                raise ValueError(
                    f'Expected {grid_size * grid_size} cells, received {len(expected_model.cells)}.'
                )

            timeout_sec = float(request.timeout_sec)
            if timeout_sec <= 0.0:
                timeout_sec = float(self._verification_config.get('frame_timeout_sec', 2.0))
            frame, header, frame_is_rectified = self._get_frame(
                bool(request.wait_for_fresh_frame), timeout_sec
            )
            if self._rectify_enabled and not frame_is_rectified:
                raise RuntimeError(
                    'A calibrated CameraInfo message is required because rectify_image=true.'
                )

            warp_size = self._warp_size(grid_size)
            workspace = warp_workspace(frame, self._roi, warp_size)
            with self._segmenter_lock:
                segmentation = self._segmenter.infer(workspace)
            projected = project_instances_to_grid(
                workspace,
                segmentation,
                grid_size,
                self._palette,
                self._projection_config,
            )
            expected_core = [self._ros_cell_to_core(cell) for cell in expected_model.cells]
            comparison = compare_cells(
                expected_core,
                projected.cells,
                min_observation_confidence=float(
                    self._verification_config.get('min_observation_confidence', 0.45)
                ),
                min_expected_confidence=float(
                    self._verification_config.get('min_expected_confidence', 0.0)
                ),
                min_alignment_coverage=float(
                    self._verification_config.get('min_alignment_coverage', 0.18)
                ),
                max_centroid_offset_ratio=float(
                    self._verification_config.get('max_centroid_offset_ratio', 0.90)
                ),
                max_overlapping_instances=int(
                    self._verification_config.get('max_overlapping_instances', 1)
                ),
            )

            threshold = float(request.pass_threshold)
            if threshold <= 0.0:
                threshold = float(self._verification_config.get('pass_threshold', 95.0))
            if not 0.0 <= threshold <= 100.0:
                raise ValueError('pass_threshold must be in [0, 100].')
            passed = comparison.match_rate >= threshold

            camera_centres = grid_centers_in_roi(
                grid_size, self._roi, frame.shape[1], frame.shape[0]
            )
            expected_by_position = {
                (int(cell.row), int(cell.col)): cell for cell in expected_model.cells
            }

            observed_model = BlockModel()
            observed_model.header = header
            observed_model.model_id = str(uuid.uuid4())
            observed_model.segmentation_backend = projected.segmentation.backend
            observed_model.segmentation_model = projected.segmentation.model_name
            observed_model.source_width = workspace.shape[1]
            observed_model.source_height = workspace.shape[0]
            observed_model.grid_size = grid_size
            observed_model.output_width = warp_size
            observed_model.output_height = warp_size
            observed_model.fixed_axis = expected_model.fixed_axis
            observed_model.fixed_axis_value = expected_model.fixed_axis_value
            for instance in projected.segmentation.instances:
                observed_model.instances.append(self._instance_message(instance))

            observed_by_position: dict[tuple[int, int], BlockCell] = {}
            for index, core_cell in enumerate(projected.cells):
                expected = expected_by_position[(core_cell.row, core_cell.col)]
                observed = self._observed_cell_message(
                    index, core_cell, camera_centres[index], expected
                )
                observed_model.cells.append(observed)
                observed_by_position[(core_cell.row, core_cell.col)] = observed

            mismatch_map: dict[tuple[int, int], str] = {}
            for core_mismatch in comparison.mismatches:
                mismatch = Mismatch()
                mismatch.reason = _REASON_TO_MSG[core_mismatch.reason]
                mismatch.row = core_mismatch.row
                mismatch.col = core_mismatch.col
                mismatch.expected = copy.deepcopy(
                    expected_by_position[(core_mismatch.row, core_mismatch.col)]
                )
                mismatch.observed = copy.deepcopy(
                    observed_by_position[(core_mismatch.row, core_mismatch.col)]
                )
                mismatch.details = core_mismatch.details
                response.mismatches.append(mismatch)
                mismatch_map[(core_mismatch.row, core_mismatch.col)] = core_mismatch.reason

            pixels_per_cell = int(self._verification_config.get('pixels_per_cell', 64))
            observed_mosaic = render_observed_mosaic(
                projected.cells,
                grid_size,
                pixels_per_cell,
                grid_thickness=int(
                    self._config.get('mosaic', {}).get('grid_line_thickness', 1)
                ),
            )
            segmentation_overlay = draw_instance_overlay(
                workspace,
                projected.segmentation,
                alpha=float(self._projection_config.get('overlay_alpha', 0.42)),
                draw_grid_size=grid_size,
            )
            overlay = draw_workspace_overlay(
                frame,
                self._roi,
                grid_size,
                mismatches=mismatch_map,
                match_rate=comparison.match_rate,
                passed=passed,
            )

            workspace_message = self._bridge.cv2_to_imgmsg(workspace, encoding='bgr8')
            workspace_message.header = header
            segmentation_message = self._bridge.cv2_to_imgmsg(
                segmentation_overlay, encoding='bgr8'
            )
            segmentation_message.header = header
            observed_mosaic_message = self._bridge.cv2_to_imgmsg(
                observed_mosaic, encoding='bgr8'
            )
            observed_mosaic_message.header = header
            overlay_message = self._bridge.cv2_to_imgmsg(overlay, encoding='bgr8')
            overlay_message.header = header

            response.success = True
            response.passed = passed
            response.match_rate = float(comparison.match_rate)
            response.message = (
                f'{comparison.matched_cells}/{comparison.total_cells} cells matched; '
                f'{len(observed_model.instances)} instances detected; threshold={threshold:.1f}%.'
            )
            response.observed_model = observed_model
            response.workspace_image = workspace_message
            response.segmentation_overlay = segmentation_message
            response.observed_mosaic = observed_mosaic_message
            response.overlay_image = overlay_message

            self._workspace_publisher.publish(workspace_message)
            self._segmentation_publisher.publish(segmentation_message)
            self._observed_mosaic_publisher.publish(observed_mosaic_message)
            self._verification_overlay_publisher.publish(overlay_message)
            self._observed_model_publisher.publish(observed_model)
            return response
        except Exception as exc:
            response.success = False
            response.passed = False
            response.match_rate = 0.0
            response.message = str(exc)
            self.get_logger().error(response.message)
            return response


def main(args=None) -> None:
    rclpy.init(args=args)
    node = VerifyNode()
    executor = MultiThreadedExecutor(num_threads=4)
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

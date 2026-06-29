from __future__ import annotations

from dataclasses import dataclass
from itertools import product as iter_product
import math
import threading
import time
from pathlib import Path

import cv2
import numpy as np
import rclpy
from ament_index_python.packages import PackageNotFoundError, get_package_share_directory
from cv_bridge import CvBridge
from rclpy.callback_groups import ReentrantCallbackGroup
from rclpy.executors import MultiThreadedExecutor
from rclpy.node import Node
from rclpy.qos import (
    DurabilityPolicy,
    QoSProfile,
    ReliabilityPolicy,
    qos_profile_sensor_data,
)
from sensor_msgs.msg import Image

from cobot1.vision_core.config import load_vision_config
from cobot1.vision_core.grid_projection import quantize_image_to_grid
from cobot1.vision_core.mosaic import fit_image
from cobot1_interfaces.action._assembly import Assembly_FeedbackMessage
from cobot1_interfaces.msg import ExpectedModel, WebcamError


CELL_ASPECT_WIDTH = 15.9
CELL_ASPECT_HEIGHT = 19.0
DEFAULT_CONFIDENCE_THRESHOLD = 0.70
DEFAULT_MATCH_THRESHOLD = 0.80
DEFAULT_BEAM_WIDTH = 15


def _default_vision_config() -> str:
    try:
        return str(Path(get_package_share_directory('cobot1')) / 'config' / 'vision.yaml')
    except PackageNotFoundError:
        return str(Path(__file__).resolve().parent.parent / 'config' / 'vision.yaml')


@dataclass
class InspectionResult:
    PASS = 'PASS'
    FAIL = 'FAIL'
    UNCERTAIN = 'UNCERTAIN'
    CAMERA_ERROR = 'CAMERA_ERROR'
    ROI_ERROR = 'ROI_ERROR'

    step: int = 0
    row: int = 0
    col: int = 0
    expected_color: str = ''
    observed_color: str = ''
    confidence: float = 0.0
    match_rate: float = 0.0
    status: str = UNCERTAIN
    message: str = ''


class VerifyNode(Node):
    """카메라 프레임으로 조립 결과를 검증하고 디버그 오버레이를 발행한다."""

    def __init__(self):
        super().__init__('verify')

        self.declare_parameter('vision_config_file', _default_vision_config())
        self.declare_parameter('image_topic', '/front_camera/image_raw')
        self.declare_parameter('expected_model_topic', '/vision/expected_model')
        self.declare_parameter('assembly_feedback_topic', '/execute_queue/_action/feedback')
        self.declare_parameter('webcam_result_topic', '/webcam/error')
        self.declare_parameter('publish_webcam_result', False)
        self.declare_parameter('debug_image_topic', '/vision/debug_grid')
        self.declare_parameter('debug_overlay_interval_sec', 0.5)
        self.declare_parameter('default_grid_rows', 8)
        self.declare_parameter('default_grid_cols', 16)

        self._callback_group = ReentrantCallbackGroup()
        self._bridge = CvBridge()
        self._state_lock = threading.RLock()

        self._latest_frame = None
        self._last_debug_overlay_time = 0.0
        self._last_debug_error_time = 0.0
        self._expected_colors: list[str] = []
        self._expected_rows = 0
        self._expected_cols = 0
        self._block_spans: list[tuple[int, int, int, str]] = []
        self._inspected_steps: set[int] = set()
        self._last_inspection = None

        self._config = load_vision_config(str(self.get_parameter('vision_config_file').value))
        self._projection_config = dict(self._config.get('grid_projection', {}))
        self._verification_config = dict(self._config.get('verification', {}))
        self._palette, self._empty_rgb = self._load_palette()
        self._empty_aliases = {
            str(value).strip().lower()
            for value in self._verification_config.get(
                'empty_aliases',
                ['', 'empty', 'background', 'unknown'],
            )
        }

        model_qos = QoSProfile(depth=1)
        model_qos.reliability = ReliabilityPolicy.RELIABLE
        model_qos.durability = DurabilityPolicy.TRANSIENT_LOCAL

        self.create_subscription(
            Image,
            str(self.get_parameter('image_topic').value),
            self._on_image,
            qos_profile_sensor_data,
            callback_group=self._callback_group,
        )
        self.create_subscription(
            ExpectedModel,
            str(self.get_parameter('expected_model_topic').value),
            self._on_expected_model,
            model_qos,
            callback_group=self._callback_group,
        )
        self.create_subscription(
            Assembly_FeedbackMessage,
            str(self.get_parameter('assembly_feedback_topic').value),
            self._on_assembly_feedback,
            10,
            callback_group=self._callback_group,
        )
        self._debug_pub = self.create_publisher(
            Image,
            str(self.get_parameter('debug_image_topic').value),
            10,
        )
        self._webcam_result_pub = self.create_publisher(
            WebcamError,
            str(self.get_parameter('webcam_result_topic').value),
            10,
        )

        self.get_logger().info(
            f'VerifyNode ready: image={self.get_parameter("image_topic").value}, '
            f'result={self.get_parameter("webcam_result_topic").value}, '
            f'debug={self.get_parameter("debug_image_topic").value}'
        )

    def _load_palette(self):
        palette = {}
        empty_rgb = None
        for entry in self._config.get('palette', {}).get('entries', []):
            name = str(entry['name'])
            rgb = tuple(int(value) for value in entry['rgb'])
            if bool(entry.get('occupied', True)):
                palette[name] = rgb
            elif empty_rgb is None or name == 'empty':
                empty_rgb = rgb
        if empty_rgb is None:
            raise ValueError('vision.yaml palette requires an occupied=false entry.')
        return palette, empty_rgb

    def _on_image(self, msg: Image):
        frame = self._bridge.imgmsg_to_cv2(msg, desired_encoding='bgr8')
        with self._state_lock:
            self._latest_frame = frame.copy()
        self._publish_debug_overlay_if_due(frame)

    def _on_expected_model(self, msg: ExpectedModel):
        rows, cols = self._grid_shape_from_expected(msg)

        with self._state_lock:
            self._expected_colors = list(msg.colors)
            self._expected_rows = rows
            self._expected_cols = cols
            self._block_spans = self._block_spans_from_expected(msg.colors, rows, cols)
            self._inspected_steps.clear()
            self._last_inspection = None

        self.get_logger().info(
            f'기준 모델 수신: {rows}x{cols}, '
            f'{len(self._block_spans)}개 블록 판독 대상'
        )

    def _grid_shape_from_expected(self, msg: ExpectedModel) -> tuple[int, int]:
        rows = int(getattr(msg, 'grid_rows', 0) or 0)
        cols = int(getattr(msg, 'grid_cols', 0) or 0)
        if rows > 0 and cols > 0:
            return rows, cols

        default_rows = int(self.get_parameter('default_grid_rows').value)
        default_cols = int(self.get_parameter('default_grid_cols').value)
        cell_count = int(getattr(msg, 'grid_size', 0) or len(msg.colors))
        if cell_count == default_rows * default_cols:
            return default_rows, default_cols
        if default_rows > 0 and cell_count > 0 and cell_count % default_rows == 0:
            return default_rows, cell_count // default_rows
        if default_cols > 0 and cell_count > 0 and cell_count % default_cols == 0:
            return cell_count // default_cols, default_cols

        side = math.isqrt(cell_count) if cell_count > 0 else 0
        if side > 0 and side * side == cell_count:
            return side, side
        return default_rows, default_cols

    def _on_assembly_feedback(self, msg: Assembly_FeedbackMessage):
        step_to_check = int(msg.feedback.current_index) - 1
        if step_to_check < 0:
            return
        with self._state_lock:
            if step_to_check in self._inspected_steps:
                return
            self._inspected_steps.add(step_to_check)
        threading.Thread(
            target=self._delayed_publish_step_inspection,
            args=(step_to_check,),
            daemon=True,
        ).start()

    def _delayed_publish_step_inspection(self, step: int):
        delay_sec = float(self._verification_config.get('settle_delay_sec', 0.75))
        if delay_sec > 0.0:
            time.sleep(delay_sec)
        self._publish_step_inspection(step)

    def _publish_step_inspection(self, step: int):
        inspection = self._inspect_step(step)
        with self._state_lock:
            self._last_inspection = inspection
        self.get_logger().info(
            f'블록 판독: step={inspection.step}, status={inspection.status}, '
            f'match={inspection.match_rate:.2f}, {inspection.message}'
        )
        if bool(self.get_parameter('publish_webcam_result').value):
            self._publish_webcam_result(inspection)
        self._publish_debug_overlay_for_inspection(inspection)

    def _publish_webcam_result(self, inspection: InspectionResult):
        msg = WebcamError()
        msg.step = int(inspection.step)
        msg.row = int(inspection.row)
        msg.col = int(inspection.col)
        msg.expected_color = inspection.expected_color
        msg.detected_color = inspection.observed_color
        msg.message = (
            f'{inspection.status}: {inspection.message} '
            f'(confidence={inspection.confidence:.2f}, match={inspection.match_rate:.2f})'
        )
        self._webcam_result_pub.publish(msg)

    def _inspect_step(self, step: int) -> InspectionResult:
        with self._state_lock:
            expected_colors = list(self._expected_colors)
            rows = self._expected_rows
            cols = self._expected_cols
            block_spans = list(self._block_spans)
            frame = None if self._latest_frame is None else self._latest_frame.copy()

        inspection = InspectionResult()
        inspection.step = int(step)

        if frame is None:
            inspection.status = InspectionResult.CAMERA_ERROR
            inspection.message = '카메라 프레임을 아직 받지 못했습니다.'
            return inspection
        if not expected_colors or rows <= 0 or cols <= 0:
            inspection.status = InspectionResult.ROI_ERROR
            inspection.message = '기준 모델이 없거나 grid 크기가 유효하지 않습니다.'
            return inspection
        if step >= len(block_spans):
            inspection.status = InspectionResult.ROI_ERROR
            inspection.message = f'step {step}에 대응되는 블록 위치가 없습니다.'
            return inspection

        row, col_start, width, expected_color = block_spans[step]
        inspection.row = int(row)
        inspection.col = int(col_start)
        inspection.expected_color = self._display_color(expected_color)

        if self._front_plane_configured():
            return self._inspect_front_block(
                inspection,
                frame,
                row,
                col_start,
                width,
                expected_color,
            )

        try:
            observed_colors = self._colors_from_frame(frame, rows, cols)
        except ValueError as exc:
            inspection.status = InspectionResult.ROI_ERROR
            inspection.message = str(exc)
            return inspection
        indices = [row * cols + col for col in range(col_start, col_start + width)]
        matched = sum(
            1 for index in indices
            if index < len(observed_colors)
            and self._same_color(expected_colors[index], observed_colors[index])
        )
        match_rate = matched / float(len(indices))
        observed_summary = self._observed_summary(observed_colors, indices)

        inspection.observed_color = observed_summary
        inspection.confidence = float(match_rate)
        inspection.match_rate = float(match_rate)

        confidence_threshold = float(
            self._verification_config.get(
                'confidence_threshold',
                DEFAULT_CONFIDENCE_THRESHOLD,
            )
        )
        match_threshold = float(
            self._verification_config.get('match_rate', DEFAULT_MATCH_THRESHOLD)
        )
        if match_rate >= match_threshold and inspection.confidence >= confidence_threshold:
            inspection.status = InspectionResult.PASS
            inspection.message = '정상 배치'
        elif inspection.confidence < confidence_threshold:
            inspection.status = InspectionResult.UNCERTAIN
            inspection.message = (
                f'판독 불확실: expected={inspection.expected_color}, '
                f'observed={inspection.observed_color}'
            )
        else:
            inspection.status = InspectionResult.FAIL
            inspection.message = (
                f'색상/위치 불일치: expected={inspection.expected_color}, '
                f'observed={inspection.observed_color}'
            )
        return inspection

    def _colors_from_frame(self, frame, rows: int, cols: int) -> list[str]:
        if self._front_plane_configured():
            return self._front_grid_colors(frame, rows, cols)

        fitted = self._frame_for_grid(frame, rows, cols)
        _, cells = quantize_image_to_grid(
            fitted,
            self._palette,
            self._empty_rgb,
            rows,
            grid_cols=cols,
            config=self._projection_config,
        )
        return [cell.color if cell.occupied else 'empty' for cell in cells]

    def _frame_for_grid(self, frame, rows: int, cols: int):
        roi_frame = self._apply_roi(frame)
        if self._roi_configured():
            return roi_frame
        target_aspect = (cols * CELL_ASPECT_WIDTH) / (rows * CELL_ASPECT_HEIGHT)
        mosaic_config = self._config.get('mosaic', {})
        return fit_image(
            roi_frame,
            str(mosaic_config.get('fit_mode', 'smart_crop')),
            target_aspect=target_aspect,
            smart_crop_min_scale=float(mosaic_config.get('smart_crop_min_scale', 0.80)),
        )

    def _front_plane_configured(self) -> bool:
        return bool(self._verification_config.get('front_plane', {}).get('enabled', False))

    def _inspect_front_block(
        self,
        inspection: InspectionResult,
        frame,
        row: int,
        col_start: int,
        width: int,
        expected_color: str,
    ) -> InspectionResult:
        try:
            front_frame, crop_offset = self._front_crop_frame(frame)
            observed_color, color_fraction, vertical_fill, bottom_fill = (
                self._front_block_measure(
                    front_frame,
                    row,
                    col_start,
                    width,
                    expected_color,
                    crop_offset,
                )
            )
        except ValueError as exc:
            inspection.status = InspectionResult.ROI_ERROR
            inspection.message = str(exc)
            return inspection

        inspection.observed_color = observed_color
        inspection.match_rate = float(color_fraction)
        min_color_fraction = self._front_min_color_fraction(expected_color)
        inspection.confidence = float(
            min(
                color_fraction / max(0.01, min_color_fraction),
                vertical_fill / max(0.01, self._front_min_vertical_fill()),
                bottom_fill / max(0.01, self._front_min_bottom_fill()),
                1.0,
            )
        )

        same_color = self._same_color(expected_color, observed_color)
        stable_shape = (
            color_fraction >= min_color_fraction
            and vertical_fill >= self._front_min_vertical_fill()
            and bottom_fill >= self._front_min_bottom_fill()
        )

        if same_color and stable_shape:
            inspection.status = InspectionResult.PASS
            inspection.message = (
                f'정상 배치: color={color_fraction:.2f}, '
                f'height={vertical_fill:.2f}, bottom={bottom_fill:.2f}'
            )
        elif inspection.confidence < float(
            self._verification_config.get(
                'confidence_threshold',
                DEFAULT_CONFIDENCE_THRESHOLD,
            )
        ):
            inspection.status = InspectionResult.UNCERTAIN
            inspection.message = (
                f'판독 불확실: expected={inspection.expected_color}, '
                f'observed={inspection.observed_color}, '
                f'color={color_fraction:.2f}, height={vertical_fill:.2f}, '
                f'bottom={bottom_fill:.2f}'
            )
        else:
            inspection.status = InspectionResult.FAIL
            inspection.message = (
                f'색상/체결 불일치: expected={inspection.expected_color}, '
                f'observed={inspection.observed_color}, '
                f'color={color_fraction:.2f}, height={vertical_fill:.2f}, '
                f'bottom={bottom_fill:.2f}'
            )
        return inspection

    def _front_grid_colors(self, frame, rows: int, cols: int) -> list[str]:
        front_frame, crop_offset = self._front_crop_frame(frame)
        colors = []
        for row in range(rows):
            for col in range(cols):
                observed_color, color_fraction, _, _ = self._front_block_measure(
                    front_frame,
                    row,
                    col,
                    1,
                    None,
                    crop_offset,
                )
                if color_fraction < self._front_min_color_fraction(observed_color):
                    colors.append('empty')
                else:
                    colors.append(observed_color)
        return colors

    def _front_block_measure(
        self,
        frame,
        row: int,
        col_start: int,
        width: int,
        expected_color: str | None,
        crop_offset,
    ) -> tuple[str, float, float, float]:
        polygon = self._front_block_polygon(row, col_start, width, crop_offset)
        mask = np.zeros(frame.shape[:2], dtype=np.uint8)
        cv2.fillConvexPoly(mask, polygon.astype(np.int32), 255)
        pixels = frame[mask == 255]
        if pixels.size == 0:
            raise ValueError(
                f'front_plane ROI가 프레임 밖입니다: row={row}, col={col_start}, width={width}'
            )

        if expected_color:
            expected_name = self._display_color(expected_color)
            color_mask = self._front_expected_color_mask(frame, expected_name) & (mask == 255)
            color_fraction = self._mask_fraction(mask, color_mask)
            vertical_fill, bottom_fill = self._front_shape_fill(mask, color_mask)
            observed_color = (
                expected_name
                if color_fraction >= self._front_min_color_fraction(expected_name)
                else 'empty'
            )
            return observed_color, color_fraction, vertical_fill, bottom_fill

        return self._front_best_block_color(frame, mask)

    def _front_best_block_color(self, frame, roi_mask) -> tuple[str, float, float, float]:
        best = ('empty', 0.0, 0.0, 0.0)
        best_score = 0.0

        for color in self._palette:
            color_mask = self._front_color_mask(frame, color) & (roi_mask == 255)
            color_fraction = self._mask_fraction(roi_mask, color_mask)
            min_color_fraction = float(self._front_config().get('min_color_fraction', 0.25))
            if color_fraction < min_color_fraction:
                continue

            vertical_fill, bottom_fill = self._front_shape_fill(roi_mask, color_mask)
            if (
                vertical_fill < self._front_min_vertical_fill()
                or bottom_fill < self._front_min_bottom_fill()
            ):
                continue

            score = min(
                color_fraction / max(0.01, min_color_fraction),
                vertical_fill / max(0.01, self._front_min_vertical_fill()),
                bottom_fill / max(0.01, self._front_min_bottom_fill()),
            )
            if score > best_score:
                best = (color, color_fraction, vertical_fill, bottom_fill)
                best_score = score

        return best

    @staticmethod
    def _mask_fraction(roi_mask, color_mask) -> float:
        return float(np.count_nonzero(color_mask)) / float(max(1, np.count_nonzero(roi_mask)))

    def _front_shape_fill(self, roi_mask, color_mask) -> tuple[float, float]:
        ys, xs = np.where(color_mask)
        if len(xs) == 0:
            return 0.0, 0.0

        roi_ys, _ = np.where(roi_mask)
        roi_height = max(1, int(roi_ys.max() - roi_ys.min() + 1))
        vertical_fill = float(ys.max() - ys.min() + 1) / float(roi_height)

        bottom_start = int(round(roi_ys.min() + roi_height * 0.72))
        bottom_roi = roi_mask.copy()
        bottom_roi[:bottom_start, :] = 0
        bottom_pixels = max(1, int(np.count_nonzero(bottom_roi)))
        bottom_fill = float(
            np.count_nonzero(color_mask & (bottom_roi == 255))
        ) / float(bottom_pixels)
        return vertical_fill, bottom_fill

    def _front_block_polygon(self, row: int, col_start: int, width: int, crop_offset):
        scale = float(np.clip(self._front_config().get('cell_roi_scale', 0.82), 0.30, 1.20))
        col_inset = (1.0 - scale) * float(width) * 0.5
        row_inset = (1.0 - scale) * 0.5
        left = float(col_start) - 0.5 + col_inset
        right = float(col_start + width) - 0.5 - col_inset
        top = float(row) - 0.5 + row_inset
        bottom = float(row) + 0.5 - row_inset
        return np.float32([
            self._front_grid_point(left, top, crop_offset),
            self._front_grid_point(right, top, crop_offset),
            self._front_grid_point(right, bottom, crop_offset),
            self._front_grid_point(left, bottom, crop_offset),
        ])

    def _front_block_outline_polygon(self, row: int, col_start: int, width: int, crop_offset):
        left = float(col_start) - 0.5
        right = float(col_start + width) - 0.5
        top = float(row) - 0.5
        bottom = float(row) + 0.5
        return np.float32([
            self._front_grid_point(left, top, crop_offset),
            self._front_grid_point(right, top, crop_offset),
            self._front_grid_point(right, bottom, crop_offset),
            self._front_grid_point(left, bottom, crop_offset),
        ])

    def _front_grid_point(self, col: float, row: float, crop_offset):
        point = np.float32([[[float(col), float(row)]]])
        return cv2.perspectiveTransform(point, self._front_homography(crop_offset))[0, 0]

    def _front_homography(self, crop_offset):
        rows, cols = self._front_grid_size()
        if rows <= 0 or cols <= 0:
            raise ValueError('front_plane grid 크기가 유효하지 않습니다.')

        source = np.float32([
            [-0.5, -0.5],
            [float(cols) - 0.5, -0.5],
            [float(cols) - 0.5, float(rows) - 0.5],
            [-0.5, float(rows) - 0.5],
        ])
        target = self._front_corner_points() - crop_offset
        if cv2.contourArea(target) < 10.0:
            raise ValueError('front_plane corner pixel 좌표가 유효하지 않습니다.')
        return cv2.getPerspectiveTransform(source, target)

    def _front_corner_points(self):
        cfg = self._front_config()
        required_keys = (
            'top_left_corner_px',
            'top_right_corner_px',
            'bottom_right_corner_px',
            'bottom_left_corner_px',
        )
        missing_keys = [key for key in required_keys if key not in cfg]
        if missing_keys:
            raise ValueError(f'front_plane corner 좌표가 없습니다: {", ".join(missing_keys)}')
        return np.float32([
            cfg['top_left_corner_px'],
            cfg['top_right_corner_px'],
            cfg['bottom_right_corner_px'],
            cfg['bottom_left_corner_px'],
        ])

    def _front_crop_frame(self, frame):
        corners = self._front_corner_points()
        margin = max(0, int(self._front_config().get('crop_margin_px', 24)))
        frame_height, frame_width = frame.shape[:2]
        x0 = max(0, int(math.floor(float(corners[:, 0].min()))) - margin)
        y0 = max(0, int(math.floor(float(corners[:, 1].min()))) - margin)
        x1 = min(frame_width, int(math.ceil(float(corners[:, 0].max()))) + margin)
        y1 = min(frame_height, int(math.ceil(float(corners[:, 1].max()))) + margin)
        if x1 <= x0 or y1 <= y0:
            raise ValueError(
                f'front_plane crop 영역이 유효하지 않습니다: '
                f'x={x0}, y={y0}, width={x1 - x0}, height={y1 - y0}'
            )
        return frame[y0:y1, x0:x1].copy(), np.float32([x0, y0])

    def _front_grid_size(self) -> tuple[int, int]:
        with self._state_lock:
            rows = self._expected_rows or int(self.get_parameter('default_grid_rows').value)
            cols = self._expected_cols or int(self.get_parameter('default_grid_cols').value)
        return rows, cols

    def _front_config(self) -> dict:
        return dict(self._verification_config.get('front_plane', {}))

    def _front_min_color_fraction(self, color: str | None = None) -> float:
        if self._display_color(color or '') == 'green':
            return float(
                self._front_config().get(
                    'green_min_color_fraction',
                    self._front_config().get('min_color_fraction', 0.25),
                )
            )
        return float(self._front_config().get('min_color_fraction', 0.25))

    def _front_min_vertical_fill(self) -> float:
        return float(self._front_config().get('min_vertical_fill', 0.35))

    def _front_min_bottom_fill(self) -> float:
        return float(self._front_config().get('min_bottom_fill', 0.08))

    def _front_color_mask(self, image_bgr, color: str):
        color = self._display_color(color)
        if color not in self._palette:
            return np.zeros(image_bgr.shape[:2], dtype=bool)
        return self._front_lab_color_mask(
            image_bgr,
            color,
            float(self._front_config().get('color_lab_threshold', 72.0)),
        )

    def _front_lab_color_mask(self, image_bgr, color: str, threshold: float):
        lab_image = cv2.cvtColor(image_bgr, cv2.COLOR_BGR2LAB).astype(np.float32)
        expected_rgb = np.asarray([[self._palette[color]]], dtype=np.uint8)
        expected_lab = cv2.cvtColor(expected_rgb, cv2.COLOR_RGB2LAB)[0, 0].astype(np.float32)
        distance = np.linalg.norm(lab_image - expected_lab, axis=2)
        return distance <= threshold

    def _front_expected_color_mask(self, image_bgr, color: str):
        color = self._display_color(color)
        if color not in self._palette:
            return np.zeros(image_bgr.shape[:2], dtype=bool)
        mask = self._front_lab_color_mask(
            image_bgr,
            color,
            float(
                self._front_config().get(
                    f'{color}_color_lab_threshold',
                    self._front_config().get('color_lab_threshold', 72.0),
                )
            ),
        )
        if color == 'green':
            mask |= self._front_green_hsv_mask(image_bgr)
        return mask

    def _front_green_hsv_mask(self, image_bgr):
        cfg = self._front_config()
        hsv = cv2.cvtColor(image_bgr, cv2.COLOR_BGR2HSV)
        return cv2.inRange(
            hsv,
            (
                int(cfg.get('green_hsv_hue_min', 35)),
                int(cfg.get('green_hsv_min_saturation', 25)),
                int(cfg.get('green_hsv_min_value', 25)),
            ),
            (
                int(cfg.get('green_hsv_hue_max', 95)),
                255,
                255,
            ),
        ).astype(bool)

    def _roi_configured(self) -> bool:
        roi = self._verification_config.get('roi', {})
        return int(roi.get('width', 0)) > 0 and int(roi.get('height', 0)) > 0

    def _apply_roi(self, frame):
        roi = self._verification_config.get('roi', {})
        width = int(roi.get('width', 0))
        height = int(roi.get('height', 0))
        if width <= 0 or height <= 0:
            return frame

        frame_height, frame_width = frame.shape[:2]
        x0 = max(0, int(roi.get('x', 0)))
        y0 = max(0, int(roi.get('y', 0)))
        x1 = min(frame_width, x0 + width)
        y1 = min(frame_height, y0 + height)
        if x1 <= x0 or y1 <= y0:
            raise ValueError(
                f'ROI 범위 오류: x={x0}, y={y0}, width={width}, height={height}, '
                f'frame={frame_width}x{frame_height}'
            )
        return frame[y0:y1, x0:x1].copy()

    def _publish_debug_overlay_if_due(self, frame):
        interval_sec = float(self.get_parameter('debug_overlay_interval_sec').value)
        if interval_sec <= 0.0:
            return

        now = time.monotonic()
        if now - self._last_debug_overlay_time < interval_sec:
            return
        self._last_debug_overlay_time = now

        with self._state_lock:
            rows = self._expected_rows or int(self.get_parameter('default_grid_rows').value)
            cols = self._expected_cols or int(self.get_parameter('default_grid_cols').value)
            inspection = self._last_inspection
        self._publish_debug_overlay(frame, rows, cols, inspection)

    def _publish_debug_overlay_for_inspection(self, inspection: InspectionResult):
        with self._state_lock:
            if self._latest_frame is None:
                return
            frame = self._latest_frame.copy()
            rows = self._expected_rows or int(self.get_parameter('default_grid_rows').value)
            cols = self._expected_cols or int(self.get_parameter('default_grid_cols').value)
        self._publish_debug_overlay(frame, rows, cols, inspection)

    def _publish_debug_overlay(self, frame, rows: int, cols: int, inspection: InspectionResult | None):
        try:
            overlay = self._debug_overlay(frame, rows, cols, inspection)
            msg = self._bridge.cv2_to_imgmsg(overlay, encoding='bgr8')
            msg.header.stamp = self.get_clock().now().to_msg()
            msg.header.frame_id = 'front_camera_debug_grid'
            self._debug_pub.publish(msg)
        except Exception as exc:
            now = time.monotonic()
            if now - self._last_debug_error_time > 5.0:
                self._last_debug_error_time = now
                self.get_logger().warn(f'debug grid 생성 실패: {exc}')

    def _debug_overlay(self, frame, rows: int, cols: int, inspection: InspectionResult | None):
        if self._front_plane_configured():
            return self._front_debug_overlay(frame, rows, cols, inspection)

        fitted = self._frame_for_grid(frame, rows, cols)
        _, cells = quantize_image_to_grid(
            fitted,
            self._palette,
            self._empty_rgb,
            rows,
            grid_cols=cols,
            config=self._projection_config,
        )
        overlay = fitted.copy()
        height, width = overlay.shape[:2]
        x_edges = np.rint(np.linspace(0, width, cols + 1)).astype(int)
        y_edges = np.rint(np.linspace(0, height, rows + 1)).astype(int)

        for x in x_edges:
            cv2.line(overlay, (int(x), 0), (int(x), height - 1), (255, 255, 255), 1)
        for y in y_edges:
            cv2.line(overlay, (0, int(y)), (width - 1, int(y)), (255, 255, 255), 1)

        for cell in cells:
            label = self._display_color(cell.color if cell.occupied else 'empty')
            if label == 'empty':
                continue
            x = int((x_edges[cell.col] + x_edges[cell.col + 1]) * 0.5) - 10
            y = int((y_edges[cell.row] + y_edges[cell.row + 1]) * 0.5) + 5
            cv2.putText(
                overlay,
                label[0].upper(),
                (x, y),
                cv2.FONT_HERSHEY_SIMPLEX,
                0.45,
                (255, 255, 255),
                1,
                cv2.LINE_AA,
            )

        highlight = None if inspection is None else self._highlight_span(inspection.step)
        if highlight is not None:
            row, col, block_width = highlight
            cv2.rectangle(
                overlay,
                (int(x_edges[col]), int(y_edges[row])),
                (int(x_edges[min(cols, col + block_width)]) - 1, int(y_edges[row + 1]) - 1),
                (0, 255, 255),
                3,
            )

        cv2.putText(
            overlay,
            f'{cols}x{rows} debug grid',
            (10, 24),
            cv2.FONT_HERSHEY_SIMPLEX,
            0.7,
            (0, 255, 255),
            2,
            cv2.LINE_AA,
        )
        return overlay

    def _front_debug_overlay(
        self,
        frame,
        rows: int,
        cols: int,
        inspection: InspectionResult | None,
    ):
        overlay, crop_offset = self._front_crop_frame(frame)
        self._draw_front_grid(overlay, rows, cols, crop_offset)

        self._draw_front_calibration_points(overlay, crop_offset)

        highlight = None if inspection is None else self._highlight_span(inspection.step)
        if highlight is not None:
            row, col, block_width = highlight
            polygon = self._front_block_outline_polygon(
                row,
                col,
                block_width,
                crop_offset,
            ).astype(np.int32)
            self._draw_front_polygon(
                overlay,
                polygon,
                self._inspection_overlay_color(inspection.status),
                3,
            )

        if inspection is not None:
            self._draw_inspection_summary(overlay, inspection)
        return overlay

    def _draw_front_grid(self, overlay, rows: int, cols: int, crop_offset):
        grid_points = np.empty((rows + 1, cols + 1, 2), dtype=np.int32)
        for row_index in range(rows + 1):
            row_boundary = float(row_index) - 0.5
            for col_index in range(cols + 1):
                col_boundary = float(col_index) - 0.5
                grid_points[row_index, col_index] = np.rint(
                    self._front_grid_point(col_boundary, row_boundary, crop_offset)
                ).astype(np.int32)

        for row_index in range(rows + 1):
            for col_index in range(cols):
                self._draw_front_grid_segment(
                    overlay,
                    grid_points[row_index, col_index],
                    grid_points[row_index, col_index + 1],
                )
        for col_index in range(cols + 1):
            for row_index in range(rows):
                self._draw_front_grid_segment(
                    overlay,
                    grid_points[row_index, col_index],
                    grid_points[row_index + 1, col_index],
                )

    def _draw_front_grid_segment(self, overlay, start, end):
        start_point = (int(start[0]), int(start[1]))
        end_point = (int(end[0]), int(end[1]))
        cv2.line(overlay, start_point, end_point, (255, 255, 255), 1, cv2.LINE_AA)

    def _draw_front_polygon(self, overlay, polygon, color, thickness: int):
        points = [(int(point[0]), int(point[1])) for point in polygon]
        for index, start in enumerate(points):
            cv2.line(
                overlay,
                start,
                points[(index + 1) % len(points)],
                color,
                thickness,
                cv2.LINE_8,
            )

    def _inspection_overlay_color(self, status: str):
        if status == InspectionResult.PASS:
            return (0, 255, 0)
        if status == InspectionResult.FAIL:
            return (0, 0, 255)
        if status == InspectionResult.UNCERTAIN:
            return (0, 255, 255)
        if status in (InspectionResult.CAMERA_ERROR, InspectionResult.ROI_ERROR):
            return (255, 0, 255)
        return (255, 255, 255)

    def _draw_inspection_summary(self, overlay, inspection: InspectionResult):
        text = f'detected={inspection.observed_color}'
        cv2.putText(
            overlay,
            text,
            (10, 24),
            cv2.FONT_HERSHEY_SIMPLEX,
            0.55,
            (0, 0, 0),
            1,
            cv2.LINE_AA,
        )

    def _draw_front_calibration_points(self, overlay, crop_offset):
        cfg = self._front_config()
        points = [
            ('TL', cfg.get('top_left_corner_px', [0, 0])),
            ('TR', cfg.get('top_right_corner_px', [0, 0])),
            ('BR', cfg.get('bottom_right_corner_px', [0, 0])),
            ('BL', cfg.get('bottom_left_corner_px', [0, 0])),
        ]
        for label, point in points:
            x = int(round(float(point[0]) - float(crop_offset[0])))
            y = int(round(float(point[1]) - float(crop_offset[1])))
            cv2.circle(overlay, (x, y), 5, (0, 0, 255), -1)
            cv2.putText(
                overlay,
                label,
                (x + 7, y - 7),
                cv2.FONT_HERSHEY_SIMPLEX,
                0.5,
                (0, 0, 255),
                1,
                cv2.LINE_AA,
            )

    def _highlight_span(self, step: int | None):
        if step is None:
            return None
        with self._state_lock:
            if step < 0 or step >= len(self._block_spans):
                return None
            row, col, width, _ = self._block_spans[step]
        return int(row), int(col), int(width)

    def _block_spans_from_expected(
        self,
        colors: list[str],
        rows: int,
        cols: int,
    ) -> list[tuple[int, int, int, str]]:
        if len(colors) != rows * cols:
            return []

        try:
            grid = [
                list(colors[row * cols:(row + 1) * cols])
                for row in range(rows)
            ]
            row_blocks = self._match_blocks(grid, cols, rows)
        except ValueError as exc:
            self.get_logger().warn(f'검증용 블록 계획 생성 실패: {exc}')
            return []

        spans = []
        for layer in range(rows):
            row = rows - 1 - layer
            for col_start, width, color, _ in row_blocks.get(row, []):
                spans.append((row, col_start, width, color))
        return spans

    @staticmethod
    def _generate_partitions(length: int) -> list[list[int]]:
        if length == 0:
            return [[]]
        if length < 2:
            return []

        partitions = []
        for width in (2, 3):
            if length >= width:
                for rest in VerifyNode._generate_partitions(length - width):
                    partitions.append([width] + rest)
        return partitions

    @staticmethod
    def _internal_boundaries(blocks, cols: int) -> set[int]:
        boundaries = set()
        for col_start, width, _, _ in blocks:
            boundaries.add(col_start)
            boundaries.add(col_start + width)
        boundaries.discard(0)
        boundaries.discard(cols)
        return boundaries

    @staticmethod
    def _block_loss(col_start: int, width: int, lower_boundaries: set[int]) -> int:
        left = col_start
        right = col_start + width
        hits = [boundary for boundary in lower_boundaries if left <= boundary <= right]
        if len(hits) == 1 and hits[0] != left and hits[0] != right:
            return 0
        return 1

    @staticmethod
    def _to_blocks(runs, partitions):
        blocks = []
        for (color, _, start_col), partition in zip(runs, partitions):
            col = start_col
            for width in partition:
                blocks.append((col, width, color, 1 if width == 2 else 2))
                col += width
        return blocks

    def _find_runs(self, row: list[str]):
        runs = []
        col = 0
        while col < len(row):
            color = row[col]
            if self._is_empty(color):
                col += 1
                continue

            length = 1
            while col + length < len(row) and self._same_color(row[col + length], color):
                length += 1

            if length >= 2:
                runs.append((color, length, col))
            col += length
        return runs

    def _run_partitions(self, runs):
        partitions = []
        for color, length, start_col in runs:
            candidates = self._generate_partitions(length)
            if not candidates:
                raise ValueError(
                    f'길이 {length}의 런({color}, col {start_col})을 분할할 수 없습니다.'
                )
            partitions.append(candidates)
        return partitions

    def _match_blocks(self, grid: list[list[str]], cols: int, rows: int):
        bottom = rows - 1
        runs = self._find_runs(grid[bottom])
        if not runs:
            return {row: [] for row in range(rows)}

        candidates = []
        for partitions in iter_product(*self._run_partitions(runs)):
            blocks = self._to_blocks(runs, partitions)
            type2_count = sum(1 for _, width, _, _ in blocks if width == 3)
            candidates.append((type2_count, blocks))
        candidates.sort(key=lambda item: item[0], reverse=True)

        beam = []
        for _, blocks in candidates[:DEFAULT_BEAM_WIDTH]:
            beam.append((0.0, {bottom: blocks}, self._internal_boundaries(blocks, cols)))

        for layer in range(1, rows):
            row = rows - 1 - layer
            weight = math.sqrt(rows - layer)
            runs = self._find_runs(grid[row])
            if not runs:
                beam = [(loss, {**row_blocks, row: []}, boundaries) for loss, row_blocks, boundaries in beam]
                continue

            new_beam = []
            for prev_loss, prev_rows, lower_boundaries in beam:
                for partitions in iter_product(*self._run_partitions(runs)):
                    blocks = self._to_blocks(runs, partitions)
                    loss = sum(
                        self._block_loss(col_start, width, lower_boundaries)
                        for col_start, width, _, _ in blocks
                    )
                    total_loss = prev_loss + loss * weight
                    new_beam.append((
                        total_loss,
                        {**prev_rows, row: blocks},
                        self._internal_boundaries(blocks, cols),
                    ))

            new_beam.sort(key=lambda item: item[0])
            beam = new_beam[:DEFAULT_BEAM_WIDTH]

        return beam[0][1]

    def _observed_summary(self, observed_colors: list[str], indices: list[int]) -> str:
        colors = [
            self._display_color(observed_colors[index])
            for index in indices
            if index < len(observed_colors)
        ]
        if not colors:
            return 'empty'
        unique_colors = []
        for color in colors:
            if color not in unique_colors:
                unique_colors.append(color)
        return unique_colors[0] if len(unique_colors) == 1 else '/'.join(unique_colors)

    def _same_color(self, left: str, right: str) -> bool:
        if self._is_empty(left) and self._is_empty(right):
            return True
        return str(left).strip().lower() == str(right).strip().lower()

    def _is_empty(self, color: str) -> bool:
        return str(color).strip().lower() in self._empty_aliases

    def _display_color(self, color: str) -> str:
        return 'empty' if self._is_empty(color) else str(color).strip().lower()


def main(args=None):
    rclpy.init(args=args)
    node = VerifyNode()
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

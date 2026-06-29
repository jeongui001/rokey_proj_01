from __future__ import annotations

import threading
from typing import Optional

import cv2
import numpy as np
import rclpy
from rclpy.callback_groups import ReentrantCallbackGroup
from rclpy.executors import MultiThreadedExecutor
from rclpy.node import Node
from std_srvs.srv import SetBool

from cobot1_interfaces.srv import CheckBlock

PAUSE_SERVICE = '/robot/pause'
CHECK_SERVICE = '/webcam/check_block'

# 블록 유형별 합격 원 개수
CIRCLE_RANGE = {
    1: (2, 5),  # 2x2: 3~5개
    2: (4, 7),  # 3x2: 5~7개
}

# 4점 좌표 [(x1,y1),(x2,y2),(x3,y3),(x4,y4)] 시계 방향 (좌상→우상→우하→좌하).
# 키: (block_type, color). None이면 전체 이미지 사용.
# build_config.py 실행 후 출력된 값으로 교체할 것.
BLOCK_ROI: dict[tuple[int, str], Optional[list[tuple[int, int]]]] = {
    (1, "blue"):   [(44, 230), (304, 221), (301, 419), (70, 421)],   # 2x2
    (1, "green"):  [(63, 236), (323, 229), (311, 423), (89, 431)],   # 2x2
    (1, "red"):    [(49, 234), (303, 226), (293, 429), (72, 443)],   # 2x2
    (1, "yellow"): [(53, 236), (303, 228), (301, 418), (79, 427)],   # 2x2
    (2, "blue"):   [(47, 188), (326, 184), (311, 475), (80, 477)],   # 3x2
    (2, "green"):  [(60, 308), (317, 300), (307, 475), (80, 478)],   # 3x2
    (2, "red"):    [(75, 192), (355, 181), (328, 477), (108, 477)],  # 3x2
    (2, "yellow"): [(65, 186), (342, 178), (325, 475), (98, 477)],   # 3x2
}

HOUGH_PARAMS: dict[tuple[int, str], dict] = {
    (1, "blue"):   dict(clip_limit=2.0, dp=1.2, min_dist=80, param1=50, param2=30, min_r=5,  max_r=39),  # 2x2
    (1, "green"):  dict(clip_limit=2.5, dp=1.2, min_dist=77, param1=50, param2=40, min_r=6,  max_r=50),  # 2x2
    (1, "red"):    dict(clip_limit=2.0, dp=1.2, min_dist=79, param1=50, param2=30, min_r=5,  max_r=44),  # 2x2
    (1, "yellow"): dict(clip_limit=2.0, dp=1.2, min_dist=80, param1=50, param2=30, min_r=5,  max_r=50),  # 2x2
    (2, "blue"):   dict(clip_limit=3.0, dp=1.2, min_dist=90, param1=50, param2=35, min_r=5,  max_r=50),  # 3x2
    (2, "green"):  dict(clip_limit=3.0, dp=1.2, min_dist=90, param1=50, param2=30, min_r=5,  max_r=50),  # 3x2
    (2, "red"):    dict(clip_limit=3.0, dp=1.2, min_dist=80, param1=50, param2=30, min_r=15, max_r=50),  # 3x2
    (2, "yellow"): dict(clip_limit=2.5, dp=1.2, min_dist=80, param1=50, param2=30, min_r=5,  max_r=50),  # 3x2
}


def perspective_crop(
    image: np.ndarray,
    pts: Optional[list[tuple[int, int]]],
) -> np.ndarray:
    """
    4점 원근 변환으로 ROI를 정면에서 본 직사각형 이미지로 반환한다.
    pts는 시계 방향 순서: [좌상, 우상, 우하, 좌하].
    None이면 전체 이미지를 반환한다.
    출력 크기는 4점에서 계산한 폭·높이로 결정된다.
    """
    if pts is None:
        return image

    src = np.array(pts, dtype=np.float32)
    (tl, tr, br, bl) = src

    w = int(max(
        np.linalg.norm(tr - tl),
        np.linalg.norm(br - bl),
    ))
    h = int(max(
        np.linalg.norm(bl - tl),
        np.linalg.norm(br - tr),
    ))

    dst = np.array([
        [0,     0    ],
        [w - 1, 0    ],
        [w - 1, h - 1],
        [0,     h - 1],
    ], dtype=np.float32)

    M = cv2.getPerspectiveTransform(src, dst)
    return cv2.warpPerspective(image, M, (w, h))


def detect_circles(image_bgr: np.ndarray, hough: dict) -> tuple[int, np.ndarray]:
    """BGR 이미지에서 허프 원 변환으로 원을 검출한다.
    Returns: (검출 개수, 원이 그려진 BGR 이미지)
    """
    gray = cv2.cvtColor(image_bgr, cv2.COLOR_BGR2GRAY)
    clahe = cv2.createCLAHE(clipLimit=hough.get("clip_limit", 1.0), tileGridSize=(8, 8))
    gray = clahe.apply(gray)
    blurred = cv2.GaussianBlur(gray, (9, 9), 2)
    circles = cv2.HoughCircles(
        blurred,
        cv2.HOUGH_GRADIENT,
        dp=hough["dp"],
        minDist=hough["min_dist"],
        param1=hough["param1"],
        param2=hough["param2"],
        minRadius=int(hough["min_r"]),
        maxRadius=int(hough["max_r"]),
    )
    annotated = image_bgr.copy()
    if circles is None:
        return 0, annotated
    count = int(circles.shape[1])
    for cx, cy, r in circles[0]:
        cv2.circle(annotated, (int(cx), int(cy)), int(r), (0, 255, 0), 2)
        cv2.circle(annotated, (int(cx), int(cy)), 3, (0, 0, 255), -1)
    return count, annotated


class WebcamCheckerNode(Node):
    """
    블록 존재 확인 서비스 노드.
    /webcam/check_block 서비스 요청을 받으면 웹캠으로 촬영 후 HoughCircles로 판정한다.
    불합격 시 /robot/pause 서비스를 호출해 로봇을 정지시킨다.
    """

    def __init__(self) -> None:
        super().__init__('webcam_checker')

        self.declare_parameter('video_device', '/dev/video1')
        self.declare_parameter('debug', True)
        self.declare_parameter('debug_dir', '/home/hwangjeongui/webcam_debug')
        self._device = str(self.get_parameter('video_device').value)
        self._debug = bool(self.get_parameter('debug').value)
        self._debug_dir = str(self.get_parameter('debug_dir').value)

        if self._debug:
            import os
            os.makedirs(self._debug_dir, exist_ok=True)
            self.get_logger().info(f'디버그 이미지 저장: {self._debug_dir}')

        source = int(self._device) if self._device.isdigit() else self._device
        self._cap = cv2.VideoCapture(source)
        if not self._cap.isOpened():
            self.get_logger().error(f'웹캠을 열 수 없음: {self._device}')

        self._latest_frame: Optional[np.ndarray] = None
        self._frame_lock = threading.Lock()
        self._capture_thread = threading.Thread(target=self._capture_loop, daemon=True)
        self._capture_thread.start()

        self._callback_group = ReentrantCallbackGroup()
        self._pause_client = self.create_client(SetBool, PAUSE_SERVICE)
        self._service = self.create_service(
            CheckBlock,
            CHECK_SERVICE,
            self._handle_check,
            callback_group=self._callback_group,
        )

        self.get_logger().info(
            f'WebcamCheckerNode 준비: device={self._device}, service={CHECK_SERVICE}'
        )

    def _capture_loop(self) -> None:
        """백그라운드에서 계속 프레임을 읽어 최신 프레임만 보관한다."""
        while True:
            if not self._cap.isOpened():
                break
            ok, frame = self._cap.read()
            if ok and frame is not None:
                with self._frame_lock:
                    self._latest_frame = frame

    def _capture_frame(self) -> Optional[np.ndarray]:
        """최신 프레임을 반환한다. 아직 없으면 None."""
        with self._frame_lock:
            if self._latest_frame is None:
                self.get_logger().error('프레임 없음 — 웹캠 확인 필요')
                return None
            return self._latest_frame.copy()

    def _call_pause(self) -> None:
        """/robot/pause 서비스를 호출해 로봇을 일시정지시킨다."""
        if not self._pause_client.wait_for_service(timeout_sec=2.0):
            self.get_logger().error('/robot/pause 서비스 없음 — 정지 불가')
            return
        req = SetBool.Request()
        req.data = True
        future = self._pause_client.call_async(req)
        done = threading.Event()
        future.add_done_callback(lambda _: done.set())
        if not done.wait(timeout=5.0):
            self.get_logger().error('일시정지 요청 타임아웃 — 로봇 미정지')
            return
        self.get_logger().info('로봇 일시정지 요청 완료')

    def _handle_check(
        self,
        request: CheckBlock.Request,
        response: CheckBlock.Response,
    ) -> CheckBlock.Response:
        block_type = int(request.block_type)
        color = str(request.color).strip().lower()
        circle_range = CIRCLE_RANGE.get(block_type)

        if circle_range is None:
            response.passed = False
            response.detected_circles = 0
            response.message = f'알 수 없는 block_type: {block_type}'
            self.get_logger().error(response.message)
            return response
        min_circles, max_circles = circle_range

        frame = self._capture_frame()
        if frame is None:
            response.passed = False
            response.detected_circles = 0
            response.message = '웹캠 캡처 실패'
            self._call_pause()
            return response

        roi = BLOCK_ROI.get((block_type, color))
        cropped = perspective_crop(frame, roi)
        hough = HOUGH_PARAMS.get((block_type, color), next(iter(HOUGH_PARAMS.values())))
        detected, annotated = detect_circles(cropped, hough)

        if self._debug:
            tag = f'bt{block_type}_{color}'
            cv2.imwrite(f'{self._debug_dir}/{tag}_1_raw.jpg', frame)
            cv2.imwrite(f'{self._debug_dir}/{tag}_2_warped.jpg', cropped)
            cv2.imwrite(f'{self._debug_dir}/{tag}_3_result.jpg', annotated)

        response.detected_circles = min(detected, 255)
        result_msg = f'허프 원 검출: {detected}개 / 허용 {min_circles}~{max_circles}개 ({block_type}형 {color})'
        self.get_logger().info(result_msg)
        print(f'[webcam_checker] {result_msg}', flush=True)

        if min_circles <= detected <= max_circles:
            response.passed = True
            response.message = f'합격: {detected}개 검출 (허용 {min_circles}~{max_circles}개)'
            self.get_logger().info(response.message)
        else:
            response.passed = False
            response.message = f'불합격: {detected}개 검출 (허용 {min_circles}~{max_circles}개)'
            self.get_logger().warn(response.message)
            self._call_pause()

        return response


def main(args=None) -> None:
    rclpy.init(args=args)
    node = WebcamCheckerNode()
    executor = MultiThreadedExecutor(num_threads=3)
    executor.add_node(node)
    try:
        executor.spin()
    except KeyboardInterrupt:
        node.get_logger().info('WebcamCheckerNode 종료')
    finally:
        node._cap.release()
        executor.shutdown()
        node.destroy_node()
        rclpy.shutdown()


if __name__ == '__main__':
    main()

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
REQUIRED_CIRCLES = {
    1: 4,  # 2x2
    2: 6,  # 3x2
}

# 픽셀 좌표 (x, y, w, h). None이면 전체 이미지 사용. 실측 후 채울 것.
BLOCK_ROI: dict[int, Optional[tuple[int, int, int, int]]] = {
    1: None,  # 2x2 — TODO
    2: None,  # 3x2 — TODO
}

# HoughCircles 파라미터 — 실측 튜닝 필요
HOUGH_DP = 1.2
HOUGH_MIN_DIST = 20
HOUGH_PARAM1 = 50
HOUGH_PARAM2 = 30
HOUGH_MIN_RADIUS = 5
HOUGH_MAX_RADIUS = 50


def crop_roi(
    image: np.ndarray,
    roi: Optional[tuple[int, int, int, int]],
) -> np.ndarray:
    """ROI가 지정된 경우 크롭, None이면 전체 이미지 반환."""
    if roi is None:
        return image
    x, y, w, h = roi
    return image[y:y + h, x:x + w]


def count_circles(image_bgr: np.ndarray) -> int:
    """BGR 이미지에서 허프 원 변환으로 원 개수를 반환한다."""
    gray = cv2.cvtColor(image_bgr, cv2.COLOR_BGR2GRAY)
    blurred = cv2.GaussianBlur(gray, (9, 9), 2)
    circles = cv2.HoughCircles(
        blurred,
        cv2.HOUGH_GRADIENT,
        dp=HOUGH_DP,
        minDist=HOUGH_MIN_DIST,
        param1=HOUGH_PARAM1,
        param2=HOUGH_PARAM2,
        minRadius=HOUGH_MIN_RADIUS,
        maxRadius=HOUGH_MAX_RADIUS,
    )
    if circles is None:
        return 0
    return int(circles.shape[1])


class WebcamCheckerNode(Node):
    """
    블록 존재 확인 서비스 노드.
    /webcam/check_block 서비스 요청을 받으면 웹캠으로 촬영 후 HoughCircles로 판정한다.
    불합격 시 /robot/pause 서비스를 호출해 로봇을 정지시킨다.
    """

    def __init__(self) -> None:
        super().__init__('webcam_checker')

        self.declare_parameter('video_device', '/dev/video1')
        self._device = str(self.get_parameter('video_device').value)

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

    def _capture_frame(self) -> Optional[np.ndarray]:
        """웹캠에서 프레임 한 장을 캡처해 반환한다. 실패 시 None."""
        source = int(self._device) if self._device.isdigit() else self._device
        cap = cv2.VideoCapture(source)
        if not cap.isOpened():
            self.get_logger().error(f'웹캠을 열 수 없음: {self._device}')
            return None
        ok, frame = cap.read()
        cap.release()
        if not ok or frame is None:
            self.get_logger().error('프레임 캡처 실패')
            return None
        return frame

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
        required = REQUIRED_CIRCLES.get(block_type)

        if required is None:
            response.passed = False
            response.detected_circles = 0
            response.message = f'알 수 없는 block_type: {block_type}'
            self.get_logger().error(response.message)
            return response

        frame = self._capture_frame()
        if frame is None:
            response.passed = False
            response.detected_circles = 0
            response.message = '웹캠 캡처 실패'
            self._call_pause()
            return response

        roi = BLOCK_ROI.get(block_type)
        cropped = crop_roi(frame, roi)
        detected = count_circles(cropped)

        response.detected_circles = min(detected, 255)
        if detected >= required:
            response.passed = True
            response.message = f'합격: {detected}개 검출 (필요 {required}개)'
            self.get_logger().info(response.message)
        else:
            response.passed = False
            response.message = f'불합격: {detected}개 검출 (필요 {required}개)'
            self.get_logger().warn(response.message)
            self._call_pause()

        return response


def main(args=None) -> None:
    rclpy.init(args=args)
    node = WebcamCheckerNode()
    executor = MultiThreadedExecutor(num_threads=2)
    executor.add_node(node)
    try:
        executor.spin()
    except KeyboardInterrupt:
        node.get_logger().info('WebcamCheckerNode 종료')
    finally:
        executor.shutdown()
        node.destroy_node()
        rclpy.shutdown()


if __name__ == '__main__':
    main()

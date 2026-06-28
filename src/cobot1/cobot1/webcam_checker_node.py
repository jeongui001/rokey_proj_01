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

# 4점 좌표 [(x1,y1),(x2,y2),(x3,y3),(x4,y4)] 시계 방향 (좌상→우상→우하→좌하).
# 키: (block_type, color). None이면 전체 이미지 사용.
# build_config.py 실행 후 출력된 값으로 교체할 것.
BLOCK_ROI: dict[tuple[int, str], Optional[list[tuple[int, int]]]] = {
    (1, "yellow"): None,
    (1, "red"):    None,
    (1, "blue"):   None,
    (1, "green"):  None,
    (2, "yellow"): None,
    (2, "red"):    None,
    (2, "blue"):   None,
    (2, "green"):  None,
}

# HoughCircles 파라미터 — (block_type, color)별. build_config.py 출력값으로 교체할 것.
HOUGH_PARAMS: dict[tuple[int, str], dict] = {
    (1, "yellow"): dict(dp=1.2, min_dist=20, param1=50, param2=30, min_r=5, max_r=50),
    (1, "red"):    dict(dp=1.2, min_dist=20, param1=50, param2=30, min_r=5, max_r=50),
    (1, "blue"):   dict(dp=1.2, min_dist=20, param1=50, param2=30, min_r=5, max_r=50),
    (1, "green"):  dict(dp=1.2, min_dist=20, param1=50, param2=30, min_r=5, max_r=50),
    (2, "yellow"): dict(dp=1.2, min_dist=20, param1=50, param2=30, min_r=5, max_r=50),
    (2, "red"):    dict(dp=1.2, min_dist=20, param1=50, param2=30, min_r=5, max_r=50),
    (2, "blue"):   dict(dp=1.2, min_dist=20, param1=50, param2=30, min_r=5, max_r=50),
    (2, "green"):  dict(dp=1.2, min_dist=20, param1=50, param2=30, min_r=5, max_r=50),
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


def count_circles(image_bgr: np.ndarray, hough: dict) -> int:
    """BGR 이미지에서 허프 원 변환으로 원 개수를 반환한다."""
    gray = cv2.cvtColor(image_bgr, cv2.COLOR_BGR2GRAY)
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
        color = str(request.color).strip().lower()
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

        roi = BLOCK_ROI.get((block_type, color))
        cropped = perspective_crop(frame, roi)
        hough = HOUGH_PARAMS.get((block_type, color), next(iter(HOUGH_PARAMS.values())))
        detected = count_circles(cropped, hough)

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

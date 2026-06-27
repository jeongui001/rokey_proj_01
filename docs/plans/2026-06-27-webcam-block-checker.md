# 웹캠 블록 검사 노드 구현 계획

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** 키팅 트레이에서 블록을 집기 직전 웹캠으로 블록 존재를 확인하고, 불합격 시 로봇을 자동 일시정지시킨다.

**Architecture:** `WebcamCheckerNode`가 ROS2 서비스(`/webcam/check_block`)를 제공한다. `RobotControllerNode`는 `KITTING_PRE_GRIP_WAIT` 단계에서 이 서비스를 동기 호출하고, 불합격이면 예외를 던져 액션을 abort한다. 웹캠 노드는 직접 `/robot/pause`를 호출해 로봇도 정지시킨다.

**Tech Stack:** ROS2 Humble, Python 3.10+, OpenCV (`cv2.HoughCircles`), `cobot1_interfaces`

## Global Constraints

- 빌드는 사용자가 직접 실행 (`colcon build`). 코드에서 빌드 명령 실행 금지.
- 기존 코드의 로직·포맷·스타일 변경 금지. 요청된 변경만 수행.
- `BLOCK_ROI` 좌표는 미확정 — `None` 플레이스홀더로 두고 전체 이미지 사용.
- HoughCircles 파라미터는 미확정 — 기본값으로 두고 튜닝은 실측 후 진행.
- 웹캠 장치: 기본 `/dev/video1` (파라미터로 변경 가능).

---

## 파일 맵

| 파일 | 작업 |
|------|------|
| `src/cobot1_interfaces/srv/CheckBlock.srv` | **신규 생성** |
| `src/cobot1_interfaces/CMakeLists.txt` | **수정** — `CheckBlock.srv` 등록 |
| `src/cobot1/cobot1/webcam_checker_node.py` | **신규 생성** |
| `src/cobot1/setup.py` | **수정** — entry point 추가 |
| `src/cobot1/cobot1/robot_controller_node.py` | **수정** — `_check_block` 추가, `KITTING_PRE_GRIP_WAIT` 교체 |
| `src/cobot1/launch/assembly.launch.py` | **수정** — `webcam_checker` 노드 추가 |

---

## Task 1: CheckBlock.srv 인터페이스 추가

**Files:**
- Create: `src/cobot1_interfaces/srv/CheckBlock.srv`
- Modify: `src/cobot1_interfaces/CMakeLists.txt`

**Interfaces:**
- Produces: `CheckBlock.Request.block_type (uint8)`, `CheckBlock.Response.passed (bool)`, `CheckBlock.Response.detected_circles (uint8)`, `CheckBlock.Response.message (string)`

- [ ] **Step 1: srv 파일 생성**

`src/cobot1_interfaces/srv/CheckBlock.srv` 내용:
```
uint8 block_type   # 1=2x2  2=3x2
---
bool passed
uint8 detected_circles
string message
```

- [ ] **Step 2: CMakeLists.txt에 등록**

`src/cobot1_interfaces/CMakeLists.txt`의 `rosidl_generate_interfaces` 블록에 한 줄 추가:

```cmake
rosidl_generate_interfaces(${PROJECT_NAME}
  "msg/WebcamError.msg"
  "msg/ExpectedModel.msg"
  "msg/BlockTask.msg"
  "srv/ProcessMosaic.srv"
  "srv/SequencePlan.srv"
  "srv/CheckBlock.srv"
  "action/Assembly.action"
  DEPENDENCIES builtin_interfaces std_msgs sensor_msgs geometry_msgs
)
```

- [ ] **Step 3: 빌드 요청**

사용자에게 빌드를 요청한다:
```
colcon build --packages-select cobot1_interfaces
source install/setup.bash
```

빌드 성공 확인:
```bash
ros2 interface show cobot1_interfaces/srv/CheckBlock
```

예상 출력:
```
uint8 block_type
---
bool passed
uint8 detected_circles
string message
```

- [ ] **Step 4: 커밋**

```bash
git add src/cobot1_interfaces/srv/CheckBlock.srv src/cobot1_interfaces/CMakeLists.txt
git commit -m "feat: CheckBlock.srv 인터페이스 추가"
```

---

## Task 2: WebcamCheckerNode 구현

**Files:**
- Create: `src/cobot1/cobot1/webcam_checker_node.py`
- Modify: `src/cobot1/setup.py`

**Interfaces:**
- Consumes: `CheckBlock.srv` (Task 1)
- Produces: `/webcam/check_block` 서비스, `/robot/pause` 서비스 클라이언트

- [ ] **Step 1: `webcam_checker_node.py` 생성**

`src/cobot1/cobot1/webcam_checker_node.py`:

```python
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
        done.wait(timeout=5.0)
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
```

- [ ] **Step 2: `count_circles` 단위 테스트 작성**

`src/cobot1/test/test_webcam_checker.py`:

```python
import numpy as np
import pytest
from cobot1.webcam_checker_node import count_circles, crop_roi


def _make_circle_image(n: int, size: int = 200) -> np.ndarray:
    """n개의 원이 그려진 BGR 이미지를 생성한다."""
    img = np.zeros((size, size, 3), dtype=np.uint8)
    spacing = size // (n + 1)
    for i in range(n):
        cx = spacing * (i + 1)
        cy = size // 2
        cv2.circle(img, (cx, cy), 15, (200, 200, 200), -1)
    return img


import cv2  # noqa: E402 (import after helper that uses it)


def test_count_circles_zero():
    blank = np.zeros((200, 200, 3), dtype=np.uint8)
    assert count_circles(blank) == 0


def test_count_circles_four():
    img = _make_circle_image(4)
    result = count_circles(img)
    assert result >= 4


def test_count_circles_six():
    img = _make_circle_image(6, size=300)
    result = count_circles(img)
    assert result >= 6


def test_crop_roi_none_returns_original():
    img = np.zeros((100, 100, 3), dtype=np.uint8)
    result = crop_roi(img, None)
    assert result is img


def test_crop_roi_applies_crop():
    img = np.zeros((100, 100, 3), dtype=np.uint8)
    result = crop_roi(img, (10, 20, 50, 30))
    assert result.shape == (30, 50, 3)
```

- [ ] **Step 3: 테스트 실행 (실패 확인)**

```bash
cd src/cobot1
python -m pytest test/test_webcam_checker.py -v
```

예상: `ImportError` (아직 파일 없음) 또는 import 성공 후 일부 실패.

- [ ] **Step 4: 테스트 재실행 (통과 확인)**

Step 1의 파일이 있으면:
```bash
python -m pytest test/test_webcam_checker.py -v
```

예상: `test_crop_roi_none_returns_original`, `test_crop_roi_applies_crop` PASS.
`test_count_circles_*`는 HoughCircles 파라미터에 따라 결과가 다를 수 있음 — 실패 시 파라미터 튜닝 후 재실행.

- [ ] **Step 5: `setup.py` entry point 추가**

`src/cobot1/setup.py`의 `console_scripts` 리스트에 추가:

```python
'webcam_checker_node = cobot1.webcam_checker_node:main',
```

결과:
```python
entry_points={
    'console_scripts': [
        'bridge_node = cobot1.bridge_node:main',
        'image_processor_node = cobot1.image_processor_node:main',
        'sequencer_node = cobot1.sequencer_node:main',
        'robot_controller_node = cobot1.robot_controller_node:main',
        'verify_node = cobot1.verify_node:main',
        'camera_node = cobot1.camera_node:main',
        'webcam_checker_node = cobot1.webcam_checker_node:main',
    ],
},
```

- [ ] **Step 6: 커밋**

```bash
git add src/cobot1/cobot1/webcam_checker_node.py src/cobot1/setup.py src/cobot1/test/test_webcam_checker.py
git commit -m "feat: WebcamCheckerNode 구현 및 entry point 등록"
```

---

## Task 3: robot_controller_node.py 수정

**Files:**
- Modify: `src/cobot1/cobot1/robot_controller_node.py`

**Interfaces:**
- Consumes: `CheckBlock.srv` (Task 1) — `CheckBlock.Request.block_type (uint8)`, `CheckBlock.Response.passed (bool)`
- Produces: `RobotControllerNode._check_block(block_type_str: str) -> None` (raises RuntimeError on fail)

- [ ] **Step 1: `RobotControllerNode.__init__`에 서비스 클라이언트 추가**

`robot_controller_node.py`의 `RobotControllerNode.__init__` 내, `self.get_logger().info(f"Action Server 시작: {ACTION_NAME}")` 바로 앞에 추가:

```python
from cobot1_interfaces.srv import CheckBlock as _CheckBlock
self._block_checker_client = self.create_client(_CheckBlock, '/webcam/check_block')
```

- [ ] **Step 2: `_check_block` 메서드 추가**

`RobotControllerNode` 클래스 내, `cancel_callback` 메서드 바로 앞에 추가:

```python
def _check_block(self, block_type_str: str) -> None:
    """
    웹캠 블록 검사 서비스를 동기적으로 호출한다.
    노드가 이미 MultiThreadedExecutor에서 스핀 중이므로
    threading.Event로 future 완료를 기다린다.
    passed=False이면 RuntimeError를 발생시켜 액션을 abort 처리한다.
    """
    import threading as _threading
    from cobot1_interfaces.srv import CheckBlock as _CheckBlock

    _type_map = {"2x2": 1, "3x2": 2}
    req = _CheckBlock.Request()
    req.block_type = _type_map[block_type_str]

    future = self._block_checker_client.call_async(req)
    done = _threading.Event()
    future.add_done_callback(lambda _: done.set())
    done.wait(timeout=10.0)

    res = future.result()
    if res is None:
        raise RuntimeError("웹캠 서비스 응답 없음 (timeout)")
    if not res.passed:
        raise RuntimeError(
            f"블록 감지 실패 ({res.detected_circles}개 검출): {res.message}"
        )
```

- [ ] **Step 3: `KITTING_PRE_GRIP_WAIT` 단계 교체**

`pick_from_kitting_tray` 내 아래 두 줄을:

```python
        # 4. Pick Pose 도달 후 0.3초 정지
        _step("KITTING_PRE_GRIP_WAIT")
        self._wait(PICK_PRE_GRIP_WAIT_SEC)
```

다음으로 교체:

```python
        # 4. Pick Pose 도달 후 웹캠으로 블록 존재 확인
        _step("KITTING_PRE_GRIP_WAIT")
        self._node._check_block(task.block_type_str)
```

- [ ] **Step 4: 변경 결과 확인**

`robot_controller_node.py`에서 아래 두 부분이 올바른지 확인:

1. `__init__` 내 클라이언트 생성:
```python
from cobot1_interfaces.srv import CheckBlock as _CheckBlock
self._block_checker_client = self.create_client(_CheckBlock, '/webcam/check_block')
```

2. `pick_from_kitting_tray` 내:
```python
_step("KITTING_PRE_GRIP_WAIT")
self._node._check_block(task.block_type_str)
```

3. `_check_block` 메서드가 클래스 내에 존재하는지 확인.

- [ ] **Step 5: 커밋**

```bash
git add src/cobot1/cobot1/robot_controller_node.py
git commit -m "feat: 블록 집기 전 웹캠 검사 서비스 호출 추가"
```

---

## Task 4: 런치 파일 등록

**Files:**
- Modify: `src/cobot1/launch/assembly.launch.py`

**Interfaces:**
- Consumes: `webcam_checker_node` entry point (Task 2)

- [ ] **Step 1: `assembly.launch.py`에 노드 추가**

`src/cobot1/launch/assembly.launch.py`의 `LaunchDescription` 리스트에 추가:

```python
from launch import LaunchDescription
from launch_ros.actions import Node


def generate_launch_description():
    return LaunchDescription([
        Node(
            package='cobot1',
            executable='bridge_node',
            name='bridge',
            output='screen',
        ),
        Node(
            package='cobot1',
            executable='image_processor_node',
            name='image_processor',
            output='screen',
        ),
        Node(
            package='cobot1',
            executable='sequencer_node',
            name='sequencer',
            output='screen',
        ),
        Node(
            package='cobot1',
            executable='robot_controller_node',
            name='robot_controller',
            output='screen',
        ),
        Node(
            package='cobot1',
            executable='verify_node',
            name='verify',
            output='screen',
        ),
        Node(
            package='cobot1',
            executable='camera_node',
            name='camera',
            output='screen',
        ),
        Node(
            package='cobot1',
            executable='webcam_checker_node',
            name='webcam_checker',
            output='screen',
            parameters=[{'video_device': '/dev/video1'}],
        ),
    ])
```

- [ ] **Step 2: 빌드 요청**

사용자에게 빌드를 요청한다:
```
colcon build --packages-select cobot1
source install/setup.bash
```

- [ ] **Step 3: 노드 단독 실행 확인**

터미널에서 노드만 단독으로 실행해 서비스가 올라오는지 확인:
```bash
ros2 run cobot1 webcam_checker_node
```

별도 터미널에서:
```bash
ros2 service list | grep webcam
```

예상 출력:
```
/webcam/check_block
```

- [ ] **Step 4: 커밋**

```bash
git add src/cobot1/launch/assembly.launch.py
git commit -m "feat: 런치 파일에 webcam_checker_node 등록"
```

---

## 미결 사항 (구현 후 실측 튜닝)

- `BLOCK_ROI`: 실제 카메라 앵글에서 픽셀 좌표 측정 후 `webcam_checker_node.py`의 `BLOCK_ROI` 딕셔너리 채울 것
- `HOUGH_*` 파라미터: 실측 이미지로 `cv2.HoughCircles` 파라미터 튜닝
- `/dev/video1`: 실제 장치 경로 확인 (`ls /dev/video*`)

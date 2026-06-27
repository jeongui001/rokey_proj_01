# 웹캠 블록 검사 노드 설계

## 목적

키팅 트레이에서 블록을 집기 직전, 웹캠으로 블록 존재 여부를 확인한다.
블록이 없거나 불충분하면 로봇을 일시정지시켜 작업 실패를 예방한다.

## 트리거 타이밍

`robot_controller_node.py`의 `pick_from_kitting_tray` 내 `KITTING_PRE_GRIP_WAIT` 단계.
기존 `self._wait(0.3)` 대신 웹캠 서비스 호출로 교체한다.
로봇이 pick_pose에 도달한 상태이므로 카메라 앵글이 블록을 직접 내려다본다.

## 인터페이스

### 새 서비스 파일

`src/cobot1_interfaces/srv/CheckBlock.srv`

```
uint8 block_type   # 1=2x2  2=3x2
---
bool passed
uint8 detected_circles
string message
```

### CMakeLists.txt 변경

`cobot1_interfaces/CMakeLists.txt`의 `rosidl_generate_interfaces`에
`"srv/CheckBlock.srv"` 한 줄 추가.

## 신규 노드: WebcamCheckerNode

**파일:** `src/cobot1/cobot1/webcam_checker_node.py`

### 파라미터

| 파라미터 | 기본값 | 설명 |
|---|---|---|
| `video_device` | `/dev/video1` | 웹캠 장치 경로 |

### 서비스

`/webcam/check_block` (CheckBlock.srv)

### 처리 흐름

1. `cv2.VideoCapture`로 현재 프레임 단일 캡처
2. `BLOCK_ROI[block_type]`에서 크롭 영역 조회
   - 값이 `None`이면 전체 이미지 사용 (좌표 미확정 상태)
3. GrayScale 변환 → GaussianBlur 전처리
4. `cv2.HoughCircles` 실행
5. 검출 원 개수 판정
   - `block_type=1` (2x2): 원 4개 이상 → passed=True
   - `block_type=2` (3x2): 원 6개 이상 → passed=True
   - 미달: passed=False → `/robot/pause` 서비스 호출 (`data=True`)
6. 응답 반환

### ROI 플레이스홀더

```python
# 픽셀 좌표 (x, y, w, h). None이면 전체 이미지 사용. 실측 후 채울 것.
BLOCK_ROI: dict[int, tuple[int, int, int, int] | None] = {
    1: None,  # 2x2 — TODO
    2: None,  # 3x2 — TODO
}
```

## robot_controller_node.py 변경

### 변경 범위

`pick_from_kitting_tray` 내 `KITTING_PRE_GRIP_WAIT` 단계만 수정.

**Before:**
```python
_step("KITTING_PRE_GRIP_WAIT")
self._wait(PICK_PRE_GRIP_WAIT_SEC)
```

**After:**
```python
_step("KITTING_PRE_GRIP_WAIT")
self._node._check_block(task.block_type_str)
```

### RobotControllerNode에 추가

`__init__`에서 서비스 클라이언트 생성:
```python
from cobot1_interfaces.srv import CheckBlock
self._block_checker_client = self.create_client(CheckBlock, '/webcam/check_block')
```

`_check_block` 메서드:
```python
def _check_block(self, block_type_str: str) -> None:
    import threading
    from cobot1_interfaces.srv import CheckBlock
    type_map = {"2x2": 1, "3x2": 2}
    req = CheckBlock.Request()
    req.block_type = type_map[block_type_str]
    future = self._block_checker_client.call_async(req)
    done = threading.Event()
    future.add_done_callback(lambda _: done.set())
    done.wait(timeout=10.0)
    res = future.result()
    if res is None:
        raise RuntimeError("웹캠 서비스 응답 없음")
    if not res.passed:
        raise RuntimeError(f"블록 감지 실패 ({res.detected_circles}개 검출): {res.message}")
```

> `rclpy.spin_until_future_complete`는 이미 스핀 중인 노드에서 호출 시 데드락 위험이 있다.
> 대신 `threading.Event`로 done callback을 기다리는 방식을 사용한다.

`passed=False`이면 예외 → `execute_callback`의 `except` 블록이 abort 처리.
웹캠 노드 내부에서는 `/robot/pause`를 직접 호출해 로봇도 정지.

## 런치 및 패키지 등록

### assembly.launch.py

```python
Node(
    package='cobot1',
    executable='webcam_checker_node',
    name='webcam_checker',
    output='screen',
    parameters=[{'video_device': '/dev/video1'}],
),
```

### setup.py entry point 추가

```python
'webcam_checker_node = cobot1.webcam_checker_node:main',
```

## 미결 사항

- `BLOCK_ROI` 좌표: 실측 후 채울 것
- HoughCircles 파라미터(dp, minDist, param1, param2, minRadius, maxRadius): 실측 튜닝 필요
- `/dev/video1` 장치 경로: 실제 환경에서 확인 필요

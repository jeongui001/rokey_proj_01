"""
spiral_detach_discard.py
블록 결합 해제(move_spiral 3회) 및 폐기 바구니 배출 실행 모듈.

robot_controller_node.py의 RobotMotionController와 함께 사용한다.
순환 import를 피하기 위해 CartesianPose를 이 파일에 독립적으로 정의한다.
"""

from __future__ import annotations

import time
from dataclasses import dataclass
from typing import Callable, List, Optional, Tuple

import DR_init

# ─────────────────────────────────────────────────────────────────────────────
# 1. 로봇 기본 설정
# ─────────────────────────────────────────────────────────────────────────────
ROBOT_ID = "dsr01"
ROBOT_MODEL = "m0609"

DR_init.__dsr__id = ROBOT_ID
DR_init.__dsr__model = ROBOT_MODEL

# ─────────────────────────────────────────────────────────────────────────────
# 2. 조정 가능한 상수
# ─────────────────────────────────────────────────────────────────────────────

JOINT_VELOCITY = 60.0
JOINT_ACCELERATION = 60.0

LINEAR_VELOCITY: List[float] = [60.0, 60.0]
LINEAR_ACCELERATION: List[float] = [60.0, 60.0]

HOME_JOINT_DEG = [0.0, 0.0, 90.0, 0.0, 90.0, 0.0]

RG2_FORCE_VALUE = 400
RG2_STATUS_POLL_SEC = 0.1
RG2_SETTLE_WAIT_SEC = 0.2

MOTION_SETTLE_WAIT_SEC = 0.2

DETACH_APPROACH_HEIGHT_MM = 50.0
DETACH_LIFT_HEIGHT_MM = 100.0
BASKET_APPROACH_HEIGHT_MM = 80.0

# 결합 해제 후 바스켓 이동 전 안전 고도 (mm)
DETACH_TRANSIT_Z_MM = 270.0

# 수평·상승 이동 배속 파라미터
TRAVERSE_LINEAR_VELOCITY: List[float] = [240.0, 240.0]
TRAVERSE_LINEAR_ACCELERATION: List[float] = [120.0, 120.0]

SPIRAL_TRIALS: Tuple[Tuple[float, float, float], ...] = (
    (1.0, 0.8, 1.0),
    (1.0, 0.8, 1.0),
    (1.0, 0.8, 1.0),
)

# ─────────────────────────────────────────────────────────────────────────────
# 3. RG2 Modbus TCP 접속 설정
# ─────────────────────────────────────────────────────────────────────────────
GRIPPER_NAME = "rg2"
TOOLCHANGER_IP = "192.168.1.1"
TOOLCHANGER_PORT = "502"

# ─────────────────────────────────────────────────────────────────────────────
# 4. Cartesian Pose 데이터 모델 (순환 import 방지용 독립 정의)
# ─────────────────────────────────────────────────────────────────────────────

@dataclass(frozen=True)
class CartesianPose:
    x_mm: float
    y_mm: float
    z_mm: float
    a_deg: float
    b_deg: float
    c_deg: float


def _with_z(pose: CartesianPose, z_mm: float) -> CartesianPose:
    return CartesianPose(
        x_mm=pose.x_mm,
        y_mm=pose.y_mm,
        z_mm=z_mm,
        a_deg=pose.a_deg,
        b_deg=pose.b_deg,
        c_deg=pose.c_deg,
    )


def _add_z(pose: CartesianPose, offset_mm: float) -> CartesianPose:
    return _with_z(pose, pose.z_mm + offset_mm)


def _to_posx(pose: CartesianPose):
    from DR_common2 import posx
    return posx(
        pose.x_mm,
        pose.y_mm,
        pose.z_mm,
        pose.a_deg,
        pose.b_deg,
        pose.c_deg,
    )


# ─────────────────────────────────────────────────────────────────────────────
# 4.5. 폐기 바구니 Pose — 수치만 여기서 수정
# ─────────────────────────────────────────────────────────────────────────────
BASKET_POSE = CartesianPose(658.35, 282.22, 130.0, 90.0, -180.0, 90.0)


# ─────────────────────────────────────────────────────────────────────────────
# 5. 결합 해제 작업 데이터 모델
# ─────────────────────────────────────────────────────────────────────────────

@dataclass(frozen=True)
class DetachDiscardTask:
    task_id: str
    color: str
    detach_pose: CartesianPose
    basket_pose: CartesianPose
    pre_press: bool = False


# ─────────────────────────────────────────────────────────────────────────────
# 6. Spiral 결합 해제 함수
# ─────────────────────────────────────────────────────────────────────────────

def spiral_detach_only(
    log_info: Callable[[str], None],
    log_error: Callable[[str], None],
) -> bool:
    from DSR_ROBOT2 import move_spiral, wait, DR_AXIS_Z, DR_BASE

    for i in range(len(SPIRAL_TRIALS)):
        rev = SPIRAL_TRIALS[i][0]
        radius_mm = SPIRAL_TRIALS[i][1]
        z_motion_mm = SPIRAL_TRIALS[i][2]

        log_info(
            f"move_spiral 실행: trial={i + 1}/{len(SPIRAL_TRIALS)}, "
            f"rev={rev}, rmax={radius_mm}, lmax={z_motion_mm}"
        )

        ret = move_spiral(
            rev=rev,
            rmax=radius_mm,
            lmax=z_motion_mm,
            vel=[10.0, 10.0],
            acc=[10.0, 10.0],
            time=0.0,
            axis=DR_AXIS_Z,
            ref=DR_BASE,
        )

        if ret == -1:
            log_error(
                f"move_spiral 실패: trial={i}"
            )
            return False

        wait(0.2)

    log_info("spiral_detach_only 완료")
    return True


# ─────────────────────────────────────────────────────────────────────────────
# 7. 결합 해제 및 폐기 배출 실행 함수
# ─────────────────────────────────────────────────────────────────────────────

def execute_detach_discard(
    controller,
    task: DetachDiscardTask,
    step_callback: Optional[Callable[[str], None]] = None,
) -> None:
    logger = controller.logger

    def _step(name: str) -> None:
        logger.info(f"[{task.task_id}] 단계: {name}")
        if step_callback is not None:
            step_callback(name)

    from DSR_ROBOT2 import wait

    detach_approach_pose = _add_z(task.detach_pose, DETACH_APPROACH_HEIGHT_MM)
    basket_approach_pose = _add_z(task.basket_pose, BASKET_APPROACH_HEIGHT_MM)

    # 1. 블록 위 50mm로 고속 접근
    _step("DETACH_APPROACH")
    controller.move_linear(detach_approach_pose, "DETACH_APPROACH",
                           vel=TRAVERSE_LINEAR_VELOCITY, acc=TRAVERSE_LINEAR_ACCELERATION)

    # 1.5. 제거 예정 블록을 spiral 전에 눌러 결합 상태를 안정화
    if task.pre_press:
        _step("PREPRESS_GRIP")
        controller.rg2_grip()

        _step("PREPRESS_DESCEND")
        controller.force_press(task.detach_pose)

        _step("PREPRESS_LIFT")
        controller.move_linear(detach_approach_pose, "PREPRESS_LIFT",
                               vel=TRAVERSE_LINEAR_VELOCITY, acc=TRAVERSE_LINEAR_ACCELERATION)

        _step("PREPRESS_RELEASE")
        controller.rg2_release()

    # 2. 그리퍼 열기
    _step("RG2_OPEN")
    controller.rg2_release()

    # 3. Place했던 좌표 그대로 하강 → 동일 위치에서 파지
    _step("DETACH_DESCEND")
    controller.move_linear(task.detach_pose, "DETACH_DESCEND")

    # 4. 그리퍼 닫기
    _step("RG2_CLOSE")
    controller.rg2_grip()

    # 5. Spiral 결합 해제
    _step("SPIRAL_DETACH")
    success = spiral_detach_only(
        log_info=lambda msg: logger.info(msg),
        log_error=lambda msg: logger.error(msg),
    )

    if not success:
        raise RuntimeError(
            f"블록 결합 해제 실패: task_id={task.task_id}"
        )

    # 6. 블록 위 100mm까지 상승
    _step("DETACH_LIFT")
    detach_lift_pose = _add_z(task.detach_pose, DETACH_LIFT_HEIGHT_MM)
    controller.move_linear(detach_lift_pose, "DETACH_LIFT")

    # 7. 안전 고도까지 상승 (동기 — 자세 전환 전 완전 정지)
    _step("DETACH_TRANSIT")
    detach_transit_pose = CartesianPose(
        x_mm=task.detach_pose.x_mm,
        y_mm=task.detach_pose.y_mm,
        z_mm=DETACH_TRANSIT_Z_MM,
        a_deg=task.detach_pose.a_deg,
        b_deg=task.detach_pose.b_deg,
        c_deg=task.detach_pose.c_deg,
    )
    controller.move_linear(detach_transit_pose, "DETACH_TRANSIT",
                           vel=TRAVERSE_LINEAR_VELOCITY, acc=TRAVERSE_LINEAR_ACCELERATION)

    # 8. 바스켓 상부로 이동 (동기 — 자세 변경 포함)
    _step("BASKET_APPROACH")
    controller.move_linear(basket_approach_pose, "BASKET_APPROACH",
                           vel=TRAVERSE_LINEAR_VELOCITY, acc=TRAVERSE_LINEAR_ACCELERATION)

    # 9. 바스켓 위치로 하강
    _step("BASKET_DESCEND")
    controller.move_linear(task.basket_pose, "BASKET_DESCEND")

    # 10. 그리퍼 열어 블록 낙하 배출
    _step("RG2_OPEN")
    controller.rg2_release()

    # 11. 바스켓 상부로 복귀
    _step("BASKET_LIFT")
    controller.move_linear(basket_approach_pose, "BASKET_LIFT",
                           vel=TRAVERSE_LINEAR_VELOCITY, acc=TRAVERSE_LINEAR_ACCELERATION)
    wait(MOTION_SETTLE_WAIT_SEC)

    logger.info(
        f"[{task.task_id}] 결합 해제 및 폐기 완료 — color={task.color}"
    )

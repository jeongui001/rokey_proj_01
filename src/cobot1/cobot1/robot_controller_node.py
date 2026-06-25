"""
robot_controller_node.py
Doosan M0609 + OnRobot RG2 키팅 트레이 방식 Pick & Place 실행 모듈.
ROS2 Action Server(/execute_queue)를 통해 BlockTask[] Goal을 수신한다.

동작 방식:
  - Pick 위치는 color, block_type 기반 KITTING_TRAY_PROFILES에서 조회한다.
  - Place 위치는 task.y_position(Y)과 노드 파라미터(place_x_mm, place_z_mm)로 결정한다.
"""

from __future__ import annotations

import math
import time
from dataclasses import dataclass
from threading import Lock
from typing import Callable, List, Optional

import rclpy
from rclpy.action import ActionServer, CancelResponse, GoalResponse
from rclpy.callback_groups import ReentrantCallbackGroup
from rclpy.executors import MultiThreadedExecutor
from rclpy.node import Node
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
#    실제 로봇 환경에 맞게 이 구역의 값을 수정하라.
# ─────────────────────────────────────────────────────────────────────────────

# 홈 자세 관절 각도 (단위: 도)
HOME_JOINT_DEG = [
    0.0,   # J1 베이스
    0.0,   # J2 숄더
    90.0,  # J3 엘보
    0.0,   # J4 포암
    90.0,  # J5 리스트
    0.0,   # J6 툴
]

# 블록 적층 피치 계산용
BLOCK_HEIGHT_MM = 19.0
ASSEMBLY_CLEARANCE_MM = 0.5
STACK_PITCH_MM = BLOCK_HEIGHT_MM + ASSEMBLY_CLEARANCE_MM  # 19.5 mm

# 관절 이동 속도·가속도 (단위: %)
JOINT_VELOCITY = 60.0
JOINT_ACCELERATION = 60.0

# 일반 직선 이동 속도·가속도: [선속도(mm/s), 각속도(deg/s)]
LINEAR_VELOCITY: List[float] = [60.0, 60.0]
LINEAR_ACCELERATION: List[float] = [60.0, 60.0]

# Place 최종 하강 전용 저속 설정 — TODO: 실제 장비 값 입력
PLACE_LINEAR_VELOCITY: List[float] = [10.0, 10.0]
PLACE_LINEAR_ACCELERATION: List[float] = [10.0, 10.0]

# RG2 설정
RG2_FORCE_VALUE = 400       # 파지 힘 (단위: 1/10 N)
RG2_STATUS_POLL_SEC = 0.1   # Busy 폴링 주기 (초)
RG2_SETTLE_WAIT_SEC = 0.2   # 일반 RG2 동작 완료 후 안정화 대기 (초)

# 작업 사이 공통 이동 높이 — TODO: 실제 장비 값 입력 (충돌 없는 안전 높이)
TRANSFER_Z_MM = 300.0

# Pick 하강 완료 후 그립 전 대기 (초)
PICK_PRE_GRIP_WAIT_SEC = 0.3

# RG2 Close Busy 종료 후 추가 안정화 대기 (초)
PICK_POST_GRIP_WAIT_SEC = 0.5

# Place 해제 후 추가 대기 (초)
PLACE_RELEASE_WAIT_SEC = 0.2

# 정상 Tool 자세 — TODO: 실제 티칭 Pose의 정상 자세 A/B/C 값으로 수정
NORMAL_TOOL_A_DEG = 0.0
NORMAL_TOOL_B_DEG = 180.0
NORMAL_TOOL_C_DEG = 0.0

# Queue 이동 정책
MOVE_HOME_AT_QUEUE_START = True   # 큐 시작 전 홈 이동 여부
MOVE_HOME_AT_QUEUE_END = False    # 큐 완료 후 홈 이동 여부 (기본: TRANSFER_Z에서 대기)

# ─────────────────────────────────────────────────────────────────────────────
# 3. RG2 Modbus TCP 접속 설정
# ─────────────────────────────────────────────────────────────────────────────
GRIPPER_NAME = "rg2"
TOOLCHANGER_IP = "192.168.1.1"
TOOLCHANGER_PORT = "502"

# ─────────────────────────────────────────────────────────────────────────────
# 4. Action Server 설정
# ─────────────────────────────────────────────────────────────────────────────
ACTION_NAME = "/execute_queue"

# ─────────────────────────────────────────────────────────────────────────────
# 5. Cartesian Pose 데이터 모델
# ─────────────────────────────────────────────────────────────────────────────

@dataclass(frozen=True)
class CartesianPose:
    """로봇 TCP의 직교좌표 자세 (Base 좌표계 기준)."""
    x_mm: float
    y_mm: float
    z_mm: float
    a_deg: float  # Yaw  (Z축 회전)
    b_deg: float  # Pitch (Y축 회전)
    c_deg: float  # Roll  (X축 회전)


def with_z(pose: CartesianPose, z_mm: float) -> CartesianPose:
    """Z값만 바꾼 새 CartesianPose를 반환한다."""
    return CartesianPose(
        x_mm=pose.x_mm,
        y_mm=pose.y_mm,
        z_mm=z_mm,
        a_deg=pose.a_deg,
        b_deg=pose.b_deg,
        c_deg=pose.c_deg,
    )


def add_z(pose: CartesianPose, offset_mm: float) -> CartesianPose:
    """현재 Z에 offset을 더한 새 CartesianPose를 반환한다."""
    return with_z(pose, pose.z_mm + offset_mm)


def to_posx(pose: CartesianPose):
    """CartesianPose를 DSR SDK의 posx 객체로 변환한다."""
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
# 6. 키팅 트레이 프로파일 데이터 모델
# ─────────────────────────────────────────────────────────────────────────────

@dataclass(frozen=True)
class KittingTrayProfile:
    """
    색상·유형별 키팅 트레이 Pick 설정.
    파일 상단의 KITTING_TRAY_PROFILES에서 사용자가 직접 수정한다.
    """
    pick_x_mm: float         # 트레이 블록의 Base X 좌표 (mm)
    pick_y_mm: float         # 트레이 블록의 Base Y 좌표 (mm)
    pick_z_mm: float         # 그리퍼가 블록을 집는 Base Z 좌표 (mm)
    tilted_a_deg: float      # 트레이 접근 시 Tool A 각도 (기울기 보정용)
    tool_retract_z_mm: float # Tool 기준 Z축 인출 거리 (mm, 부호는 장비 확인 후 결정)


# ─────────────────────────────────────────────────────────────────────────────
# 7. 색상·유형별 키팅 트레이 설정
#    키: (color, block_type). block_type은 BlockTask.block_type (uint8) 과 일치한다.
#    실제 장비에서 티칭한 값을 TODO 항목에 입력하라.
# ─────────────────────────────────────────────────────────────────────────────

KITTING_TRAY_PROFILES = {
    "red": {
        1: KittingTrayProfile(
            pick_x_mm=0.0,          # TODO: 빨간 블록 트레이 X (mm)
            pick_y_mm=0.0,          # TODO: 빨간 블록 트레이 Y (mm)
            pick_z_mm=0.0,          # TODO: 빨간 블록 Pick Z (mm)
            tilted_a_deg=0.0,       # TODO: 빨간 블록 트레이용 Tool A (deg)
            tool_retract_z_mm=50.0, # TODO: Tool Z 인출 거리 (mm, 부호 장비 확인)
        ),
    },
    "blue": {
        1: KittingTrayProfile(
            pick_x_mm=0.0,
            pick_y_mm=0.0,
            pick_z_mm=0.0,
            tilted_a_deg=0.0,
            tool_retract_z_mm=50.0,
        ),
    },
    "green": {
        1: KittingTrayProfile(
            pick_x_mm=0.0,
            pick_y_mm=0.0,
            pick_z_mm=0.0,
            tilted_a_deg=0.0,
            tool_retract_z_mm=50.0,
        ),
    },
    "yellow": {
        1: KittingTrayProfile(
            pick_x_mm=0.0,
            pick_y_mm=0.0,
            pick_z_mm=0.0,
            tilted_a_deg=0.0,
            tool_retract_z_mm=50.0,
        ),
    },
}


def get_kitting_profile(color: str, block_type: int) -> KittingTrayProfile:
    """
    색상·block_type으로 KittingTrayProfile을 조회한다.
    미등록 color 또는 block_type이면 ValueError를 발생시킨다.
    """
    color_entry = KITTING_TRAY_PROFILES.get(color)
    if color_entry is None:
        raise ValueError(
            f"키팅 트레이 설정 없음: color={color}, block_type={block_type}"
        )
    profile = color_entry.get(block_type)
    if profile is None:
        raise ValueError(
            f"키팅 트레이 설정 없음: color={color}, block_type={block_type}"
        )
    return profile


# ─────────────────────────────────────────────────────────────────────────────
# 8. Pick & Place 작업 데이터 모델
# ─────────────────────────────────────────────────────────────────────────────

@dataclass(frozen=True)
class PickPlaceTask:
    """
    단일 키팅 트레이 Pick & Place 작업 파라미터.
    BlockTask (color, block_type, y_position) 에서 변환하여 생성한다.
    """
    color: str
    block_type: int              # BlockTask.block_type (uint8)
    base_place_pose: CartesianPose  # Place 기준 좌표 (y_position + 노드 파라미터로 계산)
    stack_index: int = 0         # 현재 인터페이스에 stack_index 없음 — 기본 0


# ─────────────────────────────────────────────────────────────────────────────
# 9. RobotMotionController 클래스
# ─────────────────────────────────────────────────────────────────────────────

class RobotMotionController:
    """
    로봇 관절·직선 이동 및 그리퍼 제어를 캡슐화한다.
    키팅 트레이 Pick & Place의 단계별 함수를 제공한다.
    """

    def __init__(self, node: Node) -> None:
        self._node = node
        self._logger = node.get_logger()

        # DR_init.__dsr__node 설정 후에 SDK 모듈을 임포트해야 하므로 지연 바인딩
        from DSR_ROBOT2 import (
            movej,
            movel,
            wait,
            mwait,
            DR_BASE,
            DR_TOOL,
            DR_MV_MOD_REL,
            get_current_posx,
        )
        from DR_common2 import posj

        self._movej = movej
        self._movel = movel
        self._wait = wait
        self._mwait = mwait
        self._DR_BASE = DR_BASE
        self._DR_TOOL = DR_TOOL
        self._DR_MV_MOD_REL = DR_MV_MOD_REL
        self._get_current_posx = get_current_posx
        self._posj = posj

        from pick_and_place_text.onrobot import RG
        self.gripper = RG(
            GRIPPER_NAME,
            TOOLCHANGER_IP,
            TOOLCHANGER_PORT,
        )

        self._logger.info("RobotMotionController 초기화 완료")

    @property
    def logger(self):
        """외부 모듈이 동일한 로거를 사용할 수 있도록 노출."""
        return self._logger

    # ── 기본 이동 함수 ────────────────────────────────────────────────────────

    def move_home(self) -> None:
        """관절 공간 이동으로 홈 자세로 복귀한다."""
        self._logger.info("홈 자세로 이동")
        ret = self._movej(
            self._posj(*HOME_JOINT_DEG),
            vel=JOINT_VELOCITY,
            acc=JOINT_ACCELERATION,
        )
        if ret == -1:
            raise RuntimeError("movej 홈 이동 실패")
        self._mwait()

    def move_linear(
        self,
        pose: CartesianPose,
        step_name: str,
        *,
        vel: Optional[List[float]] = None,
        acc: Optional[List[float]] = None,
    ) -> None:
        """
        TCP를 현재 위치에서 pose까지 Base 좌표계 기준 직선으로 이동한다.
        vel/acc를 지정하면 해당 속도를 사용하고, 지정하지 않으면 LINEAR_VELOCITY/ACCELERATION을 사용한다.
        """
        _vel = vel if vel is not None else LINEAR_VELOCITY
        _acc = acc if acc is not None else LINEAR_ACCELERATION

        self._logger.info(
            f"직선 이동: step={step_name}  "
            f"x={pose.x_mm:.2f}  y={pose.y_mm:.2f}  z={pose.z_mm:.2f}  "
            f"a={pose.a_deg:.2f}"
        )
        ret = self._movel(
            to_posx(pose),
            vel=_vel,
            acc=_acc,
            ref=self._DR_BASE,
        )
        if ret == -1:
            raise RuntimeError(
                f"movel 실패: step={step_name}, pose={pose}"
            )
        self._mwait()

    def move_relative_tool_z(
        self,
        distance_mm: float,
        step_name: str,
    ) -> None:
        """
        현재 Tool 좌표계의 Z축 방향으로 distance_mm만큼 상대 이동한다.
        기울어진 Tool 자세 상태에서 트레이 방향으로 인출할 때 사용한다.
        distance_mm의 부호(양수/음수)는 실제 장비의 Tool Z 방향을 확인하라.
        """
        if distance_mm == 0:
            raise ValueError(
                f"tool_retract_z_mm가 0입니다: step={step_name}"
            )

        from DR_common2 import posx as _posx

        self._logger.info(
            f"Tool Z 상대 이동: step={step_name}, distance={distance_mm:.2f} mm"
        )
        ret = self._movel(
            _posx(0.0, 0.0, distance_mm, 0.0, 0.0, 0.0),
            vel=LINEAR_VELOCITY,
            acc=LINEAR_ACCELERATION,
            ref=self._DR_TOOL,
            mod=self._DR_MV_MOD_REL,
        )
        if ret == -1:
            raise RuntimeError(
                f"Tool Z 상대 인출 실패: distance_mm={distance_mm}"
            )
        self._mwait()

    def get_current_cartesian_pose(self) -> CartesianPose:
        """
        현재 TCP Pose를 Base 좌표계 기준으로 조회한다.
        Tool 기준 상대이동 후 실제 Base 좌표를 얻을 때 사용한다.
        get_current_posx()는 (posx_object, solution_space) 튜플을 반환한다.
        """
        result = self._get_current_posx(ref=self._DR_BASE)

        if result is None:
            raise RuntimeError("현재 TCP Pose 조회 실패: 반환값이 None")

        pos, _ = result

        if pos is None:
            raise RuntimeError("현재 TCP Pose 조회 실패: pos가 None")

        return CartesianPose(
            x_mm=float(pos[0]),
            y_mm=float(pos[1]),
            z_mm=float(pos[2]),
            a_deg=float(pos[3]),
            b_deg=float(pos[4]),
            c_deg=float(pos[5]),
        )

    # ── RG2 그리퍼 제어 ───────────────────────────────────────────────────────

    def wait_rg2_complete(self, settle_sec: float) -> None:
        """
        RG2 Busy가 끝날 때까지 폴링하고, 종료 후 settle_sec만큼 추가 대기한다.
        settle_sec 값은 호출처에서 명시적으로 전달한다.
        """
        while self.gripper.get_status()[0]:
            time.sleep(RG2_STATUS_POLL_SEC)
        self._wait(settle_sec)

    def rg2_open_and_wait(self) -> None:
        """그리퍼를 열고 완전히 열릴 때까지 대기한다."""
        self._logger.info("RG2 열기")
        self.gripper.open_gripper(force_val=RG2_FORCE_VALUE)
        self.wait_rg2_complete(settle_sec=RG2_SETTLE_WAIT_SEC)

    def rg2_close_and_wait(self) -> None:
        """그리퍼를 닫고 파지가 완료될 때까지 대기한다 (표준 0.2초 settle)."""
        self._logger.info("RG2 닫기")
        self.gripper.close_gripper(force_val=RG2_FORCE_VALUE)
        self.wait_rg2_complete(settle_sec=RG2_SETTLE_WAIT_SEC)

    # ── 키팅 트레이 Pick 시퀀스 ───────────────────────────────────────────────

    def pick_from_kitting_tray(
        self,
        task: PickPlaceTask,
        step_callback: Optional[Callable[[str], None]] = None,
    ) -> None:
        """
        키팅 트레이에서 블록을 집는 전체 시퀀스 (과정 12-1 ~ 12-7).

        단계 순서:
          KITTING_XY_MOVE      — 트레이 X/Y로 이동 (TRANSFER_Z, 정상 A)
          KITTING_TILT_A       — 트레이용 A로 변경 (X/Y/Z 유지)
          KITTING_PICK_DESCEND — 블록 Pick Z까지 하강
          KITTING_PRE_GRIP_WAIT — 0.3초 정지
          KITTING_GRIP         — RG2 Close + Busy 폴링
          KITTING_POST_GRIP_WAIT — 0.5초 추가 대기
          KITTING_TOOL_Z_RETRACT — Tool Z 기준 상대 인출
          KITTING_NORMALIZE_A  — 현재 XYZ 유지, A만 정상값 복구
          KITTING_TRANSFER_Z   — 공통 이동 높이로 상승
        """
        profile = get_kitting_profile(task.color, task.block_type)

        if profile.tool_retract_z_mm == 0:
            raise ValueError(
                f"tool_retract_z_mm가 0입니다: color={task.color}, block_type={task.block_type}"
            )

        def _step(name: str) -> None:
            self._logger.info(f"[color={task.color}] 단계: {name}")
            if step_callback is not None:
                step_callback(name)

        # 12-1. 트레이 X/Y로 이동 (TRANSFER_Z 높이, 정상 Tool 방향 유지)
        _step("KITTING_XY_MOVE")
        xy_transfer_pose = CartesianPose(
            x_mm=profile.pick_x_mm,
            y_mm=profile.pick_y_mm,
            z_mm=TRANSFER_Z_MM,
            a_deg=NORMAL_TOOL_A_DEG,
            b_deg=NORMAL_TOOL_B_DEG,
            c_deg=NORMAL_TOOL_C_DEG,
        )
        self.move_linear(xy_transfer_pose, "KITTING_XY_MOVE")

        # 12-2. A만 트레이용 값으로 변경 (X/Y/Z/B/C 유지)
        _step("KITTING_TILT_A")
        tilted_transfer_pose = CartesianPose(
            x_mm=profile.pick_x_mm,
            y_mm=profile.pick_y_mm,
            z_mm=TRANSFER_Z_MM,
            a_deg=profile.tilted_a_deg,
            b_deg=NORMAL_TOOL_B_DEG,
            c_deg=NORMAL_TOOL_C_DEG,
        )
        self.move_linear(tilted_transfer_pose, "KITTING_TILT_A")

        # 12-3. 기울어진 A를 유지한 채 Pick Z까지 Base Z 기준 하강
        _step("KITTING_PICK_DESCEND")
        pick_descend_pose = CartesianPose(
            x_mm=profile.pick_x_mm,
            y_mm=profile.pick_y_mm,
            z_mm=profile.pick_z_mm,
            a_deg=profile.tilted_a_deg,
            b_deg=NORMAL_TOOL_B_DEG,
            c_deg=NORMAL_TOOL_C_DEG,
        )
        self.move_linear(pick_descend_pose, "KITTING_PICK_DESCEND")

        # 하강 완료 후 그립 전 정지 (0.3초)
        _step("KITTING_PRE_GRIP_WAIT")
        self._wait(PICK_PRE_GRIP_WAIT_SEC)

        # 12-4. RG2 Close — Busy 폴링은 수동으로 처리하여 단계 로그 분리
        _step("KITTING_GRIP")
        self._logger.info("RG2 키팅 파지 닫기")
        self.gripper.close_gripper(force_val=RG2_FORCE_VALUE)
        while self.gripper.get_status()[0]:
            time.sleep(RG2_STATUS_POLL_SEC)

        # Busy 종료 후 0.5초 추가 대기 (파지 안정화)
        _step("KITTING_POST_GRIP_WAIT")
        self._wait(PICK_POST_GRIP_WAIT_SEC)

        # 12-5. Tool Z 기준 상대 인출 (기울어진 A 유지)
        _step("KITTING_TOOL_Z_RETRACT")
        self.move_relative_tool_z(
            profile.tool_retract_z_mm,
            "KITTING_TOOL_Z_RETRACT",
        )

        # 12-6. 인출 후 현재 Base TCP Pose 조회 → A만 정상값으로 복구
        # Tool 기준 이동 이후 Base X/Y/Z가 변하므로 실제 Pose를 조회해야 함
        _step("KITTING_NORMALIZE_A")
        current_pose = self.get_current_cartesian_pose()
        normalized_pose = CartesianPose(
            x_mm=current_pose.x_mm,
            y_mm=current_pose.y_mm,
            z_mm=current_pose.z_mm,
            a_deg=NORMAL_TOOL_A_DEG,
            b_deg=NORMAL_TOOL_B_DEG,
            c_deg=NORMAL_TOOL_C_DEG,
        )
        self.move_linear(normalized_pose, "KITTING_NORMALIZE_A")

        # 12-7. 공통 이동 높이(TRANSFER_Z_MM)로 상승
        # NORMALIZE_A 완료 후 위치는 normalized_pose이므로 그 Z와 비교
        _step("KITTING_TRANSFER_Z")
        if normalized_pose.z_mm < TRANSFER_Z_MM:
            transfer_pose = CartesianPose(
                x_mm=normalized_pose.x_mm,
                y_mm=normalized_pose.y_mm,
                z_mm=TRANSFER_Z_MM,
                a_deg=NORMAL_TOOL_A_DEG,
                b_deg=NORMAL_TOOL_B_DEG,
                c_deg=NORMAL_TOOL_C_DEG,
            )
            self.move_linear(transfer_pose, "KITTING_TRANSFER_Z")
        else:
            self._logger.info(
                f"[color={task.color}] KITTING_TRANSFER_Z: 이미 이동 높이 이상 "
                f"(z={normalized_pose.z_mm:.1f} mm ≥ {TRANSFER_Z_MM:.1f} mm), 스킵"
            )

        self._logger.info(
            f"[color={task.color}] 키팅 Pick 완료"
        )

    # ── Place 시퀀스 ─────────────────────────────────────────────────────────

    def place_block_at_target(
        self,
        task: PickPlaceTask,
        step_callback: Optional[Callable[[str], None]] = None,
    ) -> None:
        """
        base_place_pose 위치에 블록을 배치하는 시퀀스 (과정 13-1 ~ 13-4).

        단계 순서:
          TARGET_XY_MOVE  — 목표 X/Y로 이동 (TRANSFER_Z, 정상 Tool 방향)
          PLACE_DESCEND   — 저속으로 최종 조립 Z까지 하강
          PLACE_RELEASE   — RG2 Open (블록 해제)
          RETURN_TRANSFER_Z — TRANSFER_Z로 복귀
        """
        def _step(name: str) -> None:
            self._logger.info(f"[color={task.color}] 단계: {name}")
            if step_callback is not None:
                step_callback(name)

        # stack_index 기반 실제 배치 Z 계산
        actual_place_z = (
            task.base_place_pose.z_mm
            + task.stack_index * STACK_PITCH_MM
        )

        # 13-1. 공통 이동 높이에서 목표 X/Y로 이동
        _step("TARGET_XY_MOVE")
        target_xy_pose = CartesianPose(
            x_mm=task.base_place_pose.x_mm,
            y_mm=task.base_place_pose.y_mm,
            z_mm=TRANSFER_Z_MM,
            a_deg=NORMAL_TOOL_A_DEG,
            b_deg=NORMAL_TOOL_B_DEG,
            c_deg=NORMAL_TOOL_C_DEG,
        )
        self.move_linear(target_xy_pose, "TARGET_XY_MOVE")

        # 13-2. 저속으로 최종 조립 Z까지 하강 (위치 제어, 힘 제어 없음)
        _step("PLACE_DESCEND")
        place_pose = CartesianPose(
            x_mm=task.base_place_pose.x_mm,
            y_mm=task.base_place_pose.y_mm,
            z_mm=actual_place_z,
            a_deg=NORMAL_TOOL_A_DEG,
            b_deg=NORMAL_TOOL_B_DEG,
            c_deg=NORMAL_TOOL_C_DEG,
        )
        self.move_linear(
            place_pose,
            "PLACE_DESCEND",
            vel=PLACE_LINEAR_VELOCITY,
            acc=PLACE_LINEAR_ACCELERATION,
        )

        # 13-3. RG2 열어 블록 해제
        _step("PLACE_RELEASE")
        self._logger.info("RG2 열기 (배치 해제)")
        self.gripper.open_gripper(force_val=RG2_FORCE_VALUE)
        self.wait_rg2_complete(settle_sec=PLACE_RELEASE_WAIT_SEC)

        # 13-4. TRANSFER_Z까지 복귀 (다음 키팅 Pick을 위한 대기 높이)
        _step("RETURN_TRANSFER_Z")
        return_pose = CartesianPose(
            x_mm=task.base_place_pose.x_mm,
            y_mm=task.base_place_pose.y_mm,
            z_mm=TRANSFER_Z_MM,
            a_deg=NORMAL_TOOL_A_DEG,
            b_deg=NORMAL_TOOL_B_DEG,
            c_deg=NORMAL_TOOL_C_DEG,
        )
        self.move_linear(return_pose, "RETURN_TRANSFER_Z")

        self._logger.info(
            f"[color={task.color}] Place 완료 — "
            f"block_type={task.block_type}, "
            f"stack_index={task.stack_index}, "
            f"place_z={actual_place_z:.2f} mm"
        )

    # ── 대표 Pick & Place 함수 ────────────────────────────────────────────────

    def execute_pick_place(
        self,
        task: PickPlaceTask,
        step_callback: Optional[Callable[[str], None]] = None,
    ) -> None:
        """
        키팅 트레이 방식 전체 Pick & Place 시퀀스를 실행한다.
        pick_from_kitting_tray → place_block_at_target 순서로 호출한다.
        """
        self.pick_from_kitting_tray(task, step_callback=step_callback)
        self.place_block_at_target(task, step_callback=step_callback)


# ─────────────────────────────────────────────────────────────────────────────
# 10. RobotControllerNode — Action Server 통합
# ─────────────────────────────────────────────────────────────────────────────

class RobotControllerNode(Node):
    """
    ROS2 Action Server(/execute_queue)를 제공하는 메인 노드.
    BlockTask[] Goal을 수신하여 키팅 트레이 방식 Pick & Place를 실행한다.
    """

    def __init__(self) -> None:
        super().__init__("robot_controller")

        DR_init.__dsr__node = self

        # Place 위치 파라미터 (Y는 BlockTask.y_position에서 수신)
        self.declare_parameter('place_x_mm', 0.0)   # TODO: 실제 Place 기준 X 좌표 (mm)
        self.declare_parameter('place_z_mm', 0.0)   # TODO: 실제 Place 기준 Z 좌표 (mm)

        self._busy_lock = Lock()
        self._busy = False

        # ReentrantCallbackGroup: execute 스레드 실행 중에도 goal/cancel 처리 가능
        self._action_callback_group = ReentrantCallbackGroup()
        self._motion_controller = RobotMotionController(self)

        from cobot1_interfaces.action import Assembly
        self._action_server = ActionServer(
            self,
            Assembly,
            ACTION_NAME,
            execute_callback=self.execute_callback,
            goal_callback=self.goal_callback,
            cancel_callback=self.cancel_callback,
            callback_group=self._action_callback_group,
        )

        self.get_logger().info(f"Action Server 시작: {ACTION_NAME}")

    def cancel_callback(self, _goal_handle) -> CancelResponse:
        """취소 요청을 항상 수락한다. 실제 중단은 execute_callback 루프에서 처리."""
        self.get_logger().info("액션 취소 요청 수신")
        return CancelResponse.ACCEPT

    def goal_callback(self, goal_request) -> GoalResponse:
        """
        Goal 유효성 검사. 아래 조건 중 하나라도 해당하면 REJECT:
          - 이미 다른 큐가 실행 중
          - tasks 배열이 비어있음
          - color가 빈 문자열인 task 포함
          - y_position에 NaN/Inf 포함
        """
        with self._busy_lock:
            if self._busy:
                self.get_logger().warn("이미 Queue 실행 중 — Goal 거부")
                return GoalResponse.REJECT

            tasks = goal_request.tasks
            if not tasks:
                self.get_logger().warn("tasks가 비어있음 — Goal 거부")
                return GoalResponse.REJECT

            for t in tasks:
                if not t.color:
                    self.get_logger().warn("color가 비어있는 task 포함 — Goal 거부")
                    return GoalResponse.REJECT

                if math.isnan(t.y_position) or math.isinf(t.y_position):
                    self.get_logger().warn(
                        f"y_position에 NaN/Inf 포함: color={t.color} — Goal 거부"
                    )
                    return GoalResponse.REJECT

            self._busy = True
            return GoalResponse.ACCEPT

    def publish_feedback(
        self,
        goal_handle,
        *,
        current_index: int,
    ) -> None:
        """현재 진행 인덱스를 Action Feedback으로 퍼블리시한다."""
        from cobot1_interfaces.action import Assembly

        feedback = Assembly.Feedback()
        feedback.current_index = int(current_index)
        goal_handle.publish_feedback(feedback)

    def execute_callback(self, goal_handle):
        """
        Goal 수락 후 큐를 순차 실행한다.

        흐름:
          1. MOVE_HOME_AT_QUEUE_START가 True이면 홈 이동
          2. tasks 순회 → BlockTask (color, block_type, y_position) 기반 Pick & Place
          3. 각 작업 시작·완료 시 current_index Feedback 퍼블리시
          4. MOVE_HOME_AT_QUEUE_END가 True이면 홈 이동 후 종료
          5. 예외 발생 시 abort 후 Result 반환
          6. finally에서 반드시 _busy = False 해제
        """
        from cobot1_interfaces.action import Assembly

        result = Assembly.Result()
        result.failed_step = -1
        result.error_message = ''
        current_index = -1

        try:
            tasks = goal_handle.request.tasks
            total_count = len(tasks)

            place_x = self.get_parameter('place_x_mm').value
            place_z = self.get_parameter('place_z_mm').value

            self.publish_feedback(goal_handle, current_index=0)

            if MOVE_HOME_AT_QUEUE_START:
                self._motion_controller.move_home()

            for current_index, task_msg in enumerate(tasks):
                if goal_handle.is_cancel_requested:
                    result.error_message = '사용자에 의해 취소됨'
                    goal_handle.canceled()
                    return result

                base_place_pose = CartesianPose(
                    x_mm=place_x,
                    y_mm=float(task_msg.y_position),
                    z_mm=place_z,
                    a_deg=NORMAL_TOOL_A_DEG,
                    b_deg=NORMAL_TOOL_B_DEG,
                    c_deg=NORMAL_TOOL_C_DEG,
                )

                pick_task = PickPlaceTask(
                    color=task_msg.color,
                    block_type=int(task_msg.block_type),
                    base_place_pose=base_place_pose,
                    stack_index=0,
                )

                # 클로저 기본 인수로 반복 변수 캡처 (파이썬 late binding 방지)
                def _step_cb(
                    _step_name: str,
                    _idx: int = current_index,
                ) -> None:
                    self.publish_feedback(goal_handle, current_index=_idx)

                self._motion_controller.execute_pick_place(
                    pick_task,
                    step_callback=_step_cb,
                )

                self.publish_feedback(goal_handle, current_index=current_index)

            if MOVE_HOME_AT_QUEUE_END:
                self._motion_controller.move_home()

            self.publish_feedback(goal_handle, current_index=total_count)

            goal_handle.succeed()
            return result

        except Exception as exc:
            self.get_logger().error(f"Action Queue 실행 실패: {exc}")
            result.error_message = str(exc)
            result.failed_step = current_index
            goal_handle.abort()
            return result

        finally:
            # 성공/실패/취소 어느 경우에도 반드시 busy 해제
            with self._busy_lock:
                self._busy = False


# ─────────────────────────────────────────────────────────────────────────────
# 11. 실행 함수
# ─────────────────────────────────────────────────────────────────────────────

def main(args=None) -> None:
    """
    ROS2를 초기화하고 RobotControllerNode를 실행한다.
    MultiThreadedExecutor(2스레드): execute 스레드와 goal/cancel 콜백 스레드를 분리한다.
    """
    rclpy.init(args=args)

    node = RobotControllerNode()
    executor = MultiThreadedExecutor(num_threads=2)
    executor.add_node(node)

    try:
        executor.spin()
    except KeyboardInterrupt:
        node.get_logger().info("RobotController Action Server를 종료합니다.")
    finally:
        executor.shutdown()
        node.destroy_node()
        rclpy.shutdown()


if __name__ == "__main__":
    main()

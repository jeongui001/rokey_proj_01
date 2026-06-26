"""
robot_controller_node.py
Doosan M0609 + OnRobot RG2 키팅 트레이 방식 Pick & Place 실행 모듈.
ROS2 Action Server(/execute_queue)를 통해 BlockTask[] Goal을 수신한다.

동작 방식:
  - Pick 위치는 color, block_type 기반 KITTING_TRAY_PROFILES에서 조회한다.
  - Place 위치는 y_position(Y)과 고정 Place 상수로 결정한다.
"""

from __future__ import annotations

import math
import time
from dataclasses import dataclass
from threading import Event, Lock, Thread
from typing import Callable, List, Optional

import rclpy
from rclpy.action import ActionServer, CancelResponse, GoalResponse
from rclpy.callback_groups import ReentrantCallbackGroup
from rclpy.executors import MultiThreadedExecutor, SingleThreadedExecutor
from rclpy.node import Node
from std_msgs.msg import Bool
from std_srvs.srv import SetBool
import DR_init

from dsr_msgs2.srv import MoveStop

# ─────────────────────────────────────────────────────────────────────────────
# 1. 로봇 기본 설정
# ─────────────────────────────────────────────────────────────────────────────
ROBOT_ID = "dsr01"
ROBOT_MODEL = "m0609"

DR_init.__dsr__id = ROBOT_ID
DR_init.__dsr__model = ROBOT_MODEL

# ─────────────────────────────────────────────────────────────────────────────
# 2. 속도·가속도 설정
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

# 블록 적층 피치
BLOCK_HEIGHT_MM = 19.0
ASSEMBLY_CLEARANCE_MM = 1.0
STACK_PITCH_MM = BLOCK_HEIGHT_MM + ASSEMBLY_CLEARANCE_MM  # 20 mm

# 관절 이동 속도·가속도 (단위: %)
JOINT_VELOCITY = 60.0
JOINT_ACCELERATION = 60.0

# 일반 직선 이동 속도·가속도: [선속도(mm/s), 각속도(deg/s)]
LINEAR_VELOCITY: List[float] = [60.0, 60.0]
LINEAR_ACCELERATION: List[float] = [60.0, 60.0]

# Place 최종 하강 전용 저속 설정
PLACE_LINEAR_VELOCITY: List[float] = [10.0, 10.0]
PLACE_LINEAR_ACCELERATION: List[float] = [10.0, 10.0]

# ─────────────────────────────────────────────────────────────────────────────
# 3. RG2 설정
# ─────────────────────────────────────────────────────────────────────────────
# Pick 하강 완료 후 그립 전 대기 (초)
PICK_PRE_GRIP_WAIT_SEC = 0.3

# ─────────────────────────────────────────────────────────────────────────────
# 4. Place 고정 설정
# ─────────────────────────────────────────────────────────────────────────────
PLACE_FIXED_X_MM = 332.0

PLACE_Y_MAX_MM = 310.0
PLACE_Y_MIN_MM = -42.0

PLACE_OVERHEAD_Z_MM = 270.0
PLACE_BASE_Z_MM = 5.0

PLACE_A_DEG = 170.0
PLACE_B_DEG = -180.0
PLACE_C_DEG = 170.0

# ─────────────────────────────────────────────────────────────────────────────
# 5. Queue 이동 정책
# ─────────────────────────────────────────────────────────────────────────────
MOVE_HOME_AT_QUEUE_START = True   # 큐 시작 전 홈 이동 여부
MOVE_HOME_AT_QUEUE_END = False    # 큐 완료 후 홈 이동 여부

# ─────────────────────────────────────────────────────────────────────────────
# 6. RG2 Digital I/O 설정
# ─────────────────────────────────────────────────────────────────────────────
GRIP_DO_CHANNEL = 1
RELEASE_DO_CHANNEL = 2
GRIP_DI_CHANNEL = 1
RELEASE_DI_CHANNEL = 2

# ─────────────────────────────────────────────────────────────────────────────
# 7. Action Server 설정
# ─────────────────────────────────────────────────────────────────────────────
ACTION_NAME = "/execute_queue"

# ─────────────────────────────────────────────────────────────────────────────
# 8. 색상 정규화
#    Goal의 color 값이 한글 또는 영문 대소문자일 수 있으므로 내부에서 정규화한다.
# ─────────────────────────────────────────────────────────────────────────────
COLOR_ALIASES = {
    "yellow": "yellow",
    "노랑":   "yellow",
    "red":    "red",
    "빨강":   "red",
    "blue":   "blue",
    "파랑":   "blue",
    "green":  "green",
    "초록":   "green",
}


def normalize_color(color: str) -> str:
    """한글/영문 색상 문자열을 내부 영문 표준값으로 변환한다."""
    key = str(color).strip().lower()
    normalized = COLOR_ALIASES.get(key)
    if normalized is None:
        raise ValueError(
            f"지원하지 않는 색상: color={color!r}, "
            f"허용 값={list(COLOR_ALIASES.keys())}"
        )
    return normalized


# ─────────────────────────────────────────────────────────────────────────────
# 9. block_type 매핑 (BlockTask.block_type uint8)
#    Sequencer가 현재 1(placeholder)을 전송하므로 실제 운용 시 값 확인 필요.
# ─────────────────────────────────────────────────────────────────────────────
BLOCK_TYPE_MAP = {
    1: "2x2",
    2: "3x2",
}


def determine_block_type(block_type_val: int) -> str:
    """BlockTask.block_type uint8 값을 '2x2' 또는 '3x2' 문자열로 변환한다."""
    result = BLOCK_TYPE_MAP.get(int(block_type_val))
    if result is None:
        raise ValueError(
            f"알 수 없는 block_type: {block_type_val}, "
            f"허용 값: {list(BLOCK_TYPE_MAP.keys())}"
        )
    return result


# ─────────────────────────────────────────────────────────────────────────────
# 10. Cartesian Pose 데이터 모델
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
# 11. 키팅 트레이 프로파일 데이터 모델
# ─────────────────────────────────────────────────────────────────────────────

@dataclass(frozen=True)
class KittingTrayProfile:
    """
    색상·유형별 키팅 트레이 Pick 설정.
    overhead_pose와 pick_pose는 실제 티칭된 전체 Pose [X, Y, Z, A, B, C]를 사용한다.
    """
    profile_id: str           # 유일한 내부 식별자
    color: str                # 정규화된 색상 (영문)
    block_type: str           # "2x2" 또는 "3x2"
    overhead_pose: CartesianPose   # 트레이 상부 대기 Pose
    pick_pose: CartesianPose       # 블록 파지 직전 Pose
    tool_retract_z_mm: float       # Pick 후 Tool 기준 +Z 인출 거리 (mm)


# ─────────────────────────────────────────────────────────────────────────────
# 12. 키팅 트레이 설정 — 총 8개 Profile
#     Pose 순서: [X, Y, Z, A, B, C]
# ─────────────────────────────────────────────────────────────────────────────

KITTING_TRAY_PROFILES = {
    "yellow": {
        "2x2": KittingTrayProfile(
            profile_id="yellow_2x2",
            color="yellow",
            block_type="2x2",
            overhead_pose=CartesianPose(203.26, -97.78, 270.22, 89.97, -179.68, 90.34),
            pick_pose=CartesianPose(203.26, -101.5,  16.50, 90.00, -149.8, 90.38),
            tool_retract_z_mm=-40.0,
        ),
        "3x2": KittingTrayProfile(
            profile_id="yellow_3x2",
            color="yellow",
            block_type="3x2",
            overhead_pose=CartesianPose(256.98, -97.78, 270.22, 89.97, -179.68, 90.34),
            pick_pose=CartesianPose(256.98, -110.0,  17.0, 90.00, -149.8, 90.38),
            tool_retract_z_mm=-40.0,
        ),
    },
    "red": {
        "2x2": KittingTrayProfile(
            profile_id="red_2x2",
            color="red",
            block_type="2x2",
            overhead_pose=CartesianPose(308.64, -97.78, 270.22, 89.97, -179.68, 90.34),
            pick_pose=CartesianPose(308.64, -101.5,  16.50, 90.00, -149.8, 90.38),
            tool_retract_z_mm=-40.0,
        ),
        "3x2": KittingTrayProfile(
            profile_id="red_3x2",
            color="red",
            block_type="3x2",
            overhead_pose=CartesianPose(361.50, -97.78, 270.22, 89.97, -179.68, 90.34),
            pick_pose=CartesianPose(361.50, -110.0,  17.0, 90.00, -149.8, 90.38),
            tool_retract_z_mm=-40.0,
        ),
    },
    "blue": {
        "2x2": KittingTrayProfile(
            profile_id="blue_2x2",
            color="blue",
            block_type="2x2",
            overhead_pose=CartesianPose(438.19, -97.78, 270.22, 89.97, -179.68, 90.34),
            pick_pose=CartesianPose(438.19, -101.5,  16.50, 90.00, -149.8, 90.38),
            tool_retract_z_mm=-40.0,
        ),
        "3x2": KittingTrayProfile(
            profile_id="blue_3x2",
            color="blue",
            block_type="3x2",
            overhead_pose=CartesianPose(491.30, -97.78, 270.22, 89.97, -179.68, 90.34),
            pick_pose=CartesianPose(491.30, -110.0,  17.0, 90.00, -149.8, 90.38),
            tool_retract_z_mm=-40.0,
        ),
    },
    "green": {
        "2x2": KittingTrayProfile(
            profile_id="green_2x2",
            color="green",
            block_type="2x2",
            overhead_pose=CartesianPose(545.08, -97.78, 270.22, 89.97, -179.68, 90.34),
            pick_pose=CartesianPose(545.08, -101.5,  16.50, 90.00, -149.8, 90.38),
            tool_retract_z_mm=-40.0,
        ),
        # 임시: 초록 3x2 트레이로 사용. 실제 초록 3x2 트레이 티칭 후 좌표 업데이트 필요.
        "3x2": KittingTrayProfile(
            profile_id="green_3x2",
            color="green",
            block_type="3x2",
            overhead_pose=CartesianPose(600.19, -97.78, 270.22, 89.97, -179.68, 90.34),
            pick_pose=CartesianPose(600.19, -97.78,  15.80, 90.00, -149.8, 90.38),
            tool_retract_z_mm=-40.0,
        ),
    },
}


def select_kitting_profile(color: str, block_type_str: str) -> KittingTrayProfile:
    """
    정규화된 색상과 블록 유형 문자열로 KittingTrayProfile을 조회한다.
    미등록 color 또는 block_type이면 ValueError를 발생시킨다.
    color는 normalize_color()로 정규화된 값이어야 한다.
    """
    color_dict = KITTING_TRAY_PROFILES.get(color)
    if color_dict is None:
        raise ValueError(
            f"키팅 트레이 설정 없음: color={color}, block_type={block_type_str}"
        )
    profile = color_dict.get(block_type_str)
    if profile is None:
        raise ValueError(
            f"키팅 트레이 설정 없음: color={color}, block_type={block_type_str}"
        )
    return profile


# ─────────────────────────────────────────────────────────────────────────────
# 13. Pick & Place 작업 데이터 모델
# ─────────────────────────────────────────────────────────────────────────────

@dataclass(frozen=True)
class PickPlaceTask:
    """
    단일 키팅 트레이 Pick & Place 작업 파라미터.
    BlockTask (color, block_type, y_position)에서 변환하여 생성한다.
    """
    color: str          # 정규화된 색상 (영문)
    block_type_str: str # "2x2" 또는 "3x2"
    place_y_mm: float   # Place Y 좌표 (BlockTask.y_position)
    stack_index: int = 0  # 현재 인터페이스에 stack_index 없음 — 기본 0


# ─────────────────────────────────────────────────────────────────────────────
# 14. RobotMotionController 클래스
# ─────────────────────────────────────────────────────────────────────────────

class RobotMotionController:
    """
    로봇 관절·직선 이동 및 그리퍼 제어를 캡슐화한다.
    키팅 트레이 Pick & Place의 단계별 함수를 제공한다.
    """

    def __init__(self, node: Node) -> None:
        self._node = node
        self._logger = node.get_logger()

        from DSR_ROBOT2 import (
            movej,
            movel,
            wait,
            mwait,
            DR_BASE,
            DR_TOOL,
            DR_MV_MOD_REL,
            get_current_posx,
            set_digital_output,
            get_digital_input,
            ON,
            OFF,
            set_tcp,
            set_tool,
            add_tool,
            check_motion,
            DR_STATE_IDLE,
        )
        from DR_common2 import posj

        # 티치 펜던트에서 Tool/TCP 설정 완료된 상태. 코드 설정은 실제 컨트롤러에서 불필요.
        # add_tool("RG2", 1.29, [9.93, 1.47, 5.16], [0.0, 0.0, 0.0, 0.0, 0.0, 0.0])
        # set_tool("RG2")
        # set_tcp("RG2_TCP", [0.0, 0.0, 228.0, 0.0, 0.0, 0.0])

        self._movej = movej
        self._movel = movel
        self._wait = wait
        self._mwait = mwait
        self._DR_BASE = DR_BASE
        self._DR_TOOL = DR_TOOL
        self._DR_MV_MOD_REL = DR_MV_MOD_REL
        self._get_current_posx = get_current_posx
        self._posj = posj
        self._set_digital_output = set_digital_output
        self._get_digital_input = get_digital_input
        self._ON = ON
        self._OFF = OFF
        self._check_motion = check_motion
        self._DR_STATE_IDLE = DR_STATE_IDLE

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

    def _movel_and_wait(
        self,
        pose_arg,
        *,
        vel,
        acc,
        ref,
        mod=None,
        step_name: str,
    ) -> None:
        """
        비동기 movel 후 완료를 50ms 간격으로 폴링하며 대기한다.
        폴링 중 force_stop_event가 설정되면 RuntimeError를 발생시킨다.
        """
        kwargs: dict = dict(vel=vel, acc=acc, ref=ref, _async=1)
        if mod is not None:
            kwargs['mod'] = mod

        ret = self._movel(pose_arg, **kwargs)
        if ret == -1:
            raise RuntimeError(f"movel 실패: step={step_name}")

        # 컨트롤러가 모션을 큐에 올릴 때까지 짧게 대기
        time.sleep(0.1)

        seen_busy = False
        while True:
            if self._node._force_stop_event.is_set():
                raise RuntimeError(f"외력 감지 정지: step={step_name}")

            state = self._check_motion()
            if state == self._DR_STATE_IDLE:
                if seen_busy:
                    break
                # 아직 모션 시작 전일 수 있으니 한 번 더 확인
                time.sleep(0.05)
                if self._check_motion() == self._DR_STATE_IDLE:
                    break
            else:
                seen_busy = True

            time.sleep(0.05)

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
            f"a={pose.a_deg:.2f}  b={pose.b_deg:.2f}  c={pose.c_deg:.2f}"
        )
        self._movel_and_wait(
            to_posx(pose),
            vel=_vel,
            acc=_acc,
            ref=self._DR_BASE,
            step_name=step_name,
        )

    def move_relative_tool_z(
        self,
        distance_mm: float,
        step_name: str,
    ) -> None:
        """
        현재 Tool 좌표계의 +Z축 방향으로 distance_mm만큼 상대 이동한다.
        기울어진 Tool 자세 상태에서 Pick 완료 후 블록 인출 방향으로 사용한다.
        """
        if distance_mm == 0:
            raise ValueError(
                f"tool_retract_z_mm가 0입니다: step={step_name}"
            )

        from DR_common2 import posx as _posx

        self._logger.info(
            f"Tool Z 상대 이동: step={step_name}, distance={distance_mm:.2f} mm"
        )
        self._movel_and_wait(
            _posx(0.0, 0.0, distance_mm, 0.0, 0.0, 0.0),
            vel=LINEAR_VELOCITY,
            acc=LINEAR_ACCELERATION,
            ref=self._DR_TOOL,
            mod=self._DR_MV_MOD_REL,
            step_name=step_name,
        )

    def get_current_cartesian_pose(self) -> CartesianPose:
        """
        현재 TCP Pose를 Base 좌표계 기준으로 조회한다.
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

    # ── RG2 그리퍼 제어 (Digital I/O) ──────────────────────────────────────────

    def _wait_di(self, channel: int) -> None:
        """Digital Input이 ON이 될 때까지 폴링한다."""
        while not self._get_digital_input(channel):
            time.sleep(0.1)

    def rg2_grip(self) -> None:
        """Digital I/O로 그리퍼를 닫고 완료를 대기한다."""
        self._logger.info(f"RG2 grip (DO{GRIP_DO_CHANNEL}=ON, DO{RELEASE_DO_CHANNEL}=OFF)")
        self._set_digital_output(GRIP_DO_CHANNEL, self._ON)
        self._set_digital_output(RELEASE_DO_CHANNEL, self._OFF)
        self._wait_di(GRIP_DI_CHANNEL)

    def rg2_release(self) -> None:
        """Digital I/O로 그리퍼를 열고 완료를 대기한다."""
        self._logger.info(f"RG2 release (DO{RELEASE_DO_CHANNEL}=ON, DO{GRIP_DO_CHANNEL}=OFF)")
        self._set_digital_output(RELEASE_DO_CHANNEL, self._ON)
        self._set_digital_output(GRIP_DO_CHANNEL, self._OFF)
        self._wait_di(RELEASE_DI_CHANNEL)

    # ── 키팅 트레이 Pick 시퀀스 ───────────────────────────────────────────────

    def pick_from_kitting_tray(
        self,
        task: PickPlaceTask,
        step_callback: Optional[Callable[[str], None]] = None,
    ) -> None:
        """
        키팅 트레이에서 블록을 집는 전체 시퀀스.

        단계 순서:
          KITTING_RELEASE         — 그리퍼 열기
          KITTING_OVERHEAD_MOVE   — 트레이 전체 상부 Pose로 이동
          KITTING_PICK_DESCEND    — 상부 Pose → Pick Pose 한 번의 movel
          KITTING_PRE_GRIP_WAIT   — Pick Pose 도달 후 0.3초 정지
          KITTING_GRIP            — RG2 Close
          KITTING_TOOL_Z_RETRACT  — Tool 기준 +Z 상대 인출
          KITTING_RETURN_OVERHEAD — 트레이 상부 Pose로 복귀
        """
        profile = select_kitting_profile(task.color, task.block_type_str)

        if profile.tool_retract_z_mm == 0:
            raise ValueError(
                f"tool_retract_z_mm가 0입니다: "
                f"color={task.color}, block_type={task.block_type_str}"
            )

        def _step(name: str) -> None:
            self._node._pause_event.wait()
            self._logger.info(f"[color={task.color}] 단계: {name}")
            if step_callback is not None:
                step_callback(name)

        # 1. 그리퍼 열기
        _step("KITTING_RELEASE")
        self.rg2_release()

        # 2. 트레이 상부 Pose로 이동
        _step("KITTING_OVERHEAD_MOVE")
        self.move_linear(profile.overhead_pose, "KITTING_OVERHEAD_MOVE")

        # 3. Pick Pose로 하강
        _step("KITTING_PICK_DESCEND")
        self.move_linear(profile.pick_pose, "KITTING_PICK_DESCEND")

        # 4. Pick Pose 도달 후 정지
        _step("KITTING_PRE_GRIP_WAIT")
        self._wait(PICK_PRE_GRIP_WAIT_SEC)

        # 5. RG2 grip
        _step("KITTING_GRIP")
        self.rg2_grip()

        # 6. Tool Z 방향 인출
        _step("KITTING_TOOL_Z_RETRACT")
        self.move_relative_tool_z(
            profile.tool_retract_z_mm,
            "KITTING_TOOL_Z_RETRACT",
        )

        # 7. 트레이 상부 Pose로 복귀
        _step("KITTING_RETURN_OVERHEAD")
        self.move_linear(profile.overhead_pose, "KITTING_RETURN_OVERHEAD")

        self._logger.info(
            f"[color={task.color}] 키팅 Pick 완료: profile={profile.profile_id}"
        )

    # ── Place 시퀀스 ─────────────────────────────────────────────────────────

    def place_block_at_target(
        self,
        task: PickPlaceTask,
        step_callback: Optional[Callable[[str], None]] = None,
    ) -> None:
        """
        목표 위치에 블록을 배치하는 시퀀스.

        단계 순서:
          TARGET_OVERHEAD_MOVE  — Place 상부 Pose로 이동
          PLACE_DESCEND         — 저속으로 Place Pose까지 하강
          PLACE_RELEASE         — RG2 Open
          RETURN_PLACE_OVERHEAD — Place 상부 Pose로 복귀
        """
        def _step(name: str) -> None:
            self._node._pause_event.wait()
            self._logger.info(f"[color={task.color}] 단계: {name}")
            if step_callback is not None:
                step_callback(name)

        place_y_mm = task.place_y_mm

        if not math.isfinite(place_y_mm):
            raise ValueError(f"Place Y가 유한수가 아닙니다: y={place_y_mm}")
        if not (PLACE_Y_MIN_MM <= place_y_mm <= PLACE_Y_MAX_MM):
            raise ValueError(
                f"Place Y 범위 오류: y={place_y_mm}, "
                f"허용 범위=[{PLACE_Y_MIN_MM}, {PLACE_Y_MAX_MM}]"
            )

        actual_place_z = PLACE_BASE_Z_MM + task.stack_index * STACK_PITCH_MM

        if actual_place_z >= PLACE_OVERHEAD_Z_MM:
            raise ValueError(
                f"stack_index={task.stack_index}, "
                f"actual_place_z={actual_place_z:.2f} mm가 "
                f"PLACE_OVERHEAD_Z_MM={PLACE_OVERHEAD_Z_MM:.2f} mm 이상"
            )

        place_overhead_pose = CartesianPose(
            x_mm=PLACE_FIXED_X_MM,
            y_mm=place_y_mm,
            z_mm=PLACE_OVERHEAD_Z_MM,
            a_deg=PLACE_A_DEG,
            b_deg=PLACE_B_DEG,
            c_deg=PLACE_C_DEG,
        )
        actual_place_pose = CartesianPose(
            x_mm=PLACE_FIXED_X_MM,
            y_mm=place_y_mm,
            z_mm=actual_place_z,
            a_deg=PLACE_A_DEG,
            b_deg=PLACE_B_DEG,
            c_deg=PLACE_C_DEG,
        )

        # 1. Place 상부 Pose로 이동
        _step("TARGET_OVERHEAD_MOVE")
        self.move_linear(place_overhead_pose, "TARGET_OVERHEAD_MOVE")

        # 2. 저속으로 Place Pose까지 하강
        _step("PLACE_DESCEND")
        self.move_linear(
            actual_place_pose,
            "PLACE_DESCEND",
            vel=PLACE_LINEAR_VELOCITY,
            acc=PLACE_LINEAR_ACCELERATION,
        )

        # 3. RG2 release
        _step("PLACE_RELEASE")
        self.rg2_release()

        # 4. Place 상부 Pose로 복귀
        _step("RETURN_PLACE_OVERHEAD")
        self.move_linear(place_overhead_pose, "RETURN_PLACE_OVERHEAD")

        self._logger.info(
            f"[color={task.color}] Place 완료 — "
            f"stack_index={task.stack_index}, place_z={actual_place_z:.2f} mm"
        )

    # ── 대표 Pick & Place 함수 ────────────────────────────────────────────────

    def execute_pick_place(
        self,
        task: PickPlaceTask,
        step_callback: Optional[Callable[[str], None]] = None,
    ) -> None:
        """키팅 트레이 방식 전체 Pick & Place 시퀀스를 실행한다."""
        self.pick_from_kitting_tray(task, step_callback=step_callback)
        self.place_block_at_target(task, step_callback=step_callback)


# ─────────────────────────────────────────────────────────────────────────────
# 15. _PauseServiceNode — pause/resume 및 외력 감지
# ─────────────────────────────────────────────────────────────────────────────

class _PauseServiceNode(Node):
    """
    pause/resume 서비스와 외력 감지 polling을 전용 executor에서 처리하는 독립 노드.
    RobotControllerNode의 execute_callback이 blocking 중에도 즉시 응답한다.
    """

    def __init__(self, pause_event: Event, force_stop_event: Event):
        super().__init__('robot_controller_pause')
        self._pause_event = pause_event
        self._force_stop_event = force_stop_event

        self.declare_parameter('torque_threshold_nm', 10.0)
        self.declare_parameter('force_poll_hz', 10.0)

        self.create_service(SetBool, '/robot/pause', self._handle_pause)

        self._force_detected_pub = self.create_publisher(Bool, '/robot/force_detected', 10)
        self._move_stop_client = self.create_client(MoveStop, '/dsr01/motion/move_stop')

        # DSR_ROBOT2는 RobotControllerNode 생성 시 이미 import됨 (sys.modules 캐시)
        from DSR_ROBOT2 import get_external_torque
        self._get_external_torque = get_external_torque

        Thread(target=self._poll_loop, daemon=True).start()

    def _handle_pause(self, request, response):
        if request.data:
            self._pause_event.clear()
            self.get_logger().info('일시정지')
        else:
            # 재개: force_stop_event도 클리어하여 정상 상태로 복원
            self._force_stop_event.clear()
            self._pause_event.set()
            self.get_logger().info('재개')
        response.success = True
        return response

    def _poll_loop(self):
        threshold = self.get_parameter('torque_threshold_nm').value
        hz = self.get_parameter('force_poll_hz').value
        interval = 1.0 / hz
        while rclpy.ok():
            time.sleep(interval)
            if self._force_stop_event.is_set():
                continue
            try:
                torques = self._get_external_torque()
                if torques and any(abs(t) > threshold for t in torques):
                    self._do_force_stop()
            except Exception:
                pass

    def _do_force_stop(self):
        if self._force_stop_event.is_set():
            return

        self._force_stop_event.set()
        self._pause_event.clear()

        # 컨트롤러에 즉시 정지 명령 (fire-and-forget)
        if self._move_stop_client.service_is_ready():
            req = MoveStop.Request()
            req.stop_mode = 0  # QUICK stop
            self._move_stop_client.call_async(req)
        else:
            self.get_logger().warn('move_stop 서비스 미준비')

        msg = Bool()
        msg.data = True
        self._force_detected_pub.publish(msg)
        self.get_logger().warn('외력 감지 — 정지 명령 전송, 팝업 알림 발행')


# ─────────────────────────────────────────────────────────────────────────────
# 16. RobotControllerNode — Action Server 통합
# ─────────────────────────────────────────────────────────────────────────────

class RobotControllerNode(Node):
    """
    ROS2 Action Server(/execute_queue)를 제공하는 메인 노드.
    BlockTask[] Goal을 수신하여 키팅 트레이 방식 Pick & Place를 실행한다.
    """

    def __init__(self, pause_event: Event, force_stop_event: Event) -> None:
        super().__init__("robot_controller", namespace="dsr01")

        setattr(DR_init, '__dsr__node', self)
        self.get_logger().info(
            f"DR_init.__dsr__node 확인: {getattr(DR_init, '__dsr__node', None)}")

        self._busy_lock = Lock()
        self._busy = False
        self._pause_event = pause_event
        self._force_stop_event = force_stop_event
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
        self._pause_event.set()  # pause 중 cancel 시 wait() 해제
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
            self.get_logger().info(f"Goal 수락: {len(tasks)}개 task")
            return GoalResponse.ACCEPT

    def publish_feedback(self, goal_handle, *, current_index: int) -> None:
        """현재 진행 인덱스를 Action Feedback으로 퍼블리시한다."""
        from cobot1_interfaces.action import Assembly

        feedback = Assembly.Feedback()
        feedback.current_index = int(current_index)
        goal_handle.publish_feedback(feedback)

    def execute_callback(self, goal_handle):
        """
        Goal 수락 후 큐를 순차 실행한다.

        외력 감지로 RuntimeError 발생 시 동일 인덱스를 재시도한다.
        """
        from cobot1_interfaces.action import Assembly

        result = Assembly.Result()
        result.failed_step = -1
        result.error_message = ''
        current_index = -1

        try:
            self._pause_event.set()  # 이전 goal의 pause 상태 초기화

            tasks = goal_handle.request.tasks
            total_count = len(tasks)
            self.get_logger().info(f"Queue 실행 시작: {total_count}개 task")

            self.publish_feedback(goal_handle, current_index=0)

            if MOVE_HOME_AT_QUEUE_START:
                self.get_logger().info("홈 이동 중...")
                self._motion_controller.move_home()

            stack_counter: dict = {}
            current_index = 0

            while current_index < total_count:
                self._pause_event.wait()

                if goal_handle.is_cancel_requested:
                    result.error_message = '사용자에 의해 취소됨'
                    goal_handle.canceled()
                    return result

                task_msg = tasks[current_index]
                normalized_color = normalize_color(task_msg.color)
                block_type_str = determine_block_type(task_msg.block_type)
                place_y_mm = float(task_msg.y_position)

                stack_index = stack_counter.get(place_y_mm, 0)

                self.get_logger().info(
                    f"[{current_index+1}/{total_count}] "
                    f"color={normalized_color}, type={block_type_str}, "
                    f"y={place_y_mm:.2f}, stack={stack_index}")

                pick_task = PickPlaceTask(
                    color=normalized_color,
                    block_type_str=block_type_str,
                    place_y_mm=place_y_mm,
                    stack_index=stack_index,
                )

                def _step_cb(
                    _step_name: str,
                    _idx: int = current_index,
                ) -> None:
                    self.publish_feedback(goal_handle, current_index=_idx)

                try:
                    self._motion_controller.execute_pick_place(
                        pick_task,
                        step_callback=_step_cb,
                    )
                except RuntimeError as exc:
                    if self._force_stop_event.is_set():
                        self.get_logger().warn(
                            f'외력 감지 정지 — index={current_index}, 재개 대기')
                        self._pause_event.wait()  # resume 신호 대기
                        continue  # 동일 current_index 재시도
                    raise

                self.publish_feedback(goal_handle, current_index=current_index)
                stack_counter[place_y_mm] = stack_index + 1
                current_index += 1

            if MOVE_HOME_AT_QUEUE_END:
                self._motion_controller.move_home()

            self.publish_feedback(goal_handle, current_index=total_count)

            self.get_logger().info(f"Queue 완료: {total_count}개 task 성공")
            goal_handle.succeed()
            return result

        except Exception as exc:
            self.get_logger().error(f"Action Queue 실행 실패: {exc}")
            result.error_message = str(exc)
            result.failed_step = current_index
            goal_handle.abort()
            return result

        finally:
            with self._busy_lock:
                self._busy = False


# ─────────────────────────────────────────────────────────────────────────────
# 17. 실행 함수
# ─────────────────────────────────────────────────────────────────────────────

def main(args=None) -> None:
    """
    _PauseServiceNode를 전용 SingleThreadedExecutor + 별도 스레드로 실행해
    action execute_callback이 blocking 중에도 pause/resume 서비스가 응답하도록 분리한다.
    """
    rclpy.init(args=args)

    pause_event = Event()
    pause_event.set()
    force_stop_event = Event()

    node = RobotControllerNode(pause_event, force_stop_event)
    pause_node = _PauseServiceNode(pause_event, force_stop_event)

    pause_executor = SingleThreadedExecutor()
    pause_executor.add_node(pause_node)
    pause_thread = Thread(target=pause_executor.spin, daemon=True)
    pause_thread.start()

    executor = MultiThreadedExecutor(num_threads=2)
    executor.add_node(node)

    try:
        executor.spin()
    except KeyboardInterrupt:
        node.get_logger().info("RobotController Action Server를 종료합니다.")
    finally:
        executor.shutdown()
        pause_executor.shutdown()
        node.destroy_node()
        pause_node.destroy_node()
        rclpy.shutdown()


if __name__ == "__main__":
    main()

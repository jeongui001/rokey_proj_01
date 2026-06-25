"""
robot_controller_node.py
Doosan M0609 + OnRobot RG2 Pick & Place 동작 실행 모듈.
ROS2 Action Server(/execute_queue)를 통해 외부 Goal을 수신한다.
"""

from __future__ import annotations

import math
import time
from dataclasses import dataclass
from threading import Lock
from typing import Callable, List, Optional, Sequence

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

HOME_JOINT_DEG = [
    0.0,
    0.0,
    90.0,
    0.0,
    90.0,
    0.0,
]

BLOCK_HEIGHT_MM = 19.0
ASSEMBLY_CLEARANCE_MM = 0.5
STACK_PITCH_MM = BLOCK_HEIGHT_MM + ASSEMBLY_CLEARANCE_MM

JOINT_VELOCITY = 60.0
JOINT_ACCELERATION = 60.0

LINEAR_VELOCITY: List[float] = [60.0, 60.0]
LINEAR_ACCELERATION: List[float] = [60.0, 60.0]

APPROACH_HEIGHT_MM = 50.0

RG2_FORCE_VALUE = 400
RG2_STATUS_POLL_SEC = 0.1
RG2_SETTLE_WAIT_SEC = 0.2

MOTION_SETTLE_WAIT_SEC = 0.2

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
    x_mm: float
    y_mm: float
    z_mm: float
    a_deg: float
    b_deg: float
    c_deg: float


def with_z(pose: CartesianPose, z_mm: float) -> CartesianPose:
    return CartesianPose(
        x_mm=pose.x_mm,
        y_mm=pose.y_mm,
        z_mm=z_mm,
        a_deg=pose.a_deg,
        b_deg=pose.b_deg,
        c_deg=pose.c_deg,
    )


def add_z(pose: CartesianPose, offset_mm: float) -> CartesianPose:
    return with_z(pose, pose.z_mm + offset_mm)


def to_posx(pose: CartesianPose):
    from DR_common2 import posx
    return posx(
        pose.x_mm,
        pose.y_mm,
        pose.z_mm,
        pose.a_deg,
        pose.b_deg,
        pose.c_deg,
    )


def pose_from_array(values: Sequence[float]) -> CartesianPose:
    if len(values) != 6:
        raise ValueError(
            f"Pose 배열 길이는 6이어야 합니다: 전달받은 길이={len(values)}"
        )
    return CartesianPose(
        x_mm=float(values[0]),
        y_mm=float(values[1]),
        z_mm=float(values[2]),
        a_deg=float(values[3]),
        b_deg=float(values[4]),
        c_deg=float(values[5]),
    )


# ─────────────────────────────────────────────────────────────────────────────
# 6. Pick & Place 작업 데이터 모델
# ─────────────────────────────────────────────────────────────────────────────

@dataclass(frozen=True)
class PickPlaceTask:
    task_id: str
    color: str
    pick_pose: CartesianPose
    base_place_pose: CartesianPose
    stack_index: int

    def __post_init__(self) -> None:
        if self.stack_index < 0:
            raise ValueError(
                f"stack_index는 0 이상이어야 합니다: "
                f"task_id={self.task_id}, stack_index={self.stack_index}"
            )


# ─────────────────────────────────────────────────────────────────────────────
# 7. RobotMotionController 클래스
# ─────────────────────────────────────────────────────────────────────────────

class RobotMotionController:
    def __init__(self, node: Node) -> None:
        self._node = node
        self._logger = node.get_logger()

        from DSR_ROBOT2 import (
            movej,
            movel,
            wait,
            mwait,
            DR_BASE,
        )
        from DR_common2 import posj

        self._movej = movej
        self._movel = movel
        self._wait = wait
        self._mwait = mwait
        self._DR_BASE = DR_BASE
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
        return self._logger

    def move_home(self) -> None:
        self._logger.info("홈 자세로 이동")
        ret = self._movej(
            self._posj(*HOME_JOINT_DEG),
            vel=JOINT_VELOCITY,
            acc=JOINT_ACCELERATION,
        )
        if ret == -1:
            raise RuntimeError("movej 홈 이동 실패")
        self._mwait()

    def wait_rg2_complete(self) -> None:
        while self.gripper.get_status()[0]:
            time.sleep(RG2_STATUS_POLL_SEC)
        self._wait(RG2_SETTLE_WAIT_SEC)

    def rg2_open_and_wait(self) -> None:
        self._logger.info("RG2 열기")
        self.gripper.open_gripper(force_val=RG2_FORCE_VALUE)
        self.wait_rg2_complete()

    def rg2_close_and_wait(self) -> None:
        self._logger.info("RG2 닫기")
        self.gripper.close_gripper(force_val=RG2_FORCE_VALUE)
        self.wait_rg2_complete()

    def move_linear(
        self,
        pose: CartesianPose,
        step_name: str,
    ) -> None:
        self._logger.info(
            f"직선 이동: step={step_name}  "
            f"x={pose.x_mm:.2f}  y={pose.y_mm:.2f}  z={pose.z_mm:.2f}"
        )
        ret = self._movel(
            to_posx(pose),
            vel=LINEAR_VELOCITY,
            acc=LINEAR_ACCELERATION,
            ref=self._DR_BASE,
        )
        if ret == -1:
            raise RuntimeError(
                f"movel 실패: step={step_name}, pose={pose}"
            )
        self._mwait()

    def execute_pick_place(
        self,
        task: PickPlaceTask,
        step_callback: Optional[Callable[[str], None]] = None,
    ) -> None:
        def _step(name: str) -> None:
            self._logger.info(f"[{task.task_id}] 단계: {name}")
            if step_callback is not None:
                step_callback(name)

        pick_approach_pose = add_z(task.pick_pose, APPROACH_HEIGHT_MM)

        _step("PICK_APPROACH")
        self.move_linear(pick_approach_pose, "PICK_APPROACH")

        _step("RG2_OPEN")
        self.rg2_open_and_wait()

        _step("PICK_DESCEND")
        self.move_linear(task.pick_pose, "PICK_DESCEND")

        _step("RG2_CLOSE")
        self.rg2_close_and_wait()

        _step("PICK_LIFT")
        self.move_linear(pick_approach_pose, "PICK_LIFT")
        self._wait(MOTION_SETTLE_WAIT_SEC)

        actual_place_z = (
            task.base_place_pose.z_mm
            + task.stack_index * STACK_PITCH_MM
        )
        actual_place_pose = with_z(task.base_place_pose, actual_place_z)
        place_approach_pose = add_z(actual_place_pose, APPROACH_HEIGHT_MM)

        _step("PLACE_APPROACH")
        self.move_linear(place_approach_pose, "PLACE_APPROACH")

        _step("PLACE_DESCEND")
        self.move_linear(actual_place_pose, "PLACE_DESCEND")

        _step("RG2_OPEN")
        self.rg2_open_and_wait()

        _step("PLACE_LIFT")
        self.move_linear(place_approach_pose, "PLACE_LIFT")
        self._wait(MOTION_SETTLE_WAIT_SEC)

        self._logger.info(
            f"[{task.task_id}] Pick & Place 완료 — "
            f"color={task.color}, "
            f"stack_index={task.stack_index}, "
            f"place_z={actual_place_z:.2f} mm"
        )


# ─────────────────────────────────────────────────────────────────────────────
# 8. RobotControllerNode — Action Server 통합
# ─────────────────────────────────────────────────────────────────────────────

class RobotControllerNode(Node):
    def __init__(self) -> None:
        super().__init__("robot_controller")

        DR_init.__dsr__node = self

        self._busy_lock = Lock()
        self._busy = False

        self._action_callback_group = ReentrantCallbackGroup()
        self._motion_controller = RobotMotionController(self)

        # BlockTask → PickPlaceTask 변환에 사용하는 파라미터
        self.declare_parameter("fixed_x", 332.0)
        self.declare_parameter("place_z", 0.0)
        self.declare_parameter("place_orientation", [0.0, 0.0, 0.0])
        self.declare_parameter("pick_pose", [0.0, 0.0, 0.0, 0.0, 0.0, 0.0])

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

    def cancel_callback(self, goal_handle) -> CancelResponse:
        self.get_logger().info("액션 취소 요청 수신")
        return CancelResponse.ACCEPT

    def goal_callback(self, goal_request) -> GoalResponse:
        with self._busy_lock:
            if self._busy:
                self.get_logger().warn("이미 Queue 실행 중 — Goal 거부")
                return GoalResponse.REJECT

            tasks = goal_request.tasks
            if not tasks:
                self.get_logger().warn("tasks가 비어있음 — Goal 거부")
                return GoalResponse.REJECT

            for t in tasks:
                if t.block_type not in (1, 2):
                    self.get_logger().warn(
                        f"유효하지 않은 block_type={t.block_type} — Goal 거부"
                    )
                    return GoalResponse.REJECT

                if math.isnan(t.y_position) or math.isinf(t.y_position):
                    self.get_logger().warn(
                        "y_position에 NaN/Inf 포함 — Goal 거부"
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
        from cobot1_interfaces.action import Assembly

        feedback = Assembly.Feedback()
        feedback.current_index = int(current_index)
        goal_handle.publish_feedback(feedback)

    def execute_callback(self, goal_handle):
        from cobot1_interfaces.action import Assembly

        result = Assembly.Result()
        result.failed_step = -1
        result.error_message = ''
        current_index = -1

        try:
            tasks = goal_handle.request.tasks

            fixed_x = self.get_parameter("fixed_x").value
            place_z = self.get_parameter("place_z").value
            place_orient = self.get_parameter("place_orientation").value
            pick_pose_values = self.get_parameter("pick_pose").value

            pick_pose = pose_from_array(pick_pose_values)

            self._motion_controller.move_home()

            for current_index, task_msg in enumerate(tasks):
                if goal_handle.is_cancel_requested:
                    result.failed_step = current_index
                    result.error_message = '사용자에 의해 취소됨'
                    goal_handle.canceled()
                    return result

                base_place_pose = CartesianPose(
                    x_mm=fixed_x,
                    y_mm=task_msg.y_position,
                    z_mm=place_z,
                    a_deg=place_orient[0],
                    b_deg=place_orient[1],
                    c_deg=place_orient[2],
                )

                pick_task = PickPlaceTask(
                    task_id=f"block_{current_index}",
                    color=task_msg.color,
                    pick_pose=pick_pose,
                    base_place_pose=base_place_pose,
                    stack_index=0,
                )

                def _step_cb(
                    step_name: str,
                    _idx: int = current_index,
                ) -> None:
                    self.publish_feedback(
                        goal_handle,
                        current_index=_idx,
                    )

                self._motion_controller.execute_pick_place(
                    pick_task,
                    step_callback=_step_cb,
                )

                self.publish_feedback(
                    goal_handle,
                    current_index=current_index,
                )

            self._motion_controller.move_home()

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
# 9. 실행 함수
# ─────────────────────────────────────────────────────────────────────────────

def main(args=None) -> None:
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

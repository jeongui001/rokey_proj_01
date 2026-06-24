import json
import time

import rclpy
from rclpy.node import Node
from rclpy.action import ActionServer, GoalResponse, CancelResponse

from cobot1_interfaces.action import ExecuteQueue


class RobotControllerNode(Node):

    def __init__(self):
        super().__init__('robot_controller')

        self._action_server = ActionServer(
            self,
            ExecuteQueue,
            '/execute_queue',
            execute_callback=self.execute_callback,
            goal_callback=self.goal_callback,
            cancel_callback=self.cancel_callback,
        )

        self.get_logger().info('RobotController 노드 시작')

    def goal_callback(self, goal_request):
        self.get_logger().info('액션 골 수신')
        return GoalResponse.ACCEPT

    def cancel_callback(self, goal_handle):
        self.get_logger().info('액션 취소 요청 수신')
        return CancelResponse.ACCEPT

    def execute_callback(self, goal_handle):
        self.get_logger().info('액션 실행 시작')

        queue = json.loads(goal_handle.request.action_queue_json)
        total = len(queue)
        feedback = ExecuteQueue.Feedback()
        result = ExecuteQueue.Result()

        for i, item in enumerate(queue):
            if goal_handle.is_cancel_requested:
                goal_handle.canceled()
                result.success = False
                result.completed_steps = i
                result.failed_step = i
                result.error_message = '사용자에 의해 취소됨'
                return result

            # TODO: 실제 로봇 제어 로직 구현
            # item['action']: "place" 또는 "remove"
            # item['color']:  블록 색상
            # item['target']: [x, y, z] 로봇 좌표
            #
            # 시뮬레이션: 1초 대기
            time.sleep(1.0)

            feedback.current_step = item['step']
            feedback.total_steps = total
            feedback.current_action = item['action']
            feedback.current_color = item['color']
            feedback.current_target = item['target']
            goal_handle.publish_feedback(feedback)

            self.get_logger().info(
                f"[{i+1}/{total}] {item['action']} {item['color']} "
                f"→ {item['target']}")

        goal_handle.succeed()
        result.success = True
        result.completed_steps = total
        result.failed_step = -1
        result.error_message = ''
        return result


def main(args=None):
    rclpy.init(args=args)
    node = RobotControllerNode()
    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass
    finally:
        node.destroy_node()
        rclpy.shutdown()

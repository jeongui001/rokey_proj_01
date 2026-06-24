import rclpy
from rclpy.node import Node

from cobot1_interfaces.srv import SequencePlan


class SequencerNode(Node):

    def __init__(self):
        super().__init__('sequencer')

        self.srv = self.create_service(
            SequencePlan, '/sequence/plan', self.handle_plan)

        self.get_logger().info('Sequencer 노드 시작')

    def handle_plan(self, request, response):
        self.get_logger().info(
            f'배치 계획 요청: grid_size={request.grid_size}')

        # TODO: 배치 계획 로직 구현
        # request.grid_json : JSON 2차원 색상 배열
        #   예: '[["red","blue"],["green","white"]]'
        # request.grid_size : 격자 크기
        #
        # 반환할 Action Queue 형식 (JSON 배열):
        # [
        #   {"action": "place", "step": 0, "color": "red", "target": [x, y, z]},
        #   {"action": "place", "step": 1, "color": "blue", "target": [x, y, z]},
        #   ...
        # ]
        # - 레이어 아래→위 순서로 정렬
        # - step: 큐 내 실행 순서
        # - target: 로봇 좌표 [x, y, z]

        response.success = False
        response.action_queue_json = ''
        response.error_message = '아직 구현되지 않았습니다.'

        return response


def main(args=None):
    rclpy.init(args=args)
    node = SequencerNode()
    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass
    finally:
        node.destroy_node()
        rclpy.shutdown()

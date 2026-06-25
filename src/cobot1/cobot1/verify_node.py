import rclpy
from rclpy.node import Node
from rclpy.qos import DurabilityPolicy, QoSProfile, ReliabilityPolicy

from cobot1_interfaces.msg import ExpectedModel


class VerifyNode(Node):
    """검증 노드 (재설계 예정).

    현재는 ExpectedModel 토픽만 수신하여 저장한다.
    검증 서비스(/verify/check)는 인터페이스 재설계 후 구현 예정.
    """

    def __init__(self):
        super().__init__('verify')

        model_qos = QoSProfile(depth=1)
        model_qos.reliability = ReliabilityPolicy.RELIABLE
        model_qos.durability = DurabilityPolicy.TRANSIENT_LOCAL

        self.create_subscription(
            ExpectedModel,
            '/vision/expected_model',
            self._on_expected_model,
            model_qos,
        )

        self._expected_colors = []
        self._expected_grid_size = 0
        self.get_logger().info('VerifyNode 시작 (검증 서비스 미구현)')

    def _on_expected_model(self, msg):
        self._expected_colors = list(msg.colors)
        self._expected_grid_size = msg.grid_size
        self.get_logger().info(
            f'기준 모델 수신: {self._expected_grid_size}셀, '
            f'{sum(1 for c in self._expected_colors if c)}개 블록')


def main(args=None):
    rclpy.init(args=args)
    node = VerifyNode()
    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass
    finally:
        node.destroy_node()
        rclpy.shutdown()

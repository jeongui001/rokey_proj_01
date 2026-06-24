import rclpy
from rclpy.node import Node

from rokey_project_01_interfaces.msg import WebcamError


class WebcamNode(Node):

    def __init__(self):
        super().__init__('webcam')

        self.error_pub = self.create_publisher(WebcamError, '/webcam/error', 10)

        # TODO: 웹캠 스트림 열기, 실시간 모니터링 타이머 설정
        # self.timer = self.create_timer(0.1, self.monitor_callback)

        self.get_logger().info('WebcamNode 시작')

    def publish_error(self, step, row, col, expected, detected, message=''):
        msg = WebcamError()
        msg.step = step
        msg.row = row
        msg.col = col
        msg.expected_color = expected
        msg.detected_color = detected
        msg.message = message
        self.error_pub.publish(msg)
        self.get_logger().warn(
            f'에러 발행: step={step} ({row},{col}) '
            f'expected={expected} detected={detected}')

    # TODO: 실시간 모니터링 콜백
    # def monitor_callback(self):
    #     frame = ...  # 웹캠 프레임 캡처
    #     # 색상 감지 로직
    #     # 에러 발견 시 self.publish_error(...) 호출


def main(args=None):
    rclpy.init(args=args)
    node = WebcamNode()
    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass
    finally:
        node.destroy_node()
        rclpy.shutdown()

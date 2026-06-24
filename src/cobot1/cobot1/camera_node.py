import rclpy
from rclpy.node import Node
from sensor_msgs.msg import Image, CameraInfo


class CameraNode(Node):

    def __init__(self):
        super().__init__('camera')

        self.image_pub = self.create_publisher(Image, '/front_camera/image_raw', 10)
        self.info_pub = self.create_publisher(CameraInfo, '/front_camera/camera_info', 10)

        # TODO: 카메라 스트림 열기, 캘리브레이션 파라미터 로드
        # TODO: 주기적 발행 타이머 설정

        self.get_logger().info('CameraNode 시작')


def main(args=None):
    rclpy.init(args=args)
    node = CameraNode()
    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass
    finally:
        node.destroy_node()
        rclpy.shutdown()

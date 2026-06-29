from __future__ import annotations

from pathlib import Path

import cv2
import rclpy
import yaml
from cv_bridge import CvBridge
from rclpy.node import Node
from sensor_msgs.msg import CameraInfo, Image


class CameraNode(Node):
    def __init__(self):
        super().__init__('camera')

        self.declare_parameter('video_device', '/dev/video0')
        self.declare_parameter('framerate', 30.0)
        self.declare_parameter('frame_id', 'front_camera_optical_frame')
        self.declare_parameter('image_width', 640)
        self.declare_parameter('image_height', 480)
        self.declare_parameter('camera_name', 'front_camera')
        self.declare_parameter('image_topic', '')
        self.declare_parameter('camera_info_topic', '')
        self.declare_parameter('camera_info_url', '')
        self.declare_parameter('flip_horizontal', False)
        self.declare_parameter('brightness', -1)
        self.declare_parameter('contrast', -1)
        self.declare_parameter('saturation', -1)
        self.declare_parameter('sharpness', -1)
        self.declare_parameter('gain', -1)
        self.declare_parameter('exposure', -1)
        self.declare_parameter('focus', -1)

        self._bridge = CvBridge()
        self._capture = None
        self._device = str(self.get_parameter('video_device').value)
        self._frame_id = str(self.get_parameter('frame_id').value)
        self._width = int(self.get_parameter('image_width').value)
        self._height = int(self.get_parameter('image_height').value)
        self._framerate = max(1.0, float(self.get_parameter('framerate').value))
        self._camera_name = str(self.get_parameter('camera_name').value)
        self._flip_horizontal = bool(self.get_parameter('flip_horizontal').value)

        image_topic = str(self.get_parameter('image_topic').value) or f'/{self._camera_name}/image_raw'
        info_topic = str(self.get_parameter('camera_info_topic').value) or f'/{self._camera_name}/camera_info'
        self._image_pub = self.create_publisher(Image, image_topic, 10)
        self._info_pub = self.create_publisher(CameraInfo, info_topic, 10)
        self._camera_info = self._load_camera_info()

        self._open_capture()
        self._timer = self.create_timer(1.0 / self._framerate, self._publish_frame)
        self.get_logger().info(
            f'CameraNode ready: device={self._device}, '
            f'topics={image_topic}, {info_topic}'
        )

    def _open_capture(self) -> None:
        if self._capture is not None:
            self._capture.release()

        source = int(self._device) if self._device.isdigit() else self._device
        self._capture = cv2.VideoCapture(source)
        if not self._capture.isOpened():
            # self.get_logger().error(f'카메라를 열 수 없습니다: {self._device}')
            return

        self._capture.set(cv2.CAP_PROP_FRAME_WIDTH, float(self._width))
        self._capture.set(cv2.CAP_PROP_FRAME_HEIGHT, float(self._height))
        self._capture.set(cv2.CAP_PROP_FPS, float(self._framerate))
        self._set_camera_property('brightness', cv2.CAP_PROP_BRIGHTNESS)
        self._set_camera_property('contrast', cv2.CAP_PROP_CONTRAST)
        self._set_camera_property('saturation', cv2.CAP_PROP_SATURATION)
        self._set_camera_property('sharpness', getattr(cv2, 'CAP_PROP_SHARPNESS', -1))
        self._set_camera_property('gain', cv2.CAP_PROP_GAIN)
        self._set_camera_property('exposure', cv2.CAP_PROP_EXPOSURE)
        self._set_camera_property('focus', getattr(cv2, 'CAP_PROP_FOCUS', -1))

    def _set_camera_property(self, parameter_name: str, property_id: int) -> None:
        if property_id < 0:
            return
        value = int(self.get_parameter(parameter_name).value)
        if value >= 0:
            self._capture.set(property_id, float(value))

    def _publish_frame(self) -> None:
        if self._capture is None or not self._capture.isOpened():
            self._open_capture()
            return

        ok, frame = self._capture.read()
        if not ok or frame is None:
            self.get_logger().warn('카메라 프레임을 읽지 못했습니다. 다시 연결을 시도합니다.')
            self._open_capture()
            return
        if self._flip_horizontal:
            frame = cv2.flip(frame, 1)

        stamp = self.get_clock().now().to_msg()
        image_msg = self._bridge.cv2_to_imgmsg(frame, encoding='bgr8')
        image_msg.header.stamp = stamp
        image_msg.header.frame_id = self._frame_id
        self._image_pub.publish(image_msg)

        info_msg = CameraInfo()
        info_msg.width = self._camera_info.width or frame.shape[1]
        info_msg.height = self._camera_info.height or frame.shape[0]
        info_msg.distortion_model = self._camera_info.distortion_model
        info_msg.d = list(self._camera_info.d)
        info_msg.k = list(self._camera_info.k)
        info_msg.r = list(self._camera_info.r)
        info_msg.p = list(self._camera_info.p)
        info_msg.header.stamp = stamp
        info_msg.header.frame_id = self._frame_id
        if self._flip_horizontal:
            self._mirror_camera_info(info_msg)
        self._info_pub.publish(info_msg)

    def _mirror_camera_info(self, info_msg: CameraInfo) -> None:
        if len(info_msg.k) >= 9 and info_msg.k[0] > 0.0:
            info_msg.k[2] = float(info_msg.width - 1) - float(info_msg.k[2])
        if len(info_msg.p) >= 12 and info_msg.p[0] > 0.0:
            info_msg.p[2] = float(info_msg.width - 1) - float(info_msg.p[2])

    def _load_camera_info(self) -> CameraInfo:
        path = self._resolve_camera_info_path(str(self.get_parameter('camera_info_url').value))
        if path is None:
            return self._uncalibrated_camera_info()

        try:
            data = yaml.safe_load(path.read_text()) or {}
        except OSError as exc:
            self.get_logger().warn(f'camera_info 파일을 읽지 못했습니다: {exc}')
            return self._uncalibrated_camera_info()

        info = self._uncalibrated_camera_info()
        info.width = int(data.get('image_width', self._width))
        info.height = int(data.get('image_height', self._height))
        info.distortion_model = str(data.get('distortion_model', 'plumb_bob'))
        info.d = _matrix_data(data, 'distortion_coefficients', 5)
        info.k = _matrix_data(data, 'camera_matrix', 9)
        info.r = _matrix_data(data, 'rectification_matrix', 9)
        info.p = _matrix_data(data, 'projection_matrix', 12)
        return info

    def _resolve_camera_info_path(self, url: str) -> Path | None:
        if not url:
            return None
        if url.startswith('file://'):
            return Path(url[7:])
        if not url.startswith('package://'):
            return Path(url)

        package, _, relative = url[10:].partition('/')
        if not package or not relative:
            return None
        try:
            from ament_index_python.packages import get_package_share_directory

            return Path(get_package_share_directory(package)) / relative
        except Exception:
            if package == 'cobot1' and relative.startswith('config/'):
                return Path(__file__).resolve().parents[1] / relative
            self.get_logger().warn(f'package URL을 해석하지 못했습니다: {url}')
            return None

    def _uncalibrated_camera_info(self) -> CameraInfo:
        info = CameraInfo()
        info.width = self._width
        info.height = self._height
        info.distortion_model = 'plumb_bob'
        info.d = [0.0, 0.0, 0.0, 0.0, 0.0]
        info.k = [0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0]
        info.r = [1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0]
        info.p = [0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0]
        return info

    def destroy_node(self):
        if self._capture is not None:
            self._capture.release()
        super().destroy_node()


def _matrix_data(data: dict, key: str, expected: int) -> list[float]:
    values = data.get(key, {}).get('data', [])
    if len(values) != expected:
        return [0.0] * expected
    return [float(value) for value in values]


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

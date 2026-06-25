import base64
import json
import threading

import cv2
import numpy as np
import rclpy
from rclpy.node import Node
from rclpy.action import ActionClient
from rclpy.qos import DurabilityPolicy, QoSProfile, ReliabilityPolicy
import socketio
from cv_bridge import CvBridge

from cobot1_interfaces.srv import ProcessMosaic, SequencePlan
from cobot1_interfaces.action import Assembly
from cobot1_interfaces.msg import ExpectedModel, WebcamError

from . import db


class BridgeNode(Node):

    # ════════════════════════════════════════════
    #  Flask/SocketIO 통신 (블랙박스)
    # ════════════════════════════════════════════

    class _FlaskClient:
        """Flask SocketIO 연결·수신·송신을 캡슐화한다.

        bridge: BridgeNode 인스턴스. Flask 이벤트 수신 시 bridge의 메서드를 호출한다.
        """

        def __init__(self, bridge: 'BridgeNode'):
            self._bridge = bridge
            self._sio = socketio.Client(reconnection=True)
            self._register_handlers()
            threading.Thread(target=self._connect, daemon=True).start()

        # ── 연결 ──

        def _connect(self):
            import time
            while True:
                try:
                    self._sio.connect('http://localhost:5000', namespaces=['/bridge'])
                    self._bridge.get_logger().info('Flask 연결 성공')
                    break
                except Exception as e:
                    self._bridge.get_logger().warn(f'Flask 연결 대기 중... ({e})')
                    time.sleep(5)

        def disconnect(self):
            self._sio.disconnect()

        # ── 이벤트 수신 → Bridge 메서드 호출 ──

        def _register_handlers(self):
            @self._sio.on('connect', namespace='/bridge')
            def on_connect():
                self._bridge.get_logger().info('SocketIO /bridge 연결됨')

            @self._sio.on('disconnect', namespace='/bridge')
            def on_disconnect():
                self._bridge.get_logger().warn('SocketIO /bridge 연결 해제됨')

            @self._sio.on('upload_image', namespace='/bridge')
            def on_upload_image(data):
                self._bridge.get_logger().info('이미지 분석 요청 수신')
                cv_image = self._decode_image(data.get('image_data', ''))
                self._bridge._current_image_data = data
                self._bridge.handle_analyze(cv_image)

            @self._sio.on('update_grid', namespace='/bridge')
            def on_update_grid(data):
                self._bridge.get_logger().info('격자 수정 수신')
                grid_json_str = data.get('grid_json', '')
                colors_2d = json.loads(grid_json_str)
                flat_colors = [c for row in colors_2d for c in row]
                self._bridge.handle_update_colors(flat_colors)

            @self._sio.on('start_assembly', namespace='/bridge')
            def on_start_assembly(data):
                self._bridge.get_logger().info('조립 시작 요청 수신')
                self._bridge.handle_start_assembly()

            @self._sio.on('pause', namespace='/bridge')
            def on_pause():
                self._bridge.get_logger().info('일시정지 요청')

            @self._sio.on('resume', namespace='/bridge')
            def on_resume():
                self._bridge.get_logger().info('재개 요청')

        # ── base64 → OpenCV 변환 ──

        @staticmethod
        def _decode_image(image_data: str):
            if ',' in image_data:
                image_data = image_data.split(',', 1)[1]
            image_bytes = base64.b64decode(image_data)
            nparr = np.frombuffer(image_bytes, np.uint8)
            return cv2.imdecode(nparr, cv2.IMREAD_COLOR)

        # ── Bridge → Flask 송신 ──

        def send_analysis_result(self, success, colors_json='', error_message=''):
            self._sio.emit('analysis_result', {
                'success': success,
                'grid_json': colors_json,
                'error_message': error_message,
            }, namespace='/bridge')

        def send_assembly_started(self):
            self._sio.emit('assembly_started', {}, namespace='/bridge')

        def send_assembly_progress(self, data):
            self._sio.emit('assembly_progress', data, namespace='/bridge')

        def send_assembly_done(self):
            self._sio.emit('assembly_done', {}, namespace='/bridge')

        def send_assembly_error(self, failed_step, error_message):
            self._sio.emit('assembly_error', {
                'failed_step': failed_step,
                'error_message': error_message,
            }, namespace='/bridge')

    # ════════════════════════════════════════════
    #  ROS2 초기화
    # ════════════════════════════════════════════

    def __init__(self):
        super().__init__('bridge')

        # ROS2 서비스 클라이언트
        self.image_client = self.create_client(ProcessMosaic, '/image/analyze')
        self.sequence_client = self.create_client(SequencePlan, '/sequence/plan')

        # ROS2 액션 클라이언트
        self.robot_action_client = ActionClient(self, Assembly, '/execute_queue')

        # ROS2 퍼블리셔
        model_qos = QoSProfile(depth=1)
        model_qos.reliability = ReliabilityPolicy.RELIABLE
        model_qos.durability = DurabilityPolicy.TRANSIENT_LOCAL
        self.verify_pub = self.create_publisher(
            ExpectedModel, '/vision/expected_model', model_qos)

        # ROS2 구독
        self.webcam_error_sub = self.create_subscription(
            WebcamError, '/webcam/error', self._on_webcam_error, 10)

        # 내부 상태
        self._bridge = CvBridge()
        self._current_colors = []
        self._current_image_data = None
        self._goal_handle = None
        self._current_tasks = []

        # Flask 연결
        self._flask = self._FlaskClient(self)
        self.get_logger().info('Bridge 노드 시작')

    # ════════════════════════════════════════════
    #  Flask 이벤트 핸들러 (Flask → Bridge 진입점)
    # ════════════════════════════════════════════

    def handle_analyze(self, cv_image):
        """이미지 분석 요청 처리. cv_image: OpenCV BGR 이미지."""
        request = ProcessMosaic.Request()
        request.input_image = self._bridge.cv2_to_imgmsg(cv_image, encoding='bgr8')
        future = self.image_client.call_async(request)
        future.add_done_callback(self._on_mosaic_result)

    def handle_update_colors(self, flat_colors):
        """사용자가 수정한 색상 배열을 반영."""
        if not self._current_colors:
            self.get_logger().warn('색상 데이터가 없습니다 (이미지 분석을 먼저 실행하세요)')
            return
        self._current_colors = flat_colors
        self.get_logger().info('사용자 색상 수정 반영 완료')
        self._flask.send_analysis_result(True, json.dumps(self._current_colors))

    def handle_start_assembly(self):
        """조립 시작 요청 처리."""
        self._publish_verify_model()
        self._call_sequence_plan()

    # ════════════════════════════════════════════
    #  ImageProcessor 서비스 (이미지 분석)
    # ════════════════════════════════════════════

    def _on_mosaic_result(self, future):
        try:
            response = future.result()
            if response.success:
                self._current_colors = list(response.colors)
                self._flask.send_analysis_result(True, json.dumps(self._current_colors))
            else:
                self._flask.send_analysis_result(False, error_message=response.message)
        except Exception as e:
            self.get_logger().error(f'ProcessMosaic 호출 실패: {e}')
            self._flask.send_analysis_result(False, error_message=str(e))

    # ════════════════════════════════════════════
    #  VerifyNode 토픽 (기준 모델 발행)
    # ════════════════════════════════════════════

    def _publish_verify_model(self):
        if self._current_colors:
            msg = ExpectedModel()
            msg.grid_size = len(self._current_colors)
            msg.colors = self._current_colors
            self.verify_pub.publish(msg)
            self.get_logger().info('기준 모델 토픽 발행 완료')
        else:
            self.get_logger().warn('기준 모델이 없습니다 (이미지 분석을 먼저 실행하세요)')

    # ════════════════════════════════════════════
    #  Sequencer 서비스 (배치 계획)
    # ════════════════════════════════════════════

    def _call_sequence_plan(self):
        request = SequencePlan.Request()
        request.colors = self._current_colors
        future = self.sequence_client.call_async(request)
        future.add_done_callback(self._on_sequence_result)

    def _on_sequence_result(self, future):
        try:
            response = future.result()
            if response.error_message:
                self._flask.send_assembly_error(-1, response.error_message)
                return
            self._send_action_goal(response.tasks)
        except Exception as e:
            self.get_logger().error(f'SequencePlan 호출 실패: {e}')
            self._flask.send_assembly_error(-1, str(e))

    # ════════════════════════════════════════════
    #  RobotController 액션 (로봇 실행)
    # ════════════════════════════════════════════

    def _send_action_goal(self, tasks):
        goal = Assembly.Goal()
        goal.tasks = tasks
        self._current_tasks = list(tasks)

        self.robot_action_client.wait_for_server(timeout_sec=5.0)
        send_future = self.robot_action_client.send_goal_async(
            goal, feedback_callback=self._on_robot_feedback)
        send_future.add_done_callback(self._on_goal_response)
        self._flask.send_assembly_started()

    def _on_goal_response(self, future):
        goal_handle = future.result()
        if not goal_handle.accepted:
            self.get_logger().warn('액션 골 거부됨')
            self._flask.send_assembly_error(-1, '로봇이 작업을 거부했습니다.')
            return
        self._goal_handle = goal_handle
        result_future = goal_handle.get_result_async()
        result_future.add_done_callback(self._on_robot_result)

    def _on_robot_feedback(self, feedback_msg):
        fb = feedback_msg.feedback
        if 0 <= fb.current_index < len(self._current_tasks):
            t = self._current_tasks[fb.current_index]
            db.insert_placement(fb.current_index, t.color, t.y_position)
        self._flask.send_assembly_progress({'current_step': fb.current_index})

    def _on_robot_result(self, future):
        result = future.result().result
        if not result.error_message:
            self._flask.send_assembly_done()
        else:
            db.insert_error(result.failed_step, 'ACTION_FAIL', result.error_message)
            self._flask.send_assembly_error(result.failed_step, result.error_message)

    # ════════════════════════════════════════════
    #  WebcamNode 토픽 (에러 감지)
    # ════════════════════════════════════════════

    def _on_webcam_error(self, msg):
        self.get_logger().warn(
            f'웹캠 에러 수신: step={msg.step} ({msg.row},{msg.col}) '
            f'{msg.expected_color}→{msg.detected_color}')
        self.cancel_assembly()
        db.insert_error(msg.step, 'WEBCAM_DETECT', msg.message)
        self._flask.send_assembly_error(
            msg.step,
            f'색상 불일치: ({msg.row},{msg.col}) '
            f'{msg.expected_color}→{msg.detected_color}')

    def cancel_assembly(self):
        if self._goal_handle is not None:
            self._goal_handle.cancel_goal_async()
            self.get_logger().info('액션 취소 요청')


def main(args=None):
    rclpy.init(args=args)
    node = BridgeNode()
    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass
    finally:
        node._flask.disconnect()
        node.destroy_node()
        rclpy.shutdown()

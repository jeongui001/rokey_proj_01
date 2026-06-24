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

from rokey_project_01_interfaces.srv import ProcessMosaic, SequencePlan
from rokey_project_01_interfaces.action import ExecuteQueue
from rokey_project_01_interfaces.msg import BlockModel, WebcamError

from . import db


class BridgeNode(Node):

    def __init__(self):
        super().__init__('bridge')

        # ── ROS2 서비스 클라이언트 ──
        self.image_client = self.create_client(ProcessMosaic, '/image/analyze')
        self.sequence_client = self.create_client(SequencePlan, '/sequence/plan')

        # ── ROS2 액션 클라이언트 ──
        self.robot_action_client = ActionClient(self, ExecuteQueue, '/execute_queue')

        # ── ROS2 퍼블리셔 ──
        model_qos = QoSProfile(depth=1)
        model_qos.reliability = ReliabilityPolicy.RELIABLE
        model_qos.durability = DurabilityPolicy.TRANSIENT_LOCAL
        self.verify_pub = self.create_publisher(
            BlockModel, '/vision/expected_model', model_qos)

        # ── ROS2 구독 ──
        self.webcam_error_sub = self.create_subscription(
            WebcamError, '/webcam/error', self._on_webcam_error, 10)

        # ── 이미지 변환 ──
        self._bridge = CvBridge()

        # ── 상태 ──
        self._current_grid_json = ''
        self._current_grid_size = 16
        self._current_model = None
        self._goal_handle = None

        # ── SocketIO 클라이언트 (Flask 연결) ──
        self.sio = socketio.Client(reconnection=True)
        self._register_sio_handlers()

        threading.Thread(target=self._connect_flask, daemon=True).start()
        self.get_logger().info('Bridge 노드 시작')

    # ════════════════════════════════════════════
    #  SocketIO → Flask 연결
    # ════════════════════════════════════════════

    def _connect_flask(self):
        flask_url = 'http://localhost:5000'
        try:
            self.sio.connect(flask_url, namespaces=['/bridge'])
            self.get_logger().info(f'Flask 연결 성공: {flask_url}')
        except Exception as e:
            self.get_logger().error(f'Flask 연결 실패: {e}')

    def _register_sio_handlers(self):

        @self.sio.on('connect', namespace='/bridge')
        def on_connect():
            self.get_logger().info('SocketIO /bridge 연결됨')

        @self.sio.on('disconnect', namespace='/bridge')
        def on_disconnect():
            self.get_logger().warn('SocketIO /bridge 연결 해제됨')

        # ── 브라우저에서 전달된 이벤트 ──

        @self.sio.on('upload_image', namespace='/bridge')
        def on_upload_image(data):
            self.get_logger().info('이미지 분석 요청 수신')
            self._call_process_mosaic(data)

        @self.sio.on('update_grid', namespace='/bridge')
        def on_update_grid(data):
            self.get_logger().info('격자 수정 수신')
            self._current_grid_json = data.get('grid_json', '')
            self.sio.emit('grid_updated', {'grid_json': self._current_grid_json},
                          namespace='/bridge')

        @self.sio.on('start_assembly', namespace='/bridge')
        def on_start_assembly(data):
            self.get_logger().info('조립 시작 요청 수신')
            grid_json = data.get('grid_json', self._current_grid_json)
            grid_size = int(data.get('grid_size0', self._current_grid_size))
            self._publish_verify_original(grid_json, grid_size)
            self._call_sequence_plan(grid_json, grid_size)

        @self.sio.on('pause', namespace='/bridge')
        def on_pause():
            self.get_logger().info('일시정지 요청')
            # TODO: RobotController에 일시정지 전달

        @self.sio.on('resume', namespace='/bridge')
        def on_resume():
            self.get_logger().info('재개 요청')
            # TODO: RobotController에 재개 전달

    # ════════════════════════════════════════════
    #  Bridge → ImageProcessor (ROS2 서비스)
    # ════════════════════════════════════════════

    def _call_process_mosaic(self, data):
        request = ProcessMosaic.Request()

        # base64 이미지 → sensor_msgs/Image 변환
        image_data = data.get('image_data', '')
        image_bytes = base64.b64decode(image_data)
        nparr = np.frombuffer(image_bytes, np.uint8)
        cv_image = cv2.imdecode(nparr, cv2.IMREAD_COLOR)
        request.input_image = self._bridge.cv2_to_imgmsg(cv_image, encoding='bgr8')

        request.grid_size = int(data.get('grid_size', 16))
        request.output_width = int(data.get('output_width', 512))
        request.output_height = int(data.get('output_height', 512))
        request.fixed_axis = ''
        request.fixed_axis_value = 0.0
        request.compute_robot_coordinates = data.get('compute_coordinates', False)

        future = self.image_client.call_async(request)
        future.add_done_callback(self._on_mosaic_result)

    def _on_mosaic_result(self, future):
        try:
            response = future.result()
            if response.success:
                self._current_model = response.model
                # BlockModel cells → grid_json (Flask 호환)
                grid_size = response.model.grid_size
                grid = [[''] * grid_size for _ in range(grid_size)]
                for cell in response.model.cells:
                    grid[cell.row][cell.col] = cell.color
                grid_json = json.dumps(grid)
                self._current_grid_json = grid_json

                self.sio.emit('analysis_result', {
                    'success': True,
                    'grid_json': grid_json,
                    'error_message': '',
                }, namespace='/bridge')
            else:
                self.sio.emit('analysis_result', {
                    'success': False,
                    'grid_json': '',
                    'error_message': response.message,
                }, namespace='/bridge')
        except Exception as e:
            self.get_logger().error(f'ProcessMosaic 호출 실패: {e}')
            self.sio.emit('analysis_result', {
                'success': False,
                'grid_json': '',
                'error_message': str(e),
            }, namespace='/bridge')

    # ════════════════════════════════════════════
    #  Bridge → VerifyNode (ROS2 토픽)
    # ════════════════════════════════════════════

    def _publish_verify_original(self, grid_json, grid_size):
        if self._current_model is not None:
            self.verify_pub.publish(self._current_model)
            self.get_logger().info('기준 모델 토픽 발행 완료')
        else:
            self.get_logger().warn(
                '기준 모델이 없습니다 (이미지 분석을 먼저 실행하세요)')

    # ════════════════════════════════════════════
    #  Bridge → Sequencer (ROS2 서비스)
    # ════════════════════════════════════════════

    def _call_sequence_plan(self, grid_json, grid_size):
        request = SequencePlan.Request()
        request.grid_json = grid_json
        request.grid_size = grid_size

        future = self.sequence_client.call_async(request)
        future.add_done_callback(self._on_sequence_result)

    def _on_sequence_result(self, future):
        try:
            response = future.result()
            if not response.success:
                self.sio.emit('assembly_error', {
                    'failed_step': -1,
                    'error_message': response.error_message,
                }, namespace='/bridge')
                return
            self._send_action_goal(response.action_queue_json)
        except Exception as e:
            self.get_logger().error(f'SequencePlan 호출 실패: {e}')
            self.sio.emit('assembly_error', {
                'failed_step': -1,
                'error_message': str(e),
            }, namespace='/bridge')

    # ════════════════════════════════════════════
    #  Bridge → RobotController (ROS2 액션)
    # ════════════════════════════════════════════

    def _send_action_goal(self, action_queue_json):
        goal = ExecuteQueue.Goal()
        goal.action_queue_json = action_queue_json

        self.robot_action_client.wait_for_server(timeout_sec=5.0)
        send_future = self.robot_action_client.send_goal_async(
            goal, feedback_callback=self._on_robot_feedback)
        send_future.add_done_callback(self._on_goal_response)

        self.sio.emit('assembly_started', {}, namespace='/bridge')

    def _on_goal_response(self, future):
        goal_handle = future.result()
        if not goal_handle.accepted:
            self.get_logger().warn('액션 골 거부됨')
            self.sio.emit('assembly_error', {
                'failed_step': -1,
                'error_message': '로봇이 작업을 거부했습니다.',
            }, namespace='/bridge')
            return

        self._goal_handle = goal_handle
        result_future = goal_handle.get_result_async()
        result_future.add_done_callback(self._on_robot_result)

    def _on_robot_feedback(self, feedback_msg):
        fb = feedback_msg.feedback
        data = {
            'current_step': fb.current_step,
            'total_steps': fb.total_steps,
            'current_action': fb.current_action,
            'current_color': fb.current_color,
            'current_target': list(fb.current_target),
        }
        db.insert_placement(fb.current_step, fb.current_color, list(fb.current_target))
        self.sio.emit('assembly_progress', data, namespace='/bridge')

    def _on_robot_result(self, future):
        result = future.result().result
        if result.success:
            self.sio.emit('assembly_done', {
                'completed_steps': result.completed_steps,
            }, namespace='/bridge')
        else:
            db.insert_error(result.failed_step, 'ACTION_FAIL', result.error_message)
            self.sio.emit('assembly_error', {
                'failed_step': result.failed_step,
                'error_message': result.error_message,
            }, namespace='/bridge')

    # ════════════════════════════════════════════
    #  WebcamNode → Bridge (ROS2 토픽 구독)
    # ════════════════════════════════════════════

    def _on_webcam_error(self, msg):
        self.get_logger().warn(
            f'웹캠 에러 수신: step={msg.step} ({msg.row},{msg.col}) '
            f'{msg.expected_color}→{msg.detected_color}')

        self.cancel_assembly()

        db.insert_error(msg.step, 'WEBCAM_DETECT', msg.message)

        self.sio.emit('assembly_error', {
            'failed_step': msg.step,
            'error_message': f'색상 불일치: ({msg.row},{msg.col}) '
                             f'{msg.expected_color}→{msg.detected_color}',
        }, namespace='/bridge')

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
        node.sio.disconnect()
        node.destroy_node()
        rclpy.shutdown()

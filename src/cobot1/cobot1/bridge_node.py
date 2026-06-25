import base64       # Flask에서 오는 이미지가 base64 인코딩이므로 디코딩에 사용
import json         # grid_json 등 JSON 문자열 ↔ Python 객체 변환
import threading    # Flask 연결을 별도 스레드에서 실행하기 위해 사용

import cv2          # base64 → OpenCV 이미지 변환에 사용
import numpy as np  # cv2.imdecode가 numpy 배열을 입력으로 받음
import rclpy
from rclpy.node import Node
from rclpy.action import ActionClient   # 로봇 제어용 액션 클라이언트
from rclpy.qos import DurabilityPolicy, QoSProfile, ReliabilityPolicy  # QoS 설정
import socketio      # Flask 서버와 실시간 양방향 통신 (WebSocket 기반)
from cv_bridge import CvBridge  # OpenCV 이미지 ↔ ROS2 sensor_msgs/Image 변환

# ── 커스텀 인터페이스 ──
from cobot1_interfaces.srv import ProcessMosaic, SequencePlan  # 서비스 타입
from cobot1_interfaces.action import Assembly                   # 액션 타입
from cobot1_interfaces.msg import BlockModel, WebcamError       # 메시지 타입

from . import db  # DB 기록 모듈 (같은 패키지 내 db.py)


class BridgeNode(Node):
    """
    Flask ↔ ROS2 중계 노드.

    역할: 브라우저(Flask)에서 오는 이벤트를 받아
    ROS2 서비스/액션/토픽으로 변환하고,
    ROS2 노드들의 응답을 다시 Flask로 전달한다.

    통신 흐름:
        [브라우저] ←SocketIO→ [Flask] ←SocketIO→ [BridgeNode] ←ROS2→ [각 노드]
    """

    def __init__(self):
        super().__init__('bridge')  # ROS2 노드 이름: 'bridge'

        # ══════════════════════════════════════
        #  ROS2 통신 인터페이스 초기화
        # ══════════════════════════════════════

        # 서비스 클라이언트: 요청-응답 패턴 (동기적 1회 호출)
        # ImageProcessorNode에 이미지 분석 요청
        self.image_client = self.create_client(ProcessMosaic, '/image/analyze')
        # SequencerNode에 조립 순서 계획 요청
        self.sequence_client = self.create_client(SequencePlan, '/sequence/plan')

        # 액션 클라이언트: 장시간 작업 + 중간 피드백 + 취소 가능
        # RobotControllerNode에 블록 배치 실행 요청
        self.robot_action_client = ActionClient(self, Assembly, '/execute_queue')

        # 퍼블리셔: 토픽에 메시지 발행 (1:N 브로드캐스트)
        # TRANSIENT_LOCAL: 구독자가 나중에 연결돼도 마지막 메시지를 받을 수 있음
        model_qos = QoSProfile(depth=1)
        model_qos.reliability = ReliabilityPolicy.RELIABLE      # 메시지 유실 방지
        model_qos.durability = DurabilityPolicy.TRANSIENT_LOCAL  # 늦은 구독자에게도 전달
        # VerifyNode에 기준 모델(완성형 설계도)을 발행
        self.verify_pub = self.create_publisher(
            BlockModel, '/vision/expected_model', model_qos)

        # 구독: 토픽에서 메시지 수신
        # WebcamNode가 실시간 모니터링 중 에러를 발견하면 여기서 수신
        self.webcam_error_sub = self.create_subscription(
            WebcamError, '/webcam/error', self._on_webcam_error, 10)

        # ══════════════════════════════════════
        #  내부 상태
        # ══════════════════════════════════════

        self._bridge = CvBridge()           # OpenCV ↔ ROS2 이미지 변환기
        self._current_grid_json = ''        # 현재 격자 데이터 (JSON 문자열)
        self._current_grid_size = 16        # 현재 격자 크기 (N×N)
        self._current_model = None          # 마지막 분석 결과 BlockModel
        self._current_image_data = None     # 최초 업로드된 원본 이미지 데이터 (재분석용)
        self._color_override = None         # 사용자가 수정한 색상 배열 (grid_json 파싱 결과)
        self._goal_handle = None            # 현재 실행 중인 액션 핸들 (취소용)
        self._current_tasks = []            # 현재 실행 중인 AssemblyTask 목록 (피드백 좌표 조회용)

        # ══════════════════════════════════════
        #  Flask 연결 (SocketIO)
        # ══════════════════════════════════════

        # SocketIO 클라이언트 생성 (reconnection=True: 끊기면 자동 재연결)
        self.sio = socketio.Client(reconnection=True)
        # SocketIO 이벤트 핸들러 등록 (브라우저 → Flask → Bridge 이벤트)
        self._register_sio_handlers()

        # Flask 연결을 별도 데몬 스레드에서 시도
        # daemon=True: 메인 프로세스 종료 시 스레드도 자동 종료
        threading.Thread(target=self._connect_flask, daemon=True).start()
        self.get_logger().info('Bridge 노드 시작')

    # ════════════════════════════════════════════
    #  Flask SocketIO 연결
    # ════════════════════════════════════════════

    def _connect_flask(self):
        """Flask 서버에 SocketIO로 연결 시도. 실패 시 5초 간격으로 재시도."""
        flask_url = 'http://localhost:5000'
        import time
        while True:
            try:
                self.sio.connect(flask_url, namespaces=['/bridge'])
                self.get_logger().info(f'Flask 연결 성공: {flask_url}')
                break  # 연결 성공 시 루프 탈출
            except Exception as e:
                self.get_logger().warn(f'Flask 연결 대기 중... ({e})')
                time.sleep(5)

    def _register_sio_handlers(self):
        """Flask로부터 오는 SocketIO 이벤트에 대한 핸들러를 등록."""

        # ── 연결/해제 이벤트 ──

        @self.sio.on('connect', namespace='/bridge')
        def on_connect():
            self.get_logger().info('SocketIO /bridge 연결됨')

        @self.sio.on('disconnect', namespace='/bridge')
        def on_disconnect():
            self.get_logger().warn('SocketIO /bridge 연결 해제됨')

        # ── 브라우저에서 전달되는 이벤트들 ──

        @self.sio.on('upload_image', namespace='/bridge')
        def on_upload_image(data):
            """사용자가 이미지를 업로드하면 ImageProcessorNode에 분석 요청."""
            self.get_logger().info('이미지 분석 요청 수신')
            # 원본 이미지 데이터 저장 (나중에 색상 수정 시 재분석에 사용)
            self._current_image_data = data
            self._color_override = None  # 최초 분석이므로 색상 오버라이드 없음
            self._call_process_mosaic(data)

        @self.sio.on('update_grid', namespace='/bridge')
        def on_update_grid(data):
            """사용자가 브라우저에서 격자를 수정하면 /image/analyze 재호출.

            sequence.md 흐름:
            1) 수정된 색상 저장
            2) 원본 이미지로 /image/analyze 서비스 재호출
            3) 응답 모델에 사용자 수정 색상 덮어씀
            """
            self.get_logger().info('격자 수정 수신 → /image/analyze 재호출')
            self._current_grid_json = data.get('grid_json', '')

            if self._current_image_data is None:
                self.get_logger().warn('원본 이미지가 없습니다 (이미지를 먼저 업로드하세요)')
                return

            # 사용자가 수정한 색상 배열을 저장 (재분석 응답 시 덮어쓸 용도)
            self._color_override = json.loads(self._current_grid_json)
            # 원본 이미지로 /image/analyze 재호출
            self._call_process_mosaic(self._current_image_data)

        @self.sio.on('start_assembly', namespace='/bridge')
        def on_start_assembly(data):
            """사용자가 '조립 시작' 버튼을 누르면 실행되는 메인 흐름.
            1) VerifyNode에 기준 모델 발행
            2) SequencerNode에 조립 계획 요청 → 로봇 실행으로 이어짐
            """
            self.get_logger().info('조립 시작 요청 수신')
            grid_json = data.get('grid_json', self._current_grid_json)
            grid_size = int(data.get('grid_size0', self._current_grid_size))
            self._publish_verify_original(grid_json, grid_size)  # 1) 기준 모델 발행
            self._call_sequence_plan(grid_json, grid_size)       # 2) 조립 계획 요청

        @self.sio.on('pause', namespace='/bridge')
        def on_pause():
            self.get_logger().info('일시정지 요청')
            # TODO: RobotController에 일시정지 전달

        @self.sio.on('resume', namespace='/bridge')
        def on_resume():
            self.get_logger().info('재개 요청')
            # TODO: RobotController에 재개 전달

    # ════════════════════════════════════════════
    #  Bridge → ImageProcessorNode (ROS2 서비스 호출)
    # ════════════════════════════════════════════

    def _call_process_mosaic(self, data):
        """Flask에서 받은 이미지를 ImageProcessorNode의 ProcessMosaic 서비스로 전달.

        Flask는 base64 문자열로 이미지를 보내지만,
        ROS2 서비스는 sensor_msgs/Image를 요구하므로 변환이 필요하다.
        변환 과정: base64 문자열 → bytes → numpy 배열 → OpenCV 이미지 → ROS2 Image
        """
        request = ProcessMosaic.Request()

        # base64 디코딩 → OpenCV 이미지로 변환
        # 브라우저에서 오는 데이터는 "data:image/png;base64,iVBOR..." 형식이므로
        # 쉼표 뒤의 순수 base64 부분만 추출
        image_data = data.get('image_data', '')
        if ',' in image_data:
            image_data = image_data.split(',', 1)[1]
        image_bytes = base64.b64decode(image_data)          # base64 → bytes
        nparr = np.frombuffer(image_bytes, np.uint8)        # bytes → numpy 배열
        cv_image = cv2.imdecode(nparr, cv2.IMREAD_COLOR)    # numpy → OpenCV BGR 이미지
        # OpenCV 이미지 → ROS2 sensor_msgs/Image 메시지로 변환
        request.input_image = self._bridge.cv2_to_imgmsg(cv_image, encoding='bgr8')

        # 요청 파라미터 설정
        request.grid_size = int(data.get('grid_size', 16))      # 격자 크기 (N×N)
        request.output_width = int(data.get('output_width', 512))
        request.output_height = int(data.get('output_height', 512))
        request.fixed_axis = ''             # 로봇 좌표 축 (비어있으면 config 기본값 사용)
        request.fixed_axis_value = 0.0
        request.compute_robot_coordinates = data.get('compute_coordinates', False)

        # 비동기 호출: 응답이 오면 _on_mosaic_result 콜백 실행
        future = self.image_client.call_async(request)
        future.add_done_callback(self._on_mosaic_result)

    def _on_mosaic_result(self, future):
        """ImageProcessorNode 응답 처리.

        응답의 BlockModel에는 각 셀의 색상/좌표 정보가 구조화되어 있지만,
        Flask는 단순한 JSON 2차원 배열을 기대하므로 변환해서 전달한다.
        """
        try:
            response = future.result()
            if response.success:
                model = response.model

                # 사용자가 색상을 수정한 경우, 모델의 셀 색상을 오버라이드
                if self._color_override is not None:
                    override = self._color_override
                    for cell in model.cells:
                        if cell.row < len(override) and cell.col < len(override[0]):
                            new_color = override[cell.row][cell.col]
                            if new_color:
                                cell.color = new_color
                                cell.occupied = True
                            else:
                                cell.color = ''
                                cell.occupied = False
                    self._color_override = None  # 오버라이드 적용 완료
                    self.get_logger().info('사용자 색상 수정 반영 완료')

                # 분석 결과 BlockModel을 저장 (나중에 VerifyNode에 발행할 때 사용)
                self._current_model = model

                # BlockModel → 2차원 색상 배열로 변환 (Flask 호환)
                # 예: [["red","blue"],["green","white"]]
                grid_size = model.grid_size
                grid = [[''] * grid_size for _ in range(grid_size)]
                for cell in model.cells:
                    grid[cell.row][cell.col] = cell.color
                grid_json = json.dumps(grid)
                self._current_grid_json = grid_json

                # 분석 성공 결과를 Flask(→브라우저)에 전송
                self.sio.emit('analysis_result', {
                    'success': True,
                    'grid_json': grid_json,
                    'error_message': '',
                }, namespace='/bridge')
            else:
                # 분석 실패 시 에러 메시지 전달
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
    #  Bridge → VerifyNode (ROS2 토픽 발행)
    # ════════════════════════════════════════════

    def _publish_verify_original(self, grid_json, grid_size):
        """조립의 '정답'이 되는 기준 모델을 VerifyNode에 발행.

        VerifyNode는 이 모델을 저장해두고,
        나중에 카메라로 촬영한 실제 조립 결과와 비교해서 일치율을 판정한다.
        TRANSIENT_LOCAL QoS 덕분에 VerifyNode가 나중에 시작돼도 이 메시지를 받을 수 있다.
        """
        if self._current_model is not None:
            self.verify_pub.publish(self._current_model)
            self.get_logger().info('기준 모델 토픽 발행 완료')
        else:
            self.get_logger().warn(
                '기준 모델이 없습니다 (이미지 분석을 먼저 실행하세요)')

    # ════════════════════════════════════════════
    #  Bridge → SequencerNode (ROS2 서비스 호출)
    # ════════════════════════════════════════════

    def _call_sequence_plan(self, grid_json, grid_size):
        """격자 데이터 + BlockModel을 SequencerNode에 보내 조립 순서(Action Queue)를 생성 요청.

        Sequencer는 레이어 아래→위 순서로 정렬된 동작 큐를 JSON으로 반환한다.
        BlockModel에 각 셀의 로봇 좌표(target)가 포함되어 있으므로 함께 전달한다.
        성공하면 _on_sequence_result에서 RobotController에 실행을 요청한다.
        """
        request = SequencePlan.Request()
        request.grid_json = grid_json   # 2차원 색상 배열 JSON
        request.grid_size = grid_size   # 격자 크기
        if self._current_model is not None:
            request.model = self._current_model  # 셀별 로봇 좌표 포함

        future = self.sequence_client.call_async(request)
        future.add_done_callback(self._on_sequence_result)

    def _on_sequence_result(self, future):
        """SequencerNode 응답 처리.

        성공 시: action_queue_json을 RobotController에 전달해서 실행
        실패 시: Flask에 에러 전송
        """
        try:
            response = future.result()
            if not response.success:
                self.sio.emit('assembly_error', {
                    'failed_step': -1,
                    'error_message': response.error_message,
                }, namespace='/bridge')
                return
            # 조립 계획 성공 → 로봇에 실행 명령
            self._send_action_goal(response.tasks)
        except Exception as e:
            self.get_logger().error(f'SequencePlan 호출 실패: {e}')
            self.sio.emit('assembly_error', {
                'failed_step': -1,
                'error_message': str(e),
            }, namespace='/bridge')

    # ════════════════════════════════════════════
    #  Bridge → RobotControllerNode (ROS2 액션 호출)
    # ════════════════════════════════════════════
    #
    #  액션은 서비스와 달리 3단계로 구성:
    #    1) Goal 전송 → 수락/거부 응답 (_on_goal_response)
    #    2) 실행 중 피드백 수신 (_on_robot_feedback) — 진행률, 현재 동작 등
    #    3) 최종 결과 수신 (_on_robot_result) — 성공/실패
    #  또한 실행 중 취소가 가능 (cancel_assembly)

    def _send_action_goal(self, tasks):
        """RobotControllerNode에 동작 큐 실행을 요청 (액션 Goal 전송)."""
        goal = Assembly.Goal()
        goal.tasks = tasks
        self._current_tasks = list(tasks)

        # 액션 서버가 준비될 때까지 최대 5초 대기
        self.robot_action_client.wait_for_server(timeout_sec=5.0)
        # 비동기 Goal 전송, 피드백 콜백 등록
        send_future = self.robot_action_client.send_goal_async(
            goal, feedback_callback=self._on_robot_feedback)
        send_future.add_done_callback(self._on_goal_response)

        # Flask에 조립 시작 알림
        self.sio.emit('assembly_started', {}, namespace='/bridge')

    def _on_goal_response(self, future):
        """액션 서버의 Goal 수락/거부 응답 처리."""
        goal_handle = future.result()
        if not goal_handle.accepted:
            # 거부됨 (예: 로봇이 다른 작업 중)
            self.get_logger().warn('액션 골 거부됨')
            self.sio.emit('assembly_error', {
                'failed_step': -1,
                'error_message': '로봇이 작업을 거부했습니다.',
            }, namespace='/bridge')
            return

        # 수락됨 → goal_handle 저장 (나중에 취소할 때 사용)
        self._goal_handle = goal_handle
        # 최종 결과를 비동기로 대기
        result_future = goal_handle.get_result_async()
        result_future.add_done_callback(self._on_robot_result)

    def _on_robot_feedback(self, feedback_msg):
        """로봇 실행 중 피드백 수신 — 세부 동작 단계마다 호출됨.

        피드백 내용: 진행률, 현재 인덱스, 작업 유형, 색상, 세부 단계명
        TASK_COMPLETE 단계에서 DB에 배치 기록 저장.
        """
        fb = feedback_msg.feedback
        data = {
            'current_step': fb.current_index,
            'total_steps': fb.total_count,
            'current_action': fb.task_type,
            'current_color': fb.color,
            'step': fb.step,
            'progress': fb.progress,
        }
        if fb.step == 'TASK_COMPLETE' and 0 <= fb.current_index < len(self._current_tasks):
            t = self._current_tasks[fb.current_index]
            db.insert_placement(fb.current_index, fb.color, list(t.target_pose[:3]))
        self.sio.emit('assembly_progress', data, namespace='/bridge')

    def _on_robot_result(self, future):
        """로봇 실행 최종 결과 처리 — 전체 큐 완료 또는 실패 시 호출."""
        result = future.result().result
        if result.success:
            # 모든 동작 완료
            self.sio.emit('assembly_done', {
                'completed_steps': result.completed_steps,
            }, namespace='/bridge')
        else:
            # 실패한 스텝과 에러 메시지를 DB에 기록하고 Flask에 전달
            db.insert_error(result.failed_step, 'ACTION_FAIL', result.error_message)
            self.sio.emit('assembly_error', {
                'failed_step': result.failed_step,
                'error_message': result.error_message,
            }, namespace='/bridge')

    # ════════════════════════════════════════════
    #  WebcamNode → Bridge (ROS2 토픽 구독)
    # ════════════════════════════════════════════

    def _on_webcam_error(self, msg):
        """WebcamNode가 실시간 모니터링 중 색상 불일치를 감지하면 호출.

        조립 중에 잘못된 블록이 놓이면:
        1) 로봇 동작 즉시 취소
        2) DB에 에러 기록
        3) Flask에 에러 전달 (브라우저에 알림 표시)
        """
        self.get_logger().warn(
            f'웹캠 에러 수신: step={msg.step} ({msg.row},{msg.col}) '
            f'{msg.expected_color}→{msg.detected_color}')

        # 로봇 동작 취소
        self.cancel_assembly()

        # DB에 에러 기록
        db.insert_error(msg.step, 'WEBCAM_DETECT', msg.message)

        # Flask에 에러 전달
        self.sio.emit('assembly_error', {
            'failed_step': msg.step,
            'error_message': f'색상 불일치: ({msg.row},{msg.col}) '
                             f'{msg.expected_color}→{msg.detected_color}',
        }, namespace='/bridge')

    def cancel_assembly(self):
        """진행 중인 로봇 액션을 취소."""
        if self._goal_handle is not None:
            self._goal_handle.cancel_goal_async()
            self.get_logger().info('액션 취소 요청')


def main(args=None):
    """노드 진입점 — setup.py의 console_scripts에서 호출됨."""
    rclpy.init(args=args)           # ROS2 초기화
    node = BridgeNode()             # 노드 인스턴스 생성
    try:
        rclpy.spin(node)            # 콜백 대기 루프 (Ctrl+C까지 실행)
    except KeyboardInterrupt:
        pass
    finally:
        node.sio.disconnect()       # Flask SocketIO 연결 해제
        node.destroy_node()         # 노드 정리 (구독/퍼블리셔/서비스 해제)
        rclpy.shutdown()            # ROS2 종료

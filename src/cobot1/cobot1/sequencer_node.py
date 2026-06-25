import json

import rclpy
from rclpy.node import Node

from cobot1_interfaces.srv import SequencePlan
from cobot1_interfaces.msg import AssemblyTask


class SequencerNode(Node):

    def __init__(self):
        super().__init__('sequencer')

        # 배치 좌표 파라미터 (나중에 실측값으로 교체)
        self.declare_parameter('start_y', 0.0)       # n1: 시작 y좌표
        self.declare_parameter('start_z', 0.0)       # n2: 시작 z좌표
        self.declare_parameter('cell_step', 0.025)    # n3: 셀 간 거리 (y축 방향)
        self.declare_parameter('fixed_x', 0.5)        # x축 고정값 (벽면 거리)
        # Place 자세 회전값 [a_deg, b_deg, c_deg] (Doosan Z-Y-Z Euler)
        self.declare_parameter('place_orientation', [0.0, 0.0, 0.0])
        # Pick 스테이션 좌표 [x, y, z, a, b, c] (블록 공급 위치)
        self.declare_parameter('pick_pose', [0.0, 0.0, 0.0, 0.0, 0.0, 0.0])

        self.srv = self.create_service(
            SequencePlan, '/sequence/plan', self.handle_plan)

        self.get_logger().info('Sequencer 노드 시작')

    def handle_plan(self, request, response):
        """grid_json을 받아 지그재그(boustrophedon) 순서의 AssemblyTask 배열을 생성.

        배치 규칙:
        - 이미지 좌하단(row=N-1, col=0)부터 시작
        - 한 행을 좌→우로 채운 뒤, 다음 행은 우→좌 (시간 단축)
        - col 방향 → 현실 y축 (좌→우: y 감소, 우→좌: y 증가)
        - row 방향 → 현실 z축 (아래→위)
        """
        self.get_logger().info(
            f'배치 계획 요청: grid_size={request.grid_size}')

        try:
            grid = json.loads(request.grid_json)
            grid_size = request.grid_size

            if len(grid) != grid_size:
                raise ValueError(
                    f'grid_json 행 수({len(grid)})가 grid_size({grid_size})와 불일치')

            # 파라미터 읽기
            start_y = self.get_parameter('start_y').value
            start_z = self.get_parameter('start_z').value
            cell_step = self.get_parameter('cell_step').value
            fixed_x = self.get_parameter('fixed_x').value
            place_orient = list(self.get_parameter('place_orientation').value)
            pick_pose = list(self.get_parameter('pick_pose').value)

            tasks = []
            step = 0

            # 아래→위 순서 (row N-1 → row 0)
            for layer, row in enumerate(range(grid_size - 1, -1, -1)):
                if layer % 2 == 0:
                    cols = range(grid_size)
                else:
                    cols = range(grid_size - 1, -1, -1)

                for col in cols:
                    color = grid[row][col]
                    if not color:
                        continue

                    y = start_y - col * cell_step
                    row_from_bottom = grid_size - 1 - row
                    z = start_z + row_from_bottom * cell_step

                    task = AssemblyTask()
                    task.task_type = AssemblyTask.PICK_PLACE
                    task.task_id = f'place_{step}'
                    task.color = color
                    task.source_pose = pick_pose
                    task.target_pose = [fixed_x, y, z] + place_orient
                    task.stack_index = 0

                    tasks.append(task)
                    step += 1

            response.success = True
            response.tasks = tasks
            response.error_message = ''
            self.get_logger().info(
                f'배치 계획 완료: {step}개 블록, {grid_size}행 지그재그')

        except Exception as e:
            response.success = False
            response.tasks = []
            response.error_message = str(e)
            self.get_logger().error(f'배치 계획 실패: {e}')

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

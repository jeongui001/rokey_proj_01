import rclpy
from rclpy.node import Node

from cobot1_interfaces.srv import SequencePlan
from cobot1_interfaces.msg import BlockTask


class SequencerNode(Node):

    def __init__(self):
        super().__init__('sequencer')

        # 그리드 크기 파라미터
        self.declare_parameter('grid_width', 24)
        self.declare_parameter('grid_height', 10)

        # 배치 좌표 파라미터
        self.declare_parameter('start_x', 332.0)
        self.declare_parameter('start_y_type1', 310.0)
        self.declare_parameter('start_y_type2', 302.05)
        self.declare_parameter('cell_pitch', 15.9)

        self.srv = self.create_service(
            SequencePlan, '/sequence/plan', self.handle_plan)

        self.get_logger().info('Sequencer 노드 시작')

    def handle_plan(self, request, response):
        """colors 배열을 받아 지그재그(boustrophedon) 순서의 BlockTask 배열을 생성.

        배치 규칙:
        - request.colors: grid_height × grid_width 크기의 row-major flat 배열
        - 아래 행부터 위로, 지그재그 순서로 순회
        - 빈 문자열('')인 셀은 건너뜀
        """
        grid_width = self.get_parameter('grid_width').value
        grid_height = self.get_parameter('grid_height').value

        self.get_logger().info(
            f'배치 계획 요청: {grid_width}x{grid_height} 그리드')

        try:
            expected = grid_width * grid_height
            if len(request.colors) != expected:
                raise ValueError(
                    f'colors 길이({len(request.colors)})가 '
                    f'grid 크기({expected})와 불일치')

            # flat 배열을 2D 그리드로 변환 (row-major)
            grid = []
            for r in range(grid_height):
                row = request.colors[r * grid_width:(r + 1) * grid_width]
                grid.append(row)

            tasks = []
            count = 0

            # 아래→위 순서 (row grid_height-1 → row 0), 지그재그
            for layer, row in enumerate(range(grid_height - 1, -1, -1)):
                if layer % 2 == 0:
                    cols = range(grid_width)
                else:
                    cols = range(grid_width - 1, -1, -1)

                for col in cols:
                    color = grid[row][col]
                    if not color:
                        continue

                    task = BlockTask()
                    task.color = color
                    task.block_type = 1  # placeholder
                    task.y_position = 0.0  # placeholder

                    tasks.append(task)
                    count += 1

            response.tasks = tasks
            response.error_message = ''
            self.get_logger().info(
                f'배치 계획 완료: {count}개 블록, 지그재그 순서')

        except Exception as e:
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

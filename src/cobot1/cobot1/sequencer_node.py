from itertools import product as iter_product

import rclpy
from rclpy.node import Node

from cobot1_interfaces.srv import SequencePlan
from cobot1_interfaces.msg import BlockTask


class SequencerNode(Node):

    def __init__(self):
        super().__init__('sequencer')

        self.declare_parameter('grid_width', 24)
        self.declare_parameter('grid_height', 10)
        self.declare_parameter('start_x', 332.0)
        self.declare_parameter('start_y_type1', 310.0)
        self.declare_parameter('start_y_type2', 302.05)
        self.declare_parameter('cell_pitch', 15.9)
        self.declare_parameter('beam_width', 5)
        self.declare_parameter('empty_color', 'empty')

        self.srv = self.create_service(
            SequencePlan, '/sequence/plan', self.handle_plan)
        self.get_logger().info('Sequencer 노드 시작')

    # ── 서비스 핸들러 ──

    def handle_plan(self, request, response):
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

            grid = []
            for r in range(grid_height):
                row = list(request.colors[r * grid_width:(r + 1) * grid_width])
                grid.append(row)

            empty_color = self.get_parameter('empty_color').value
            row_blocks = self._match_blocks(
                grid, grid_width, grid_height, empty_color)
            tasks = self._build_tasks(row_blocks, grid_width, grid_height)

            response.tasks = tasks
            response.error_message = ''
            self.get_logger().info(f'배치 계획 완료: {len(tasks)}개 블록')

        except Exception as e:
            response.tasks = []
            response.error_message = str(e)
            self.get_logger().error(f'배치 계획 실패: {e}')

        return response

    # ── 색상 런 추출 ──

    @staticmethod
    def _find_runs(row, empty_color='empty'):
        runs = []
        i = 0
        while i < len(row):
            color = row[i]
            if not color or color == empty_color:
                i += 1
                continue
            length = 1
            while i + length < len(row) and row[i + length] == color:
                length += 1
            if length >= 2:
                runs.append((color, length, i))
            i += length
        return runs

    # ── 분할 후보 생성 ──

    @staticmethod
    def _generate_partitions(n):
        if n == 0:
            return [[]]
        if n < 2:
            return []
        result = []
        for first in (2, 3):
            if n >= first:
                for rest in SequencerNode._generate_partitions(n - first):
                    result.append([first] + rest)
        return result

    # ── 내부 경계 계산 ──

    @staticmethod
    def _internal_boundaries(blocks, grid_width):
        bounds = set()
        for start, width, _, _ in blocks:
            bounds.add(start)
            bounds.add(start + width)
        bounds.discard(0)
        bounds.discard(grid_width)
        return bounds

    # ── 벽돌 규칙 loss ──

    @staticmethod
    def _block_loss(start, width, lower_bounds):
        a = start
        b = start + width
        hits = [p for p in lower_bounds if a <= p <= b]
        if len(hits) == 1 and hits[0] != a and hits[0] != b:
            return 0
        return 1

    # ── 분할 → 블록 리스트 변환 ──

    @staticmethod
    def _to_blocks(runs, combo):
        blocks = []
        for (color, _, start), partition in zip(runs, combo):
            col = start
            for w in partition:
                blocks.append((col, w, color, 1 if w == 2 else 2))
                col += w
        return blocks

    # ── 런별 분할 후보 ──

    def _run_partitions(self, runs):
        parts = []
        for color, length, start in runs:
            p = self._generate_partitions(length)
            if not p:
                raise ValueError(
                    f'길이 {length}의 런({color}, col {start})을 분할 불가')
            parts.append(p)
        return parts

    # ── Beam Search DP ──

    def _match_blocks(self, grid, grid_width, grid_height, empty_color):
        beam_width = self.get_parameter('beam_width').value
        bottom = grid_height - 1

        runs = self._find_runs(grid[bottom], empty_color)
        if not runs:
            return {r: [] for r in range(grid_height)}

        run_parts = self._run_partitions(runs)

        # 맨 아래 행: 유형2 블록 수 기준 상위 beam_width개
        candidates = []
        for combo in iter_product(*run_parts):
            blocks = self._to_blocks(runs, combo)
            type2_count = sum(1 for _, w, _, _ in blocks if w == 3)
            candidates.append((type2_count, blocks))
        candidates.sort(key=lambda x: x[0], reverse=True)

        beam = []
        for _, blocks in candidates[:beam_width]:
            bounds = self._internal_boundaries(blocks, grid_width)
            beam.append((0.0, {bottom: blocks}, bounds))

        # 나머지 행 (아래→위)
        for layer in range(1, grid_height):
            row = grid_height - 1 - layer
            weight = grid_height - layer

            runs = self._find_runs(grid[row], empty_color)
            if not runs:
                beam = [(loss, {**rd, row: []}, b) for loss, rd, b in beam]
                continue

            run_parts = self._run_partitions(runs)

            new_beam = []
            for prev_loss, prev_rd, lower_b in beam:
                for combo in iter_product(*run_parts):
                    blocks = self._to_blocks(runs, combo)
                    loss = sum(
                        self._block_loss(s, w, lower_b)
                        for s, w, _, _ in blocks)
                    total = prev_loss + loss * weight
                    bounds = self._internal_boundaries(blocks, grid_width)
                    new_beam.append((total, {**prev_rd, row: blocks}, bounds))

            new_beam.sort(key=lambda x: x[0])
            beam = new_beam[:beam_width]

        best_loss, best_rd, _ = beam[0]
        self.get_logger().info(f'블록 매칭 완료: loss={best_loss}')
        return best_rd

    # ── BlockTask 생성 (지그재그 + Y좌표) ──

    def _build_tasks(self, row_blocks, grid_width, grid_height):
        start_y_t1 = self.get_parameter('start_y_type1').value
        start_y_t2 = self.get_parameter('start_y_type2').value
        pitch = self.get_parameter('cell_pitch').value
        tasks = []

        for layer in range(grid_height):
            row = grid_height - 1 - layer
            blocks = row_blocks.get(row, [])
            if not blocks:
                continue

            y_pos = self._y_positions(blocks, start_y_t1, start_y_t2, pitch, grid_width)

            order = list(range(len(blocks)))
            if layer % 2 == 1:
                order = list(reversed(order))

            for i in order:
                _, _, color, btype = blocks[i]
                task = BlockTask()
                task.color = color
                task.block_type = btype
                task.y_position = y_pos[i]
                tasks.append(task)

        return tasks

    # ── Y좌표 계산 ──

    @staticmethod
    def _y_positions(blocks, start_y_t1, start_y_t2, pitch, grid_width):
        n = len(blocks)
        if n == 0:
            return []

        y = [0.0] * n
        rblock = blocks[-1]
        right_gap = grid_width - (rblock[0] + rblock[1])
        y[-1] = (start_y_t1 if rblock[3] == 1 else start_y_t2) - right_gap * pitch

        for i in range(n - 2, -1, -1):
            prev_type = blocks[i + 1][3]
            curr_type = blocks[i][3]
            if prev_type == curr_type == 1:
                factor = 2.0
            elif prev_type == curr_type == 2:
                factor = 3.0
            else:
                factor = 2.5
            gap = blocks[i + 1][0] - (blocks[i][0] + blocks[i][1])
            y[i] = y[i + 1] - pitch * (factor + gap)

        return y


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

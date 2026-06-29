#!/usr/bin/env python3
"""
qt_app/main.py
PySide6 기반 데스크탑 UI.
기존 Flask + SocketIO 서버(port 5000)에 접속하여 동작한다.
Flask 앱과 bridge_node가 실행 중이어야 한다.

실행:
  pip install PySide6 "python-socketio[client]"
  python src/qt_app/main.py
"""

import sys
import json
import base64

try:
    from PySide6.QtWidgets import (
        QApplication, QMainWindow, QWidget, QStackedWidget,
        QVBoxLayout, QHBoxLayout, QLabel, QPushButton, QSpinBox,
        QProgressBar, QTextEdit, QTableWidget, QTableWidgetItem,
        QHeaderView, QSizePolicy, QFileDialog, QGroupBox, QScrollArea,
    )
    from PySide6.QtCore import Qt, QThread, Signal, QPoint, QRect, QBuffer, QIODevice
    from PySide6.QtGui import QPixmap, QPainter, QColor, QPen, QBrush, QImage, QFont
except ImportError:
    print("PySide6가 설치되어 있지 않습니다.\npip install PySide6")
    sys.exit(1)

try:
    import socketio as sio_pkg
    HAS_SOCKETIO = True
except ImportError:
    HAS_SOCKETIO = False
    print("[경고] python-socketio 없음. pip install 'python-socketio[client]'")

# ── 색상 상수 ──────────────────────────────────────────────────────────────────

COLOR_HEX = {
    "red":    "#e3000b",
    "blue":   "#006cb7",
    "yellow": "#ffcd00",
    "green":  "#00a650",
}
COLOR_LABEL = {"red": "빨강", "blue": "파랑", "yellow": "노랑", "green": "초록"}
CELL_ASPECT_W = 15.9
CELL_ASPECT_H = 19.0

# ── 스타일시트 ─────────────────────────────────────────────────────────────────

STYLESHEET = """
QMainWindow, QWidget {
    background-color: #0d1117;
    color: #c9d1d9;
    font-family: sans-serif;
    font-size: 14px;
}
QGroupBox {
    background-color: #161b22;
    border: 1px solid #30363d;
    border-radius: 8px;
    margin-top: 12px;
    padding: 16px 12px 12px 12px;
    font-size: 15px;
    font-weight: bold;
    color: #e6edf3;
}
QGroupBox::title {
    subcontrol-origin: margin;
    left: 12px;
    padding: 0 4px;
}
QPushButton {
    background-color: #238636;
    color: white;
    border: none;
    border-radius: 4px;
    padding: 8px 16px;
}
QPushButton:hover  { background-color: #2ea043; }
QPushButton:disabled { background-color: #484f58; color: #8b949e; }
QPushButton#secondary {
    background-color: #21262d;
    border: 1px solid #30363d;
    color: #c9d1d9;
}
QPushButton#secondary:hover { background-color: #30363d; }
QSpinBox {
    background-color: #21262d;
    color: #c9d1d9;
    border: 1px solid #30363d;
    border-radius: 4px;
    padding: 4px 8px;
}
QLabel#hint { color: #8b949e; font-size: 12px; }
QLabel#status_bold { font-weight: bold; font-size: 15px; }
QTextEdit {
    background-color: #0d1117;
    color: #8b949e;
    border: 1px solid #30363d;
    border-radius: 4px;
    font-family: monospace;
    font-size: 12px;
}
QProgressBar {
    background-color: #21262d;
    border: none;
    border-radius: 10px;
    height: 20px;
    text-align: center;
    color: #c9d1d9;
}
QProgressBar::chunk {
    background-color: #1f6feb;
    border-radius: 10px;
}
QTableWidget {
    background-color: #21262d;
    border: 1px solid #30363d;
    border-radius: 4px;
    gridline-color: #30363d;
}
QHeaderView::section {
    background-color: #161b22;
    color: #8b949e;
    border: none;
    padding: 6px 10px;
    border-bottom: 1px solid #30363d;
}
QScrollArea { border: none; }
QScrollBar:vertical {
    background: #161b22;
    width: 8px;
    border-radius: 4px;
}
QScrollBar::handle:vertical {
    background: #30363d;
    border-radius: 4px;
}
"""

# ══════════════════════════════════════════════════════════════════════════════
# SocketIO 워커 (백그라운드 스레드)
# ══════════════════════════════════════════════════════════════════════════════

class SocketWorker(QThread):
    sig_analysis_result   = Signal(dict)
    sig_grid_updated      = Signal(dict)
    sig_block_plan        = Signal(dict)
    sig_assembly_started  = Signal(dict)
    sig_assembly_progress = Signal(dict)
    sig_assembly_done     = Signal(dict)
    sig_assembly_error    = Signal(dict)
    sig_system_log        = Signal(dict)
    sig_connected         = Signal()

    def __init__(self):
        super().__init__()
        self.sio = sio_pkg.Client(reconnection=False) if HAS_SOCKETIO else None
        if self.sio:
            self._bind()

    def _bind(self):
        sio = self.sio

        @sio.event
        def connect():
            self.sig_connected.emit()

        @sio.on("analysis_result")
        def _(d): self.sig_analysis_result.emit(d)

        @sio.on("grid_updated")
        def _(d): self.sig_grid_updated.emit(d)

        @sio.on("block_plan")
        def _(d): self.sig_block_plan.emit(d)

        @sio.on("assembly_started")
        def _(d={}): self.sig_assembly_started.emit(d or {})

        @sio.on("assembly_progress")
        def _(d): self.sig_assembly_progress.emit(d)

        @sio.on("assembly_done")
        def _(d): self.sig_assembly_done.emit(d)

        @sio.on("assembly_error")
        def _(d): self.sig_assembly_error.emit(d)

        @sio.on("system_log")
        def _(d): self.sig_system_log.emit(d)

    def run(self):
        if not self.sio:
            return
        try:
            self.sio.connect("http://localhost:5000")
            self.sio.wait()
        except Exception as e:
            print(f"[SocketIO] 연결 실패: {e}")

    def send(self, event, data=None):
        if not self.sio or not self.sio.connected:
            print(f"[SocketIO] 연결되지 않음 — {event} 전송 실패")
            return
        try:
            self.sio.emit(event, data)
        except Exception as e:
            print(f"[SocketIO] emit 실패 ({event}): {e}")

    def stop(self):
        if self.sio:
            try:
                self.sio.disconnect()
            except Exception:
                pass

# ══════════════════════════════════════════════════════════════════════════════
# 이미지 뷰어 (ROI 드래그 선택)
# ══════════════════════════════════════════════════════════════════════════════

class ImageViewer(QLabel):
    roi_changed = Signal(object)   # QRect(이미지 좌표) or None

    MAX_W = 480

    def __init__(self):
        super().__init__()
        self.setAlignment(Qt.AlignLeft | Qt.AlignTop)
        self.setCursor(Qt.CrossCursor)
        self.setStyleSheet("border: 1px solid #30363d; border-radius: 4px;")
        self._orig: QPixmap | None = None
        self._roi_label: QRect | None = None    # 라벨 좌표계
        self._roi_image: QRect | None = None    # 원본 이미지 좌표계
        self._drag_start: QPoint | None = None

    def load_from_path(self, path: str):
        self._orig = QPixmap(path)
        self._roi_label = None
        self._roi_image = None
        self._refresh_pixmap()

    def _refresh_pixmap(self):
        if self._orig is None:
            return
        scaled = self._orig.scaledToWidth(self.MAX_W, Qt.SmoothTransformation)
        self.setPixmap(scaled)
        self.setFixedSize(scaled.size())
        self.update()

    def _to_image_pos(self, p: QPoint) -> QPoint:
        if self._orig is None or self.pixmap() is None:
            return p
        lw, lh = self.pixmap().width(), self.pixmap().height()
        iw, ih = self._orig.width(), self._orig.height()
        x = max(0, min(iw - 1, int(p.x() * iw / lw)))
        y = max(0, min(ih - 1, int(p.y() * ih / lh)))
        return QPoint(x, y)

    def mousePressEvent(self, e):
        if self._orig is None:
            return
        self._drag_start = e.pos()
        self._roi_label = None
        self._roi_image = None
        self.roi_changed.emit(None)
        self.update()

    def mouseMoveEvent(self, e):
        if self._drag_start is None:
            return
        x0, y0 = self._drag_start.x(), self._drag_start.y()
        x1, y1 = e.pos().x(), e.pos().y()
        self._roi_label = QRect(
            QPoint(min(x0, x1), min(y0, y1)),
            QPoint(max(x0, x1), max(y0, y1)),
        )
        self.update()

    def mouseReleaseEvent(self, e):
        if self._drag_start is None:
            return
        if self._roi_label and self._roi_label.width() > 10 and self._roi_label.height() > 10:
            p0 = self._to_image_pos(self._roi_label.topLeft())
            p1 = self._to_image_pos(self._roi_label.bottomRight())
            self._roi_image = QRect(p0, p1)
            self.roi_changed.emit(self._roi_image)
        else:
            self._roi_label = None
            self._roi_image = None
            self.roi_changed.emit(None)
        self._drag_start = None
        self.update()

    def paintEvent(self, e):
        super().paintEvent(e)
        if self._roi_label:
            painter = QPainter(self)
            painter.setPen(QPen(QColor("#00e5ff"), 2, Qt.DashLine))
            painter.setBrush(QBrush(QColor(0, 229, 255, 20)))
            painter.drawRect(self._roi_label)

    def clear_roi(self):
        self._roi_label = None
        self._roi_image = None
        self.roi_changed.emit(None)
        self.update()

    def has_roi(self) -> bool:
        return self._roi_image is not None

    def get_image_b64(self) -> str:
        """ROI가 있으면 크롭, 없으면 전체를 base64 JPEG로 반환."""
        if self._orig is None:
            return ""
        src = self._orig.copy(self._roi_image) if self._roi_image else self._orig
        buf = QBuffer()
        buf.open(QIODevice.WriteOnly)
        src.save(buf, "JPEG", 92)
        raw = bytes(buf.data())
        return "data:image/jpeg;base64," + base64.b64encode(raw).decode()

# ══════════════════════════════════════════════════════════════════════════════
# 그리드 캔버스 (클릭/드래그 편집)
# ══════════════════════════════════════════════════════════════════════════════

class GridCanvas(QWidget):
    def __init__(self):
        super().__init__()
        self.grid_w = 16
        self.grid_h = 8
        self.grid: list[list[str]] = [[""] * 16 for _ in range(8)]
        self.block_map: list[list[int]] | None = None
        self.selected_color = "red"
        self._painting = False
        self._erase = False
        self._last_cell: tuple | None = None
        self.setMinimumWidth(480)
        self.setSizePolicy(QSizePolicy.Expanding, QSizePolicy.Fixed)
        self.setCursor(Qt.CrossCursor)
        self.setContextMenuPolicy(Qt.PreventContextMenu)
        self.setStyleSheet("border: 1px solid #30363d; border-radius: 4px;")
        self._recalc_height()

    def _recalc_height(self):
        w = max(self.width(), 480)
        h = max(self.grid_h,
                int(w * (self.grid_h * CELL_ASPECT_H) / (self.grid_w * CELL_ASPECT_W)))
        self.setFixedHeight(h)

    def resizeEvent(self, e):
        self._recalc_height()

    def _cell_size(self):
        return self.width() / self.grid_w, self.height() / self.grid_h

    def _pos_to_cell(self, x, y):
        cw, ch = self._cell_size()
        if cw <= 0 or ch <= 0:
            return None, None
        col, row = int(x / cw), int(y / ch)
        if 0 <= row < self.grid_h and 0 <= col < self.grid_w:
            return row, col
        return None, None

    def paintEvent(self, e):
        painter = QPainter(self)
        cw, ch = self._cell_size()
        painter.fillRect(self.rect(), QColor("#0d1117"))
        for r in range(self.grid_h):
            for c in range(self.grid_w):
                color = self.grid[r][c] if r < len(self.grid) and c < len(self.grid[r]) else ""
                painter.fillRect(
                    int(c * cw) + 1, int(r * ch) + 1,
                    max(1, int(cw) - 2), max(1, int(ch) - 2),
                    QColor(COLOR_HEX.get(color, "#333333")),
                )
        if self.block_map:
            painter.setPen(QPen(QColor("#bf00ff"), 3))
            drawn: set[int] = set()
            for r in range(self.grid_h):
                for c in range(self.grid_w):
                    bid = self.block_map[r][c]
                    if bid < 0 or bid in drawn:
                        continue
                    end_c = c
                    while end_c + 1 < self.grid_w and self.block_map[r][end_c + 1] == bid:
                        end_c += 1
                    painter.drawRect(
                        int(c * cw), int(r * ch),
                        int((end_c - c + 1) * cw), int(ch),
                    )
                    drawn.add(bid)

    def mousePressEvent(self, e):
        self._painting = True
        self._erase = (e.button() == Qt.RightButton)
        self._last_cell = None
        self._paint_at(e.pos())

    def mouseMoveEvent(self, e):
        if self._painting:
            self._paint_at(e.pos())

    def mouseReleaseEvent(self, e):
        self._painting = False

    def _paint_at(self, pos):
        row, col = self._pos_to_cell(pos.x(), pos.y())
        if row is None or self._last_cell == (row, col):
            return
        self._last_cell = (row, col)
        self.grid[row][col] = "" if self._erase else self.selected_color
        self.block_map = None
        self.update()

    def load(self, grid: list, grid_w: int, grid_h: int):
        self.grid_w = grid_w
        self.grid_h = grid_h
        self.grid = grid
        self.block_map = None
        self._recalc_height()
        self.update()

# ══════════════════════════════════════════════════════════════════════════════
# 설계도 캔버스 (읽기 전용, 진행 오버레이 포함)
# ══════════════════════════════════════════════════════════════════════════════

class BlueprintCanvas(QWidget):
    def __init__(self):
        super().__init__()
        self.grid_w = 16
        self.grid_h = 8
        self.grid: list[list[str]] = [[""] * 16 for _ in range(8)]
        self.block_map: list[list[int]] | None = None
        self.current_step = -1
        self.setMinimumWidth(480)
        self.setSizePolicy(QSizePolicy.Expanding, QSizePolicy.Fixed)
        self.setStyleSheet("border: 1px solid #30363d; border-radius: 4px;")
        self._recalc_height()

    def _recalc_height(self):
        w = max(self.width(), 480)
        h = max(self.grid_h,
                int(w * (self.grid_h * CELL_ASPECT_H) / (self.grid_w * CELL_ASPECT_W)))
        self.setFixedHeight(h)

    def resizeEvent(self, e):
        self._recalc_height()

    def _cell_size(self):
        return self.width() / self.grid_w, self.height() / self.grid_h

    def load(self, grid: list, grid_w: int, grid_h: int, block_map=None):
        self.grid_w = grid_w
        self.grid_h = grid_h
        self.grid = [row[:] for row in grid]
        self.block_map = block_map
        self.current_step = -1
        self._recalc_height()
        self.update()

    def set_progress(self, current_step: int):
        self.current_step = current_step
        self.update()

    def paintEvent(self, e):
        painter = QPainter(self)
        cw, ch = self._cell_size()
        painter.fillRect(self.rect(), QColor("#0d1117"))

        for r in range(self.grid_h):
            for c in range(self.grid_w):
                color = self.grid[r][c] if r < len(self.grid) and c < len(self.grid[r]) else ""
                bid = (self.block_map[r][c]
                       if self.block_map and r < len(self.block_map) and c < len(self.block_map[r])
                       else -1)
                is_done = bid >= 0 and self.current_step >= 0 and bid < self.current_step
                if color:
                    painter.setOpacity(0.25 if is_done else 1.0)
                    painter.fillRect(
                        int(c * cw) + 1, int(r * ch) + 1,
                        max(1, int(cw) - 2), max(1, int(ch) - 2),
                        QColor(COLOR_HEX.get(color, "#333333")),
                    )
                    painter.setOpacity(1.0)
                else:
                    painter.fillRect(
                        int(c * cw) + 1, int(r * ch) + 1,
                        max(1, int(cw) - 2), max(1, int(ch) - 2),
                        QColor("#333333"),
                    )

        if self.block_map:
            drawn: set[int] = set()
            for r in range(self.grid_h):
                for c in range(self.grid_w):
                    bid = (self.block_map[r][c]
                           if r < len(self.block_map) and c < len(self.block_map[r])
                           else -1)
                    if bid < 0 or bid in drawn:
                        continue
                    end_c = c
                    while end_c + 1 < self.grid_w and self.block_map[r][end_c + 1] == bid:
                        end_c += 1
                    is_done = self.current_step >= 0 and bid < self.current_step
                    is_current = bid == self.current_step
                    if is_current:
                        painter.setPen(QPen(QColor("#ffff00"), 3))
                    elif is_done:
                        painter.setPen(QPen(QColor("#3a3a3a"), 1))
                    else:
                        painter.setPen(QPen(QColor("#bf00ff"), 2))
                    painter.drawRect(
                        int(c * cw), int(r * ch),
                        int((end_c - c + 1) * cw), int(ch),
                    )
                    drawn.add(bid)


# ══════════════════════════════════════════════════════════════════════════════
# 블록 맵 빌드 (JS buildBlockMap과 동일한 로직)
# ══════════════════════════════════════════════════════════════════════════════

def build_block_map(blocks, grid, grid_w, grid_h):
    map_ = [[-1] * grid_w for _ in range(grid_h)]
    block_info = []
    t_idx = bid = 0
    for layer in range(grid_h):
        row = grid_h - 1 - layer
        runs, i = [], 0
        while i < grid_w:
            color = grid[row][i] if row < len(grid) and i < len(grid[row]) else ""
            if not color or color == "empty":
                i += 1
                continue
            length = 1
            while i + length < grid_w and grid[row][i + length] == color:
                length += 1
            if length >= 2:
                runs.append({"len": length, "start": i, "color": color})
            i += length
        total = sum(r["len"] for r in runs)
        row_tasks, covered = [], 0
        while t_idx < len(blocks) and covered < total:
            w = 2 if blocks[t_idx]["block_type"] == 1 else 3
            row_tasks.append({"w": w, "btype": blocks[t_idx]["block_type"]})
            covered += w
            t_idx += 1
        rt = 0
        for run in runs:
            col, rem = run["start"], run["len"]
            while rem > 0 and rt < len(row_tasks):
                w = row_tasks[rt]["w"]
                for c in range(col, min(col + w, grid_w)):
                    map_[row][c] = bid
                block_info.append({"color": run["color"], "type": row_tasks[rt]["btype"]})
                bid += 1
                col += w
                rem -= w
                rt += 1
    return map_, block_info

# ══════════════════════════════════════════════════════════════════════════════
# 페이지 1: 이미지 분석
# ══════════════════════════════════════════════════════════════════════════════

class Page1(QWidget):
    sig_analyze = Signal(dict)

    def __init__(self):
        super().__init__()
        layout = QVBoxLayout(self)
        layout.setContentsMargins(16, 16, 16, 16)
        layout.setSpacing(12)

        group = QGroupBox("1. 이미지 분석")
        vbox = QVBoxLayout(group)
        vbox.setSpacing(10)

        # 이미지 뷰어
        self.viewer = ImageViewer()
        self.viewer.roi_changed.connect(self._on_roi)
        vbox.addWidget(self.viewer)

        self.lbl_hint = QLabel("이미지 위를 드래그하여 분석 영역을 선택하세요. 선택하지 않으면 전체를 사용합니다.")
        self.lbl_hint.setObjectName("hint")
        self.lbl_hint.setWordWrap(True)
        self.lbl_hint.setVisible(False)
        vbox.addWidget(self.lbl_hint)

        # 파일 + ROI 초기화
        row1 = QHBoxLayout()
        self.btn_file = QPushButton("파일 선택")
        self.btn_file.clicked.connect(self._open_file)
        row1.addWidget(self.btn_file)
        self.btn_clear = QPushButton("ROI 초기화")
        self.btn_clear.setObjectName("secondary")
        self.btn_clear.setVisible(False)
        self.btn_clear.clicked.connect(self._clear_roi)
        row1.addWidget(self.btn_clear)
        row1.addStretch()
        vbox.addLayout(row1)

        # 그리드 크기 + 분석
        row2 = QHBoxLayout()
        row2.addWidget(QLabel("가로(열):"))
        self.spin_cols = QSpinBox()
        self.spin_cols.setRange(1, 32)
        self.spin_cols.setValue(16)
        row2.addWidget(self.spin_cols)
        row2.addWidget(QLabel("세로(행):"))
        self.spin_rows = QSpinBox()
        self.spin_rows.setRange(1, 32)
        self.spin_rows.setValue(8)
        row2.addWidget(self.spin_rows)
        self.btn_analyze = QPushButton("분석 요청")
        self.btn_analyze.setEnabled(False)
        self.btn_analyze.clicked.connect(self._on_analyze)
        row2.addWidget(self.btn_analyze)
        row2.addStretch()
        vbox.addLayout(row2)

        self.lbl_status = QLabel("")
        self.lbl_status.setObjectName("hint")
        vbox.addWidget(self.lbl_status)

        layout.addWidget(group)
        layout.addStretch()

    def _open_file(self):
        path, _ = QFileDialog.getOpenFileName(
            self, "이미지 선택", "", "이미지 (*.png *.jpg *.jpeg *.bmp)"
        )
        if not path:
            return
        self.viewer.load_from_path(path)
        self.lbl_hint.setVisible(True)
        self.btn_analyze.setEnabled(True)
        self.lbl_status.setText("")

    def _on_roi(self, roi):
        self.btn_clear.setVisible(roi is not None)

    def _clear_roi(self):
        self.viewer.clear_roi()

    def _on_analyze(self):
        self.btn_analyze.setEnabled(False)
        self.lbl_status.setText("분석 중...")
        self.sig_analyze.emit({
            "image_data": self.viewer.get_image_b64(),
            "grid_rows":  self.spin_rows.value(),
            "grid_cols":  self.spin_cols.value(),
            "roi_selected": self.viewer.has_roi(),
        })

    def on_failed(self, msg: str):
        self.btn_analyze.setEnabled(True)
        self.lbl_status.setText(f"분석 실패: {msg}")

    def reset_status(self):
        self.lbl_status.setText("")

# ══════════════════════════════════════════════════════════════════════════════
# 페이지 2: 분석 결과 편집
# ══════════════════════════════════════════════════════════════════════════════

class Page2(QWidget):
    sig_update = Signal(dict)
    sig_start  = Signal(dict)
    sig_back   = Signal()

    def __init__(self):
        super().__init__()
        layout = QVBoxLayout(self)
        layout.setContentsMargins(16, 16, 16, 16)
        layout.setSpacing(12)

        group = QGroupBox("2. 분석 결과 편집")
        vbox = QVBoxLayout(group)
        vbox.setSpacing(10)

        hint = QLabel("셀 클릭 → 색상 변경 / 우클릭 → 비우기")
        hint.setObjectName("hint")
        vbox.addWidget(hint)

        # 색상 팔레트
        palette_row = QHBoxLayout()
        self._pal_btns: dict[str, QPushButton] = {}
        for name, hex_c in COLOR_HEX.items():
            btn = QPushButton()
            btn.setFixedSize(32, 32)
            btn.setToolTip(COLOR_LABEL[name])
            btn.clicked.connect(lambda _, n=name: self._select_color(n))
            palette_row.addWidget(btn)
            self._pal_btns[name] = btn
        palette_row.addStretch()
        vbox.addLayout(palette_row)

        # 그리드 캔버스
        self.canvas = GridCanvas()
        vbox.addWidget(self.canvas)

        # 버튼
        btn_row = QHBoxLayout()
        self.btn_back = QPushButton("← 다시 분석")
        self.btn_back.setObjectName("secondary")
        self.btn_back.clicked.connect(self.sig_back.emit)
        self.btn_update = QPushButton("수정 반영")
        self.btn_update.clicked.connect(self._on_update)
        self.btn_start = QPushButton("조립 시작")
        self.btn_start.clicked.connect(self._on_start)
        btn_row.addWidget(self.btn_back)
        btn_row.addWidget(self.btn_update)
        btn_row.addWidget(self.btn_start)
        btn_row.addStretch()
        vbox.addLayout(btn_row)

        # 블록 요약 테이블
        self.table = QTableWidget(0, 4)
        self.table.setHorizontalHeaderLabels(["색상", "유형1 (2칸)", "유형2 (3칸)", "합계"])
        self.table.horizontalHeader().setSectionResizeMode(0, QHeaderView.Stretch)
        self.table.verticalHeader().setVisible(False)
        self.table.setEditTriggers(QTableWidget.NoEditTriggers)
        self.table.setVisible(False)
        vbox.addWidget(self.table)

        layout.addWidget(group)
        layout.addStretch()

        self._select_color("red")

    def _select_color(self, name: str):
        self.canvas.selected_color = name
        for n, btn in self._pal_btns.items():
            border = "#58a6ff" if n == name else "transparent"
            btn.setStyleSheet(
                f"background-color:{COLOR_HEX[n]}; border:2px solid {border}; border-radius:4px;"
            )

    def load_grid(self, grid, grid_w, grid_h):
        self.canvas.load(grid, grid_w, grid_h)
        self.table.setVisible(False)

    def _on_update(self):
        self.sig_update.emit({
            "grid_json": json.dumps(self.canvas.grid),
            "grid_rows": self.canvas.grid_h,
            "grid_cols": self.canvas.grid_w,
        })

    def _on_start(self):
        self.sig_start.emit({
            "grid_json": json.dumps(self.canvas.grid),
            "grid_rows": self.canvas.grid_h,
            "grid_cols": self.canvas.grid_w,
        })

    def show_block_plan(self, blocks: list):
        map_, block_info = build_block_map(
            blocks, self.canvas.grid, self.canvas.grid_w, self.canvas.grid_h
        )
        self.canvas.block_map = map_
        self.canvas.update()
        self._show_summary(block_info)

    def _show_summary(self, block_info: list):
        stats = {c: {"t1": 0, "t2": 0} for c in COLOR_HEX}
        for item in block_info:
            c = item["color"]
            if c in stats:
                if item["type"] == 1:
                    stats[c]["t1"] += 1
                else:
                    stats[c]["t2"] += 1
        active = [c for c in COLOR_HEX if stats[c]["t1"] + stats[c]["t2"] > 0]
        self.table.setRowCount(len(active) + 1)
        t1_total = t2_total = 0
        for i, c in enumerate(active):
            t1, t2 = stats[c]["t1"], stats[c]["t2"]
            t1_total += t1
            t2_total += t2
            for j, val in enumerate([f"■ {COLOR_LABEL[c]}", f"{t1}개", f"{t2}개", f"{t1+t2}개"]):
                item = QTableWidgetItem(val)
                item.setFlags(Qt.ItemIsEnabled)
                item.setTextAlignment(Qt.AlignCenter if j > 0 else Qt.AlignVCenter | Qt.AlignLeft)
                if j == 0:
                    item.setForeground(QColor(COLOR_HEX[c]))
                self.table.setItem(i, j, item)
        total_row = len(active)
        for j, val in enumerate(["합계", f"{t1_total}개", f"{t2_total}개", f"{t1_total+t2_total}개"]):
            item = QTableWidgetItem(val)
            item.setFlags(Qt.ItemIsEnabled)
            item.setTextAlignment(Qt.AlignCenter if j > 0 else Qt.AlignVCenter | Qt.AlignLeft)
            font = QFont(); font.setBold(True); item.setFont(font)
            self.table.setItem(total_row, j, item)
        self.table.resizeRowsToContents()
        self.table.setVisible(True)

# ══════════════════════════════════════════════════════════════════════════════
# 페이지 3: 진행 상황
# ══════════════════════════════════════════════════════════════════════════════

class Page3(QWidget):
    sig_pause  = Signal()
    sig_resume = Signal()
    sig_home   = Signal()

    def __init__(self):
        super().__init__()
        layout = QVBoxLayout(self)
        layout.setContentsMargins(16, 16, 16, 16)
        layout.setSpacing(12)

        # 설계도 섹션 (상단)
        bp_group = QGroupBox("설계도")
        bp_vbox = QVBoxLayout(bp_group)
        self.blueprint = BlueprintCanvas()
        bp_vbox.addWidget(self.blueprint)
        layout.addWidget(bp_group)

        # 진행 섹션
        prog_group = QGroupBox("3. 진행 상황")
        vbox = QVBoxLayout(prog_group)
        vbox.setSpacing(10)

        self.lbl_status = QLabel("조립 시작 중...")
        self.lbl_status.setObjectName("status_bold")
        vbox.addWidget(self.lbl_status)

        self.progress = QProgressBar()
        self.progress.setRange(0, 100)
        self.progress.setValue(0)
        vbox.addWidget(self.progress)

        self.lbl_steps = QLabel("0 / 0")
        self.lbl_steps.setObjectName("hint")
        vbox.addWidget(self.lbl_steps)

        btn_row = QHBoxLayout()
        self.btn_pause  = QPushButton("일시정지")
        self.btn_pause.setEnabled(False)
        self.btn_pause.clicked.connect(self.sig_pause.emit)
        self.btn_resume = QPushButton("재개")
        self.btn_resume.setEnabled(False)
        self.btn_resume.clicked.connect(self.sig_resume.emit)
        self.btn_home   = QPushButton("← 처음으로")
        self.btn_home.setObjectName("secondary")
        self.btn_home.clicked.connect(self.sig_home.emit)
        btn_row.addWidget(self.btn_pause)
        btn_row.addWidget(self.btn_resume)
        btn_row.addWidget(self.btn_home)
        btn_row.addStretch()
        vbox.addLayout(btn_row)
        layout.addWidget(prog_group)

        # 로그 섹션
        log_group = QGroupBox("시스템 로그")
        log_vbox = QVBoxLayout(log_group)
        self.log = QTextEdit()
        self.log.setReadOnly(True)
        self.log.setFixedHeight(220)
        log_vbox.addWidget(self.log)
        layout.addWidget(log_group)
        layout.addStretch()

    def load_blueprint(self, grid, grid_w, grid_h, block_map=None):
        self.blueprint.load(grid, grid_w, grid_h, block_map)

    def add_log(self, level: str, text: str):
        from datetime import datetime
        ts = datetime.now().strftime("%H시 %M분 %S초")
        colors = {"INFO": "#8b949e", "WARN": "#d29922", "ERROR": "#f85149"}
        color = colors.get(level, "#8b949e")
        self.log.append(f'<span style="color:{color}">[{ts}] [{level}] {text}</span>')

    def reset(self):
        self.lbl_status.setText("조립 시작 중...")
        self.progress.setValue(0)
        self.lbl_steps.setText("0 / 0")
        self.btn_pause.setEnabled(False)
        self.btn_resume.setEnabled(False)
        self.log.clear()

    def on_started(self):
        self.lbl_status.setText("조립 시작됨")
        self.btn_pause.setEnabled(True)
        self.btn_resume.setEnabled(True)
        self.add_log("INFO", "조립 시작됨")

    def on_progress(self, data: dict):
        total   = data.get("total_steps", 0)
        current = data.get("current_step", 0)
        pct = int(current / total * 100) if total > 0 else 0
        self.progress.setValue(pct)
        self.lbl_steps.setText(f"{current} / {total}")
        self.lbl_status.setText(
            f"진행 중 — {data.get('current_action', '')} {data.get('current_color', '')}"
        )
        self.blueprint.set_progress(current)

    def on_done(self, data: dict):
        self.lbl_status.setText("조립 완료")
        self.progress.setValue(100)
        self.btn_pause.setEnabled(False)
        self.btn_resume.setEnabled(False)
        self.add_log("INFO", f"조립 완료 — {data.get('completed_steps', 0)}개 블록")

    def on_error(self, data: dict):
        self.lbl_status.setText(f"오류 — Step {data.get('failed_step', '?')}")
        self.add_log("ERROR", f"오류: {data.get('error_message', '')}")

# ══════════════════════════════════════════════════════════════════════════════
# 메인 윈도우
# ══════════════════════════════════════════════════════════════════════════════

class MainWindow(QMainWindow):
    def __init__(self):
        super().__init__()
        self.setWindowTitle("레고 블록 자동 조립 시스템")
        self.setMinimumWidth(560)

        # SocketIO 워커
        self.worker = SocketWorker()

        # 페이지
        self.page1 = Page1()
        self.page2 = Page2()
        self.page3 = Page3()

        self._bind_worker()
        self.worker.start()

        self.stack = QStackedWidget()
        self.stack.addWidget(self.page1)
        self.stack.addWidget(self.page2)
        self.stack.addWidget(self.page3)

        scroll = QScrollArea()
        scroll.setWidgetResizable(True)
        scroll.setWidget(self.stack)
        self.setCentralWidget(scroll)

        # 페이지 간 시그널 연결
        self.page1.sig_analyze.connect(lambda d: self.worker.send("upload_image", d))
        self.page2.sig_update.connect(lambda d: self.worker.send("update_grid", d))
        self.page2.sig_start.connect(self._on_start_assembly)
        self.page2.sig_back.connect(lambda: self.stack.setCurrentWidget(self.page1))
        self.page3.sig_pause.connect(lambda: self.worker.send("pause"))
        self.page3.sig_resume.connect(lambda: self.worker.send("resume"))
        self.page3.sig_home.connect(self._go_home)

    def _bind_worker(self):
        self.worker.sig_analysis_result.connect(self._on_analysis_result)
        self.worker.sig_block_plan.connect(
            lambda d: self.page2.show_block_plan(d.get("blocks", []))
        )
        self.worker.sig_assembly_started.connect(lambda _: self.page3.on_started())
        self.worker.sig_assembly_progress.connect(self.page3.on_progress)
        self.worker.sig_assembly_done.connect(self.page3.on_done)
        self.worker.sig_assembly_error.connect(self.page3.on_error)
        self.worker.sig_system_log.connect(
            lambda d: self.page3.add_log("WARN", d.get("message", ""))
        )

    def _on_analysis_result(self, data: dict):
        if not data.get("success"):
            self.page1.on_failed(data.get("error_message", "알 수 없는 오류"))
            return
        parsed = json.loads(data.get("grid_json", "[]"))
        grid_w = int(data.get("grid_cols", 16))
        grid_h = int(data.get("grid_rows", 8))
        if parsed and isinstance(parsed[0], list):
            grid = parsed
            grid_h = len(grid)
            grid_w = len(grid[0]) if grid else grid_w
        else:
            grid = []
            for r in range(grid_h):
                row = parsed[r * grid_w:(r + 1) * grid_w]
                while len(row) < grid_w:
                    row.append("")
                grid.append(row)
        self.page2.load_grid(grid, grid_w, grid_h)
        self.stack.setCurrentWidget(self.page2)

    def _on_start_assembly(self, data: dict):
        self.page3.reset()
        self.page3.load_blueprint(
            self.page2.canvas.grid,
            self.page2.canvas.grid_w,
            self.page2.canvas.grid_h,
            self.page2.canvas.block_map,
        )
        self.stack.setCurrentWidget(self.page3)
        self.page3.add_log("INFO", "조립 시작 요청")
        self.worker.send("start_assembly", data)

    def _go_home(self):
        self.page1.reset_status()
        self.stack.setCurrentWidget(self.page1)

    def closeEvent(self, e):
        self.worker.stop()
        self.worker.wait(2000)
        super().closeEvent(e)

# ── 진입점 ─────────────────────────────────────────────────────────────────────

def main():
    app = QApplication(sys.argv)
    app.setStyleSheet(STYLESHEET)
    win = MainWindow()
    win.resize(680, 860)
    win.show()
    sys.exit(app.exec())


if __name__ == "__main__":
    main()

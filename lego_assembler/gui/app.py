import threading
import time
import random
import base64 as _b64

import cv2
import numpy as np
from flask import Flask, render_template, request, jsonify
from flask_socketio import SocketIO, emit

app = Flask(__name__)
app.config["SECRET_KEY"] = "lego-assembler-secret"
socketio = SocketIO(app, cors_allowed_origins="*")

# ── 상태 머신 ──────────────────────────────────────────────
state = "IDLE"

pause_event = threading.Event()
pause_event.set()

sim_thread: threading.Thread | None = None
stop_flag     = False
start_time: float = 0.0

COLORS = ["red", "blue", "yellow", "green", "white", "black", "orange", "gray"]
grid: list[list[str]] = []
active_grid_size: int  = 16
analyzed_grid: list[list[str]] = []   # /api/analyze 결과 저장; on_start에서 소비

# ── 실물 블록 색상 팔레트 (RGB) ────────────────────────────
# "orange" 키는 기존 격자 포맷 호환을 위해 유지 (실물: 갈색 블록)
BLOCK_PALETTE: dict[str, tuple[int, int, int]] = {
    "red":    (220,  50,  50),
    "blue":   ( 50, 100, 220),
    "green":  ( 50, 180,  50),
    "white":  (240, 240, 240),
    "black":  ( 40,  40,  40),
    "yellow": (220, 200,  50),
    "orange": (150,  80,  40),   # 실물: 갈색
    "gray":   (130, 130, 130),
}


def _nearest_color(
    pixel: tuple[int, int, int],
    palette: dict[str, tuple[int, int, int]],
) -> str:
    best_name, best_sq = "", float("inf")
    for name, rgb in palette.items():
        sq = sum((int(pixel[i]) - int(rgb[i])) ** 2 for i in range(3))
        if sq < best_sq:
            best_sq, best_name = sq, name
    return best_name


def image_to_grid(image_b64, grid_size=16, palette=None):
    if "," in image_b64:
        image_b64 = image_b64.split(",", 1)[1]
    img_data = _b64.b64decode(image_b64)
    np_arr = np.frombuffer(img_data, np.uint8)
    img = cv2.imdecode(np_arr, cv2.IMREAD_COLOR)
    img_rgb = cv2.cvtColor(img, cv2.COLOR_BGR2RGB)
    small = cv2.resize(img_rgb, (grid_size, grid_size),
                       interpolation=cv2.INTER_AREA)
    grid = []
    for row in small:
        grid_row = []
        for pixel in row:
            color = _nearest_color(pixel.tolist(), palette)
            grid_row.append(color)
        grid.append(grid_row)
    return grid


def set_state(new_state: str, message: str = "") -> None:
    global state
    state = new_state
    socketio.emit("status", {"state": state, "message": message})
    _emit_log("INFO", f"상태 변경: {state} — {message}")


def _emit_log(level: str, text: str) -> None:
    socketio.emit("log", {
        "level": level,
        "text": text,
        "timestamp": time.strftime("%H:%M:%S"),
    })


# ── 시뮬레이션 루프 ────────────────────────────────────────
# TODO: [ROS2 연결 시] 이 함수 전체를 실제 robot_controller 노드 호출로 교체
def simulation_loop() -> None:
    global stop_flag

    size  = active_grid_size
    total = size * size
    done_count  = 0
    error_count = 0

    # grid_init: 비-스펙 이벤트 — 프론트엔드 초기 격자 렌더링 전용
    socketio.emit("grid_init", {"grid": grid, "size": size})

    for row in range(size):
        for col in range(size):
            if stop_flag:
                return

            pause_event.wait()
            if stop_flag:
                return

            # TODO: [ROS2 연결 시] time.sleep(1) → 실제 로봇 배치 완료 대기로 교체
            time.sleep(1)

            # TODO: [웹캠 연결 시] 랜덤 오류 → OpenCV 색상 감지 결과로 교체
            if random.random() < 0.05:
                error_count += 1
                expected = grid[row][col]
                detected = random.choice([c for c in COLORS if c != expected])

                set_state("ERROR", f"블록 배치 오류 ({row},{col})")
                socketio.emit("error", {
                    "row": row,
                    "col": col,
                    "expected": expected,
                    "detected": detected,
                    "message": "감지된 색상이 목표 색상과 다릅니다.",
                })
                _emit_log("ERROR", f"오류: ({row},{col}) 예상={expected} / 감지={detected}")

                pause_event.clear()
                pause_event.wait()
                if stop_flag:
                    return
                set_state("RUNNING", "오류 해결 후 재개")

            done_count += 1

            linear = row * size + col + 1
            if linear < total:
                nr, nc = divmod(linear, size)
                next_color = grid[nr][nc]
            else:
                nr = nc = next_color = None

            socketio.emit("progress", {
                "done": done_count,
                "total": total,
                "current_row": row,
                "current_col": col,
                "current_color": grid[row][col],
                "next_row": nr,
                "next_col": nc,
                "next_color": next_color,
            })
            _emit_log("INFO", f"배치 완료: ({row},{col}) {grid[row][col]} [{done_count}/{total}]")

    elapsed = int(time.time() - start_time)
    set_state("DONE", "조립 완료")
    socketio.emit("done", {
        "total_time":  elapsed,
        "error_count": error_count,
        "done_count":  done_count,
        "total":       total,
    })
    _emit_log("INFO", f"전체 조립 완료 — 오류 {error_count}회 / 소요 {elapsed}초")


# ── HTTP 라우트 ────────────────────────────────────────────
@app.route("/")
def index():
    return render_template("index.html")


@app.route("/api/analyze", methods=["POST"])
def api_analyze():
    """
    이미지 → 블록 색상 격자 변환 엔드포인트

    Request JSON:
        image        (str)       data URL base64 이미지
        grid_size    (int)       격자 한 변 크기 (8~32, 기본 16)
        owned_colors (list[str]) 보유 색상 이름 목록 (비면 전체 사용)

    Response JSON:
        ok    (bool)
        grid  (list[list[str]])  grid_size×grid_size 색상 격자
        error (str)              실패 시 오류 메시지
    """
    global analyzed_grid

    body = request.get_json(force=True, silent=True) or {}
    image_b64    = body.get("image", "")
    grid_size    = max(8, min(32, int(body.get("grid_size", 16))))
    owned_colors = body.get("owned_colors", [])

    if not image_b64:
        return jsonify({"ok": False, "error": "image 필드가 없습니다."}), 400

    try:
        palette      = {k: v for k, v in BLOCK_PALETTE.items() if not owned_colors or k in owned_colors} or BLOCK_PALETTE
        result       = image_to_grid(image_b64, grid_size, palette)
        analyzed_grid = result
        return jsonify({"ok": True, "grid": result})
    except Exception as exc:
        return jsonify({"ok": False, "error": str(exc)}), 500


# ── SocketIO 이벤트 핸들러 ─────────────────────────────────
@socketio.on("connect")
def on_connect():
    print("[SocketIO] 클라이언트 연결됨")
    emit("status", {"state": state, "message": "서버 연결됨"})


@socketio.on("disconnect")
def on_disconnect():
    print("[SocketIO] 클라이언트 연결 해제됨")


@socketio.on("start")
def on_start(data=None):
    global sim_thread, stop_flag, grid, active_grid_size, start_time, analyzed_grid

    print(f"[이벤트] start 수신: {data}")

    if state == "RUNNING":
        emit("status", {"state": state, "message": "이미 실행 중입니다."})
        return

    if data and isinstance(data, dict):
        size = int(data.get("grid_size", 16))
        active_grid_size = max(8, min(32, size))
    else:
        active_grid_size = 16

    stop_flag = True
    pause_event.set()
    if sim_thread and sim_thread.is_alive():
        sim_thread.join(timeout=2)

    # 이미지 분석 결과가 있으면 사용, 없으면 랜덤 격자로 폴백
    if analyzed_grid:
        grid          = analyzed_grid
        analyzed_grid = []
        _emit_log("INFO", f"이미지 분석 격자 사용 ({active_grid_size}×{active_grid_size})")
    else:
        # TODO: [이미지 분석 연결 시] 이 분기는 데모용 폴백으로만 유지
        grid = [[random.choice(COLORS) for _ in range(active_grid_size)]
                for _ in range(active_grid_size)]
        _emit_log("INFO", f"랜덤 더미 격자 사용 ({active_grid_size}×{active_grid_size})")

    stop_flag  = False
    pause_event.set()
    start_time = time.time()

    set_state("RUNNING", "조립 시작")

    sim_thread = threading.Thread(target=simulation_loop, daemon=True)
    sim_thread.start()


@socketio.on("pause")
def on_pause(data=None):
    print("[이벤트] pause 수신")
    if state != "RUNNING":
        return
    pause_event.clear()
    set_state("PAUSED", "일시정지됨")


@socketio.on("resume")
def on_resume(data=None):
    print("[이벤트] resume 수신")
    if state not in ("PAUSED", "ERROR"):
        return
    pause_event.set()
    set_state("RUNNING", "재개됨")


@socketio.on("recalibrate")
def on_recalibrate(data=None):
    print("[이벤트] recalibrate 수신")
    # TODO: [웹캠 연결 시] 실제 HSV 캘리브레이션 루틴으로 교체
    _emit_log("INFO", "색상 재보정 완료 (더미)")
    emit("status", {"state": state, "message": "색상 재보정 완료"})


@socketio.on("manual_fix")
def on_manual_fix(data):
    print(f"[이벤트] manual_fix 수신: {data}")
    row, col, color = data.get("row"), data.get("col"), data.get("color")
    # TODO: [ROS2 연결 시] 실제 로봇 보정 동작 명령으로 교체
    _emit_log("INFO", f"수동 보정 적용: ({row},{col}) → {color}")
    emit("status", {"state": state, "message": f"({row},{col}) 수동 보정 완료"})


# ── 엔트리포인트 ───────────────────────────────────────────
if __name__ == "__main__":
    socketio.run(app, host="0.0.0.0", port=5000, debug=True, allow_unsafe_werkzeug=True)

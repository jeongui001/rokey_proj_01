# 레고 블록 자동 조립 시스템 — 코드 보고서

작성일: 2026-06-21

---

## 목차

1. [프로젝트 구조](#1-프로젝트-구조)
2. [app.py](#2-apppy)
3. [templates/index.html](#3-templatesindexhtml)
4. [static/main.js](#4-staticmainjs)
5. [static/style.css](#5-staticstylecss)
6. [config/colors.yaml](#6-configcolorsyaml)
7. [config/robot.yaml](#7-configrobotyaml)
8. [requirements.txt](#8-requirementstxt)

---

## 1. 프로젝트 구조

```
gui_project/
└── lego_assembler/
    ├── gui/
    │   ├── app.py
    │   ├── templates/
    │   │   └── index.html
    │   └── static/
    │       ├── main.js
    │       └── style.css
    ├── config/
    │   ├── colors.yaml
    │   └── robot.yaml
    └── requirements.txt
```

---

## 2. app.py

**경로:** `lego_assembler/gui/app.py`

Flask + Socket.IO 기반 백엔드 서버.
이미지 분석(`/api/analyze`), 시뮬레이션 루프, 상태 머신, SocketIO 이벤트 핸들러를 포함한다.

```python
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
    """LAB 색공간 유클리드 거리로 가장 가까운 색상 이름 반환"""
    lab_pixel = cv2.cvtColor(np.uint8([[list(pixel)]]), cv2.COLOR_RGB2LAB)[0, 0].astype(float)

    best_name, best_sq = "", float("inf")
    for name, rgb in palette.items():
        lab_pal = cv2.cvtColor(np.uint8([[list(rgb)]]), cv2.COLOR_RGB2LAB)[0, 0].astype(float)
        sq = float(np.sum((lab_pixel - lab_pal) ** 2))
        if sq < best_sq:
            best_sq, best_name = sq, name
    return best_name


def image_to_grid(image_b64, grid_size=16, palette=None):
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
```

---

## 3. templates/index.html

**경로:** `lego_assembler/gui/templates/index.html`

4개 섹션(시작 설정 · 설계도 미리보기 · 실시간 진행 · 결과 요약)과 오류 카드 오버레이로 구성된 단일 페이지.

```html
<!DOCTYPE html>
<html lang="ko">
<head>
  <meta charset="UTF-8" />
  <meta name="viewport" content="width=1280" />
  <title>레고 블록 자동 조립 시스템</title>
  <link rel="stylesheet" href="/static/style.css" />
</head>
<body>

<!-- ══════════════════════════════════════════════════════════
     섹션 A: 시작 설정
══════════════════════════════════════════════════════════════ -->
<section id="section-a" class="section">

  <div class="section-header">
    <h2 class="section-title">시작 설정</h2>
  </div>

  <div class="sec-a-body">

    <!-- 좌: 이미지 업로드 -->
    <div class="upload-col">
      <div class="upload-zone" id="upload-zone">
        <input type="file" id="file-input" accept="image/*" hidden />
        <div class="upload-idle" id="upload-idle">
          <div class="upload-icon">⬆</div>
          <p class="upload-hint">이미지를 끌어다 놓거나<br>클릭하여 업로드</p>
          <p class="upload-sub">PNG · JPG · GIF</p>
        </div>
        <img class="upload-preview" id="upload-preview" alt="미리보기" />
      </div>
      <div class="upload-filename" id="upload-filename"></div>
    </div>

    <!-- 우: 설정 -->
    <div class="settings-col">

      <!-- 격자 크기 -->
      <div class="setting-block">
        <label class="setting-label">격자 크기</label>
        <div class="slider-row">
          <span class="slider-tick">8</span>
          <input type="range" id="grid-slider" class="grid-slider"
                 min="8" max="32" step="8" value="16" />
          <span class="slider-tick">32</span>
          <span class="grid-badge" id="grid-badge">16 × 16</span>
        </div>
        <div class="setting-sub" id="grid-sub">총 256칸</div>
      </div>

      <!-- 보유 블록 색상 -->
      <div class="setting-block">
        <label class="setting-label">보유 블록 색상</label>
        <div class="owned-palette" id="owned-palette"></div>
        <div class="setting-sub" id="owned-hint">8 / 8 색상 보유</div>
      </div>

      <!-- 웹캠 -->
      <div class="setting-block">
        <label class="setting-label">웹캠</label>
        <div class="cam-row">
          <div class="cam-badge" id="cam-badge">
            <span class="cam-dot" id="cam-dot"></span>
            <span id="cam-text">미연결</span>
          </div>
          <select class="cam-select" id="cam-select">
            <option value="0">카메라 0 (/dev/video0)</option>
            <option value="1">카메라 1 (/dev/video1)</option>
            <option value="2">카메라 2 (USB Webcam)</option>
          </select>
          <button class="btn btn-sm btn-cam" id="btn-cam-test">연결 테스트</button>
        </div>
      </div>

      <!-- 예상 필요 블록 -->
      <div class="setting-block total-block">
        <label class="setting-label">예상 필요 블록</label>
        <div class="total-num-row">
          <span class="total-num" id="total-num">256</span>
          <span class="total-unit">개</span>
        </div>
      </div>

    </div><!-- /settings-col -->
  </div><!-- /sec-a-body -->

  <div class="sec-a-footer">
    <button class="btn btn-analyze" id="btn-analyze" disabled>분석 시작 →</button>
    <span class="analyze-hint" id="analyze-hint">이미지를 먼저 업로드하세요</span>
  </div>

</section>

<!-- ══════════════════════════════════════════════════════════
     섹션 B: 설계도 미리보기 (분석 전 숨김)
══════════════════════════════════════════════════════════════ -->
<section id="section-b" class="section" style="display:none">

  <div class="section-header">
    <h2 class="section-title">설계도 미리보기</h2>
    <span class="section-sub-badge" id="b-grid-info">16 × 16 격자</span>
  </div>

  <div class="sec-b-body">

    <!-- 원본 이미지 -->
    <div class="b-col">
      <div class="b-col-label">원본 이미지</div>
      <div class="b-image-box" id="b-image-box">
        <img id="b-original-img" alt="원본" />
        <div class="b-no-image" id="b-no-image">이미지 없음</div>
      </div>
    </div>

    <!-- 변환된 블록 격자 -->
    <div class="b-col">
      <div class="b-col-label">변환된 블록 격자</div>
      <div class="b-canvas-box">
        <canvas id="b-canvas" width="320" height="320"></canvas>
      </div>
    </div>

    <!-- 색상별 필요 블록 테이블 -->
    <div class="b-table-col">
      <div class="b-col-label">색상별 필요 블록</div>
      <div class="color-table" id="color-table"></div>
      <div class="color-total" id="color-total"></div>
    </div>

  </div><!-- /sec-b-body -->

  <div class="sec-b-footer">
    <button class="btn btn-assemble" id="btn-assemble">조립 시작 →</button>
  </div>

</section>

<!-- ══════════════════════════════════════════════════════════
     섹션 C: 실시간 진행
══════════════════════════════════════════════════════════════ -->
<section id="section-c" class="section">

  <div class="section-header">
    <h2 class="section-title">실시간 진행</h2>
    <div class="status-badge" id="status-badge">
      <span class="status-dot" id="status-dot"></span>
      <span class="status-text" id="status-text">IDLE — 대기 중</span>
    </div>
  </div>

  <!-- 진행률 바 -->
  <div class="progress-row">
    <div class="progress-track">
      <div class="progress-fill" id="progress-fill"></div>
    </div>
    <div class="progress-meta">
      <span id="progress-label">0 / 256</span>
      <span class="progress-sep">·</span>
      <span id="progress-pct">0%</span>
    </div>
  </div>

  <!-- 컨트롤 -->
  <div class="controls-row">
    <button class="btn btn-demo" id="btn-demo">▶ 데모 시작</button>
    <div class="ctrl-divider"></div>
    <button class="btn btn-pause" id="btn-pause-resume" disabled>⏸ 일시정지</button>
    <button class="btn btn-recal" id="btn-recalibrate" disabled>◎ 재캘리브레이션</button>
    <button class="btn btn-fix"   id="btn-manual-fix"  disabled>✎ 수동 보정</button>
  </div>

  <!-- 3열 메인 -->
  <div class="tri-grid">

    <div class="panel" id="panel-webcam">
      <div class="panel-header">
        <span class="panel-title">웹캠 현재 상태</span>
        <span class="badge-sim">SIM</span>
      </div>
      <div class="canvas-wrap">
        <canvas id="webcam-canvas" width="320" height="320"></canvas>
      </div>
      <div class="webcam-footer" id="webcam-footer">조립 대기 중…</div>
    </div>

    <div class="panel" id="panel-compare">
      <div class="panel-header">
        <span class="panel-title">설계도 비교</span>
      </div>
      <div class="compare-wrap">
        <div class="grid-block">
          <div class="grid-label">목표</div>
          <canvas id="target-canvas" width="192" height="192"></canvas>
        </div>
        <div class="compare-divider"></div>
        <div class="grid-block">
          <div class="grid-label">현재</div>
          <canvas id="current-canvas" width="192" height="192"></canvas>
        </div>
      </div>
      <div class="cur-pos-bar" id="cur-pos-bar">위치: —</div>
    </div>

    <div class="panel" id="panel-log">
      <div class="panel-header">
        <span class="panel-title">시스템 로그</span>
        <button class="btn-log-clear" id="btn-log-clear">지우기</button>
      </div>
      <div class="log-stream" id="log-stream"></div>
    </div>

  </div>

  <div class="next-bar" id="next-bar">
    <span class="next-label">다음 블록</span>
    <span class="next-pos"  id="next-pos">—</span>
    <span class="next-sep">·</span>
    <div  class="next-swatch" id="next-swatch"></div>
    <span class="next-name"  id="next-name">—</span>
  </div>

</section>

<!-- ══════════════════════════════════════════════════════════
     섹션 D: 결과 요약 (done 이벤트 수신 후 자동 표시)
══════════════════════════════════════════════════════════════ -->
<section id="section-d" class="section sec-d" style="display:none">

  <div class="section-header">
    <h2 class="section-title">결과 요약</h2>
    <span class="done-badge">✓ 조립 완료</span>
  </div>

  <!-- 통계 카드 3개 -->
  <div class="result-cards">

    <div class="result-card card-green">
      <div class="card-icon">✓</div>
      <div class="card-val" id="res-rate">—</div>
      <div class="card-label">완료율</div>
      <div class="card-sub" id="res-blocks">— / — 블록</div>
    </div>

    <div class="result-card card-red">
      <div class="card-icon">⚠</div>
      <div class="card-val" id="res-errors">—</div>
      <div class="card-label">오류 횟수</div>
      <div class="card-sub">수동 보정 포함</div>
    </div>

    <div class="result-card card-blue">
      <div class="card-icon">⏱</div>
      <div class="card-val" id="res-time">—</div>
      <div class="card-label">소요 시간</div>
      <div class="card-sub" id="res-time-sub">—</div>
    </div>

  </div><!-- /result-cards -->

  <!-- 로그 다운로드 -->
  <div class="result-actions">
    <button class="btn btn-download" id="btn-download-log">⬇ 전체 로그 다운로드</button>
  </div>

</section>

<!-- ══════════════════════════════════════════════════════════
     오류 카드 오버레이
══════════════════════════════════════════════════════════════ -->
<div class="err-overlay" id="err-overlay">
  <div class="err-card">
    <div class="err-card-head">
      <span class="err-icon">⚠</span>
      <h3>블록 배치 오류 감지</h3>
    </div>
    <div class="err-card-body">
      <p class="err-location" id="err-location"></p>
      <div class="err-colors">
        <div class="err-color-item">
          <div class="color-swatch-lg" id="err-exp-sw"></div>
          <span class="color-tag">목표</span>
          <span class="color-nm" id="err-exp-nm"></span>
        </div>
        <div class="err-arrow">→</div>
        <div class="err-color-item">
          <div class="color-swatch-lg" id="err-det-sw"></div>
          <span class="color-tag">감지됨</span>
          <span class="color-nm" id="err-det-nm"></span>
        </div>
      </div>
      <p class="err-msg" id="err-msg"></p>
      <div class="err-fix">
        <span class="err-fix-label">색상 직접 선택</span>
        <div class="err-palette" id="err-palette"></div>
      </div>
    </div>
    <div class="err-card-foot">
      <button class="btn btn-dismiss" id="btn-dismiss">무시하고 계속</button>
    </div>
  </div>
</div>

<script src="https://cdn.socket.io/4.7.5/socket.io.min.js"></script>
<script src="/static/main.js"></script>
</body>
</html>
```

---

## 4. static/main.js

**경로:** `lego_assembler/gui/static/main.js`

Socket.IO 클라이언트. 섹션 A~D UI 제어, 캔버스 렌더링, 이벤트 핸들러 전체 포함.

```javascript
// =============================================================
//  레고 블록 자동 조립 시스템 — GUI 클라이언트
//
//  SocketIO 인터페이스 (백엔드 연결 시 이 이름 그대로 사용)
//  프론트→서버: start | pause | resume | recalibrate | manual_fix
//  서버→프론트: status | progress | frame | log | error | done
// =============================================================

// ── 상수 ─────────────────────────────────────────────────────
const ALL_COLORS = ["red","blue","yellow","green","white","black","orange","gray"];

const COLOR_HEX = {
  red:    "#e3000b",
  blue:   "#006cb7",
  yellow: "#ffcd00",
  green:  "#00a650",
  white:  "#f0f0f0",
  black:  "#2a2a2a",
  orange: "#f47920",
  gray:   "#9e9e9e",
};

const COLOR_KR = {
  red:    "빨간색",
  blue:   "파란색",
  yellow: "노란색",
  green:  "초록색",
  white:  "흰색",
  black:  "검은색",
  orange: "주황색",
  gray:   "회색",
};

// ── 섹션 C 상태 ──────────────────────────────────────────────
let appState        = "IDLE";
let targetGrid      = null;
let currentGrid     = null;
let errorCells      = {};
let currentPos      = null;
let lastError       = null;
let totalBlocks     = 256;
let lastDoneCount   = 0;    // done 이벤트 완료율 계산용
let currentGridSize = 16;   // grid_init 수신 시 갱신

// ── 캔버스 ───────────────────────────────────────────────────
const webcamCanvas  = document.getElementById("webcam-canvas");
const targetCanvas  = document.getElementById("target-canvas");
const currentCanvas = document.getElementById("current-canvas");
const wCtx = webcamCanvas.getContext("2d");
const tCtx = targetCanvas.getContext("2d");
const cCtx = currentCanvas.getContext("2d");

const wSize = () => Math.floor(320 / currentGridSize);
const cSize = () => Math.floor(192 / currentGridSize);

// ── 섹션 C 캔버스 그리기 ─────────────────────────────────────
function drawEmpty(ctx, cell, canvasW, canvasH, msg) {
  ctx.fillStyle = "#0d1117";
  ctx.fillRect(0, 0, canvasW, canvasH);
  for (let r = 0; r < currentGridSize; r++) {
    for (let c = 0; c < currentGridSize; c++) {
      ctx.fillStyle = "#1c2128";
      ctx.fillRect(c*cell+1, r*cell+1, cell-2, cell-2);
    }
  }
  if (msg) {
    ctx.fillStyle = "rgba(139,148,158,0.7)";
    ctx.font = "13px sans-serif";
    ctx.textAlign = "center";
    ctx.fillText(msg, canvasW/2, canvasH/2);
    ctx.textAlign = "left";
  }
}

function drawTargetGrid() {
  const cs = cSize();
  tCtx.fillStyle = "#0d1117";
  tCtx.fillRect(0, 0, 192, 192);
  if (!targetGrid) return;
  for (let r = 0; r < currentGridSize; r++) {
    for (let c = 0; c < currentGridSize; c++) {
      tCtx.fillStyle = COLOR_HEX[targetGrid[r][c]] || "#333";
      tCtx.fillRect(c*cs+1, r*cs+1, cs-2, cs-2);
    }
  }
}

function drawCurrentGrid() {
  const cs = cSize();
  cCtx.fillStyle = "#0d1117";
  cCtx.fillRect(0, 0, 192, 192);
  for (let r = 0; r < currentGridSize; r++) {
    for (let c = 0; c < currentGridSize; c++) {
      const color = currentGrid && currentGrid[r][c];
      const key   = `${r},${c}`;
      cCtx.fillStyle = color ? COLOR_HEX[color] : "#1c2128";
      cCtx.fillRect(c*cs+1, r*cs+1, cs-2, cs-2);
      if (errorCells[key]) {
        cCtx.fillStyle = "rgba(218,54,51,0.45)";
        cCtx.fillRect(c*cs, r*cs, cs, cs);
        cCtx.strokeStyle = "#da3633";
        cCtx.lineWidth = 1.5;
        cCtx.strokeRect(c*cs+0.75, r*cs+0.75, cs-1.5, cs-1.5);
        cCtx.lineWidth = 1;
      }
    }
  }
}

// TODO: [웹캠 연결 시] 이 함수를 실제 video 스트림 + 격자 오버레이 방식으로 교체
function drawWebcam() {
  const cs = wSize();
  wCtx.fillStyle = "#090c10";
  wCtx.fillRect(0, 0, 320, 320);
  for (let r = 0; r < currentGridSize; r++) {
    for (let c = 0; c < currentGridSize; c++) {
      const color = currentGrid && currentGrid[r][c];
      const key   = `${r},${c}`;
      wCtx.fillStyle = color ? COLOR_HEX[color] : "#111820";
      wCtx.fillRect(c*cs+2, r*cs+2, cs-4, cs-4);
      if (errorCells[key]) {
        wCtx.fillStyle = "rgba(218,54,51,0.38)";
        wCtx.fillRect(c*cs, r*cs, cs, cs);
      }
      wCtx.strokeStyle = "rgba(0,200,255,0.18)";
      wCtx.lineWidth = 0.5;
      wCtx.strokeRect(c*cs, r*cs, cs, cs);
    }
  }
  if (currentPos && appState === "RUNNING") {
    const {row: r, col: c} = currentPos;
    wCtx.strokeStyle = "rgba(0,200,255,0.3)";
    wCtx.lineWidth = 1;
    wCtx.beginPath();
    wCtx.moveTo(c*cs+cs/2, 0);   wCtx.lineTo(c*cs+cs/2, 320);
    wCtx.moveTo(0, r*cs+cs/2);   wCtx.lineTo(320, r*cs+cs/2);
    wCtx.stroke();
    wCtx.strokeStyle = "#00c8ff";
    wCtx.lineWidth = 2;
    wCtx.strokeRect(c*cs, r*cs, cs, cs);
    wCtx.lineWidth = 1;
  }
  wCtx.fillStyle = "rgba(0,200,255,0.06)";
  wCtx.font = "bold 20px monospace";
  wCtx.textAlign = "center";
  wCtx.fillText("SIMULATION", 160, 165);
  wCtx.textAlign = "left";
}

function redrawAll() {
  drawWebcam();
  drawTargetGrid();
  drawCurrentGrid();
}

function resetCanvases(msg) {
  drawEmpty(wCtx, wSize(), 320, 320, msg || "");
  drawEmpty(tCtx, cSize(), 192, 192, "");
  drawEmpty(cCtx, cSize(), 192, 192, "");
}

resetCanvases("조립 대기 중…");

// ── 섹션 C UI 업데이트 ───────────────────────────────────────
function updateProgress(done, total) {
  const pct = total > 0 ? Math.round((done / total) * 100) : 0;
  document.getElementById("progress-fill").style.width  = `${pct}%`;
  document.getElementById("progress-label").textContent = `${done} / ${total}`;
  document.getElementById("progress-pct").textContent   = `${pct}%`;
}

const STATE_CFG = {
  IDLE:    { dotClass: "",       dot: "#6e7681", text: "IDLE — 대기 중"    },
  RUNNING: { dotClass: "pulse",  dot: "#1f6feb", text: "RUNNING — 진행 중" },
  PAUSED:  { dotClass: "",       dot: "#d29922", text: "PAUSED — 일시정지" },
  ERROR:   { dotClass: "flash",  dot: "#da3633", text: "ERROR — 오류 감지" },
  DONE:    { dotClass: "",       dot: "#238636", text: "DONE — 완료"       },
};

function updateStatusBadge(newState) {
  appState = newState;
  const cfg   = STATE_CFG[newState] || STATE_CFG.IDLE;
  const dot   = document.getElementById("status-dot");
  const text  = document.getElementById("status-text");
  const badge = document.getElementById("status-badge");

  dot.className        = "status-dot " + cfg.dotClass;
  dot.style.background = cfg.dot;
  text.textContent     = cfg.text;
  badge.className      = `status-badge state-${newState}`;

  const btnPR  = document.getElementById("btn-pause-resume");
  const btnRec = document.getElementById("btn-recalibrate");
  const btnFix = document.getElementById("btn-manual-fix");

  if (newState === "IDLE" || newState === "DONE") {
    btnPR.disabled  = true;
    btnRec.disabled = true;
    btnFix.disabled = true;
    btnFix.classList.remove("active");
    btnPR.textContent = "⏸ 일시정지";
  } else {
    btnPR.disabled  = false;
    btnRec.disabled = false;
    btnPR.textContent = (newState === "RUNNING") ? "⏸ 일시정지" : "▶ 재생";
    if (newState === "ERROR") {
      btnFix.disabled = false;
      btnFix.classList.add("active");
    } else {
      btnFix.disabled = true;
      btnFix.classList.remove("active");
    }
  }
}

function updateNextBlock(nr, nc, nColor) {
  if (nr === null || nr === undefined) {
    document.getElementById("next-pos").textContent      = "—";
    document.getElementById("next-swatch").style.display = "none";
    document.getElementById("next-name").textContent     = "—";
    return;
  }
  document.getElementById("next-pos").textContent   = `(${nr}행, ${nc}열)`;
  const sw = document.getElementById("next-swatch");
  sw.style.background = COLOR_HEX[nColor] || "transparent";
  sw.style.display    = "inline-block";
  document.getElementById("next-name").textContent = COLOR_KR[nColor] || nColor;
}

// ── 로그 스트림 ──────────────────────────────────────────────
function addLog(level, text, ts) {
  const time   = ts || new Date().toLocaleTimeString("ko-KR", {hour12: false});
  const stream = document.getElementById("log-stream");
  const el     = document.createElement("div");
  el.className = `log-entry log-${level.toLowerCase()}`;
  el.innerHTML =
    `<span class="log-ts">${time}</span>` +
    `<span class="log-level">[${level}]</span>` +
    `<span class="log-text">${text}</span>`;
  stream.appendChild(el);
  stream.scrollTop = stream.scrollHeight;
  while (stream.children.length > 300) stream.removeChild(stream.firstChild);
}

// ── 오류 카드 ────────────────────────────────────────────────
function showErrorCard(data) {
  lastError = data;
  document.getElementById("err-location").textContent        = `위치: ${data.row}행 ${data.col}열`;
  document.getElementById("err-exp-sw").style.background     = COLOR_HEX[data.expected] || "#555";
  document.getElementById("err-exp-nm").textContent          = COLOR_KR[data.expected]  || data.expected;
  document.getElementById("err-det-sw").style.background     = COLOR_HEX[data.detected] || "#555";
  document.getElementById("err-det-nm").textContent          = COLOR_KR[data.detected]  || data.detected;
  document.getElementById("err-msg").textContent             = data.message;

  const palette = document.getElementById("err-palette");
  palette.innerHTML = "";
  ALL_COLORS.forEach(color => {
    const sw = document.createElement("div");
    sw.className        = "palette-swatch";
    sw.style.background = COLOR_HEX[color];
    sw.title            = COLOR_KR[color];
    sw.addEventListener("click", () => applyManualFix(data.row, data.col, color));
    palette.appendChild(sw);
  });

  document.getElementById("err-overlay").classList.add("visible");
}

function hideErrorCard() {
  document.getElementById("err-overlay").classList.remove("visible");
}

function applyManualFix(row, col, color) {
  socket.emit("manual_fix", {row, col, color});
  if (currentGrid) currentGrid[row][col] = color;
  delete errorCells[`${row},${col}`];
  redrawAll();
  hideErrorCard();
  socket.emit("resume");
  addLog("INFO", `수동 보정: (${row},${col}) → ${COLOR_KR[color]}`);
}

// ── 섹션 D: 결과 요약 표시 ───────────────────────────────────
function showSectionD(data) {
  const done  = data.done_count !== undefined ? data.done_count : lastDoneCount;
  const total = data.total      !== undefined ? data.total      : totalBlocks;
  const rate  = total > 0 ? Math.round((done / total) * 100) : 100;

  const secs = data.total_time;
  const mins = Math.floor(secs / 60);
  const rem  = secs % 60;
  const timeStr  = mins > 0 ? `${mins}분 ${rem}초` : `${secs}초`;
  const perBlock = total > 0 && secs > 0 ? (secs / total).toFixed(1) : "1.0";

  document.getElementById("res-rate").textContent    = `${rate}%`;
  document.getElementById("res-blocks").textContent  = `${done} / ${total} 블록`;
  document.getElementById("res-errors").textContent  = String(data.error_count);
  document.getElementById("res-time").textContent    = timeStr;
  document.getElementById("res-time-sub").textContent = `블록당 약 ${perBlock}초`;

  const secD = document.getElementById("section-d");
  secD.style.display = "block";
  setTimeout(() => secD.scrollIntoView({behavior: "smooth", block: "start"}), 350);
}

// ── 시작 공통 함수 ────────────────────────────────────────────
function triggerStart(gridSize) {
  if (appState === "RUNNING") return;

  currentGridSize = gridSize || 16;
  targetGrid      = null;
  currentGrid     = null;
  errorCells      = {};
  currentPos      = null;
  lastDoneCount   = 0;
  totalBlocks     = currentGridSize * currentGridSize;
  lastError       = null;

  updateProgress(0, totalBlocks);
  updateNextBlock(null);

  document.getElementById("webcam-footer").textContent = "초기화 중…";
  document.getElementById("cur-pos-bar").textContent   = "위치: —";
  document.getElementById("log-stream").innerHTML      = "";
  document.getElementById("section-d").style.display   = "none";

  resetCanvases("초기화 중…");
  socket.emit("start", {grid_size: currentGridSize});
}

// ═══════════════════════════════════════════════════════════
//  Socket.IO 이벤트 핸들러
//  (이 블록의 이벤트 이름은 백엔드 스펙과 정확히 일치해야 함)
// ═══════════════════════════════════════════════════════════
const socket = io();

socket.on("connect", () => addLog("INFO", "서버 연결됨"));

socket.on("disconnect", () => {
  addLog("WARN", "서버 연결 해제됨");
  updateStatusBadge("IDLE");
});

// 비-스펙 이벤트: 프론트엔드 초기 격자 렌더링 전용
socket.on("grid_init", (data) => {
  currentGridSize = data.size;
  targetGrid      = data.grid;
  totalBlocks     = data.size * data.size;
  currentGrid     = Array.from({length: data.size}, () => Array(data.size).fill(null));
  errorCells      = {};
  currentPos      = null;
  updateProgress(0, totalBlocks);
  redrawAll();
  addLog("INFO", `${data.size}×${data.size} 격자 수신 완료`);
});

// ── 스펙 이벤트: 서버→프론트 ─────────────────────────────────

socket.on("status", (data) => {
  updateStatusBadge(data.state);
  if (data.state === "DONE") {
    currentPos = null;
    redrawAll();
    updateNextBlock(null);
    document.getElementById("webcam-footer").textContent = "조립 완료 ✓";
    document.getElementById("cur-pos-bar").textContent   = "조립 완료";
  }
});

socket.on("progress", (data) => {
  const {done, total, current_row, current_col, current_color,
         next_row, next_col, next_color} = data;

  if (currentGrid && current_color) {
    currentGrid[current_row][current_col] = current_color;
  }
  currentPos    = {row: current_row, col: current_col};
  lastDoneCount = done;

  updateProgress(done, total);
  updateNextBlock(next_row, next_col, next_color);

  document.getElementById("webcam-footer").textContent =
    `작업 중: (${current_row}행, ${current_col}열) — ${COLOR_KR[current_color] || current_color}`;
  document.getElementById("cur-pos-bar").textContent =
    `완료: (${current_row}행, ${current_col}열)  |  ${done} / ${total} 블록`;

  redrawAll();
});

// TODO: [웹캠 연결 시] base64 이미지를 webcam-canvas에 직접 렌더링하도록 교체
socket.on("frame", (/* data */) => {
  // const img = new Image();
  // img.onload = () => wCtx.drawImage(img, 0, 0, 320, 320);
  // img.src = "data:image/jpeg;base64," + data.frame;
});

socket.on("log", (data) => addLog(data.level, data.text, data.timestamp));

socket.on("error", (data) => {
  errorCells[`${data.row},${data.col}`] = data;
  redrawAll();
  showErrorCard(data);
  document.getElementById("section-c").scrollIntoView({behavior: "smooth", block: "start"});
});

socket.on("done", (data) => {
  updateNextBlock(null);
  showSectionD(data);
  addLog("INFO", `조립 완료 — 오류 ${data.error_count}회 / 소요 ${data.total_time}초`);
});

// ── 스펙 이벤트: 프론트→서버 ─────────────────────────────────

// "start" — triggerStart() 내부에서 emit
// "pause" / "resume" / "recalibrate" / "manual_fix" — 아래 버튼 핸들러에서 emit

// ── 섹션 C 버튼 ──────────────────────────────────────────────
document.getElementById("btn-demo").addEventListener("click", () => {
  triggerStart(secA.gridSize);
});

document.getElementById("btn-pause-resume").addEventListener("click", () => {
  if (appState === "RUNNING")
    socket.emit("pause");
  else if (appState === "PAUSED" || appState === "ERROR")
    socket.emit("resume");
});

document.getElementById("btn-recalibrate").addEventListener("click", () => {
  socket.emit("recalibrate");
  addLog("INFO", "색상 재보정 요청 전송");
});

document.getElementById("btn-manual-fix").addEventListener("click", () => {
  if (lastError) showErrorCard(lastError);
});

document.getElementById("btn-dismiss").addEventListener("click", () => {
  const err = lastError;
  hideErrorCard();
  if (err) delete errorCells[`${err.row},${err.col}`];
  redrawAll();
  socket.emit("resume");
  addLog("WARN", "오류 무시하고 재개");
});

document.getElementById("btn-log-clear").addEventListener("click", () => {
  document.getElementById("log-stream").innerHTML = "";
});

// ── 섹션 D 버튼: 로그 다운로드 ──────────────────────────────
document.getElementById("btn-download-log").addEventListener("click", () => {
  const entries = document.querySelectorAll("#log-stream .log-entry");
  let text = "레고 블록 자동 조립 시스템 — 조립 로그\n";
  text += "─".repeat(52) + "\n";
  text += `생성 시각: ${new Date().toLocaleString("ko-KR")}\n`;
  text += "─".repeat(52) + "\n\n";
  entries.forEach(el => {
    const ts    = el.querySelector(".log-ts")?.textContent    || "";
    const level = el.querySelector(".log-level")?.textContent || "";
    const msg   = el.querySelector(".log-text")?.textContent  || "";
    text += `${ts}  ${level.padEnd(8)} ${msg}\n`;
  });

  const blob = new Blob([text], {type: "text/plain;charset=utf-8"});
  const a    = document.createElement("a");
  a.href     = URL.createObjectURL(blob);
  a.download = `lego_log_${new Date().toISOString().slice(0,16).replace(/[T:]/g,"-")}.txt`;
  document.body.appendChild(a);
  a.click();
  document.body.removeChild(a);
  URL.revokeObjectURL(a.href);
  addLog("INFO", "로그 파일 다운로드 완료");
});

// ═══════════════════════════════════════════════════════════
//  섹션 A: 시작 설정
// ═══════════════════════════════════════════════════════════
const secA = {
  imageDataURL: null,
  gridSize:     16,
  ownedColors:  new Set(ALL_COLORS),
};

// 보유 색상 팔레트 초기화
(function initOwnedPalette() {
  const container = document.getElementById("owned-palette");
  ALL_COLORS.forEach(color => {
    const sw = document.createElement("div");
    sw.className        = "owned-swatch owned";
    sw.style.background = COLOR_HEX[color];
    sw.title            = COLOR_KR[color];
    sw.addEventListener("click", () => {
      if (secA.ownedColors.has(color)) {
        secA.ownedColors.delete(color);
        sw.classList.replace("owned", "not-owned");
      } else {
        secA.ownedColors.add(color);
        sw.classList.replace("not-owned", "owned");
      }
      document.getElementById("owned-hint").textContent =
        `${secA.ownedColors.size} / ${ALL_COLORS.length} 색상 보유`;
    });
    container.appendChild(sw);
  });
})();

// 격자 크기 슬라이더
document.getElementById("grid-slider").addEventListener("input", (e) => {
  secA.gridSize = parseInt(e.target.value);
  const total = secA.gridSize * secA.gridSize;
  document.getElementById("grid-badge").textContent = `${secA.gridSize} × ${secA.gridSize}`;
  document.getElementById("grid-sub").textContent   = `총 ${total}칸`;
  document.getElementById("total-num").textContent  = String(total);
});

// 이미지 업로드
(function setupUpload() {
  const zone  = document.getElementById("upload-zone");
  const input = document.getElementById("file-input");

  zone.addEventListener("click",     (e) => { if (e.target !== input) input.click(); });
  zone.addEventListener("dragover",  (e) => { e.preventDefault(); zone.classList.add("dragover"); });
  zone.addEventListener("dragleave", ()  => zone.classList.remove("dragover"));
  zone.addEventListener("drop", (e) => {
    e.preventDefault();
    zone.classList.remove("dragover");
    const file = e.dataTransfer.files[0];
    if (file && file.type.startsWith("image/")) loadImage(file);
  });
  input.addEventListener("change", (e) => {
    if (e.target.files[0]) loadImage(e.target.files[0]);
  });

  function loadImage(file) {
    const reader = new FileReader();
    reader.onload = (ev) => {
      secA.imageDataURL = ev.target.result;
      const preview = document.getElementById("upload-preview");
      preview.src = ev.target.result;
      preview.classList.add("visible");
      document.getElementById("upload-idle").style.display = "none";
      document.getElementById("upload-filename").textContent = `✓  ${file.name}`;
      document.getElementById("btn-analyze").disabled        = false;
      document.getElementById("analyze-hint").textContent    = `${file.name} — 분석 준비됨`;
    };
    reader.readAsDataURL(file);
  }
})();

// 웹캠 연결 테스트 (더미)
// TODO: [웹캠 연결 시] navigator.mediaDevices.enumerateDevices() 로 실제 장치 목록 교체
document.getElementById("btn-cam-test").addEventListener("click", () => {
  const dot    = document.getElementById("cam-dot");
  const text   = document.getElementById("cam-text");
  const select = document.getElementById("cam-select");
  dot.style.background = "#d29922";
  text.textContent     = "연결 중…";
  setTimeout(() => {
    if (Math.random() < 0.8) {
      dot.style.background = "#238636";
      text.textContent     = `카메라 ${select.value} — 연결됨`;
    } else {
      dot.style.background = "#da3633";
      text.textContent     = "연결 실패";
    }
  }, 900);
});

// [분석 시작] — 이미지가 있으면 서버 OpenCV 분석, 없으면 랜덤 폴백
document.getElementById("btn-analyze").addEventListener("click", async () => {
  const btnAnalyze = document.getElementById("btn-analyze");
  const gs         = secA.gridSize;
  const useColors  = secA.ownedColors.size > 0 ? [...secA.ownedColors] : ALL_COLORS;

  // 버튼 로딩 상태
  btnAnalyze.disabled    = true;
  btnAnalyze.textContent = "분석 중…";

  let grid;

  if (secA.imageDataURL) {
    try {
      const res  = await fetch("/api/analyze", {
        method:  "POST",
        headers: {"Content-Type": "application/json"},
        body:    JSON.stringify({
          image:        secA.imageDataURL,
          grid_size:    gs,
          owned_colors: useColors,
        }),
      });
      const json = await res.json();
      if (!json.ok) throw new Error(json.error || "서버 분석 오류");
      grid = json.grid;
    } catch (err) {
      console.warn("[analyze] 서버 분석 실패, 랜덤 격자로 대체:", err);
      grid = _randomGrid(gs, useColors);
    }
  } else {
    grid = _randomGrid(gs, useColors);
  }

  // 버튼 복원
  btnAnalyze.disabled    = false;
  btnAnalyze.textContent = "분석 시작 →";

  window._sectionBGrid = grid;
  document.getElementById("b-grid-info").textContent = `${gs} × ${gs} 격자`;

  const img   = document.getElementById("b-original-img");
  const noImg = document.getElementById("b-no-image");
  if (secA.imageDataURL) {
    img.src             = secA.imageDataURL;
    img.style.display   = "block";
    noImg.style.display = "none";
  } else {
    img.style.display   = "none";
    noImg.style.display = "block";
  }

  drawSectionBGrid(grid);
  buildColorTable(grid);

  const secB = document.getElementById("section-b");
  secB.style.display = "block";
  setTimeout(() => secB.scrollIntoView({behavior: "smooth", block: "start"}), 50);
});

// 랜덤 격자 생성 (이미지 없거나 분석 실패 시 폴백)
function _randomGrid(gs, useColors) {
  return Array.from({length: gs}, () =>
    Array.from({length: gs}, () => useColors[Math.floor(Math.random() * useColors.length)])
  );
}

// ═══════════════════════════════════════════════════════════
//  섹션 B: 설계도 미리보기
// ═══════════════════════════════════════════════════════════

function drawSectionBGrid(grid) {
  const canvas = document.getElementById("b-canvas");
  const ctx    = canvas.getContext("2d");
  const sz     = grid.length;
  const cs     = Math.floor(320 / sz);
  const side   = cs * sz;

  canvas.width = canvas.height = side;
  ctx.fillStyle = "#0d1117";
  ctx.fillRect(0, 0, side, side);

  for (let r = 0; r < sz; r++) {
    for (let c = 0; c < sz; c++) {
      ctx.fillStyle = COLOR_HEX[grid[r][c]] || "#333";
      ctx.fillRect(c*cs+1, r*cs+1, cs-2, cs-2);
      ctx.strokeStyle = "rgba(255,255,255,0.05)";
      ctx.lineWidth   = 0.5;
      ctx.strokeRect(c*cs, r*cs, cs, cs);
    }
  }
}

function buildColorTable(grid) {
  const sz    = grid.length;
  const total = sz * sz;
  const counts = {};
  for (const row of grid) {
    for (const color of row) counts[color] = (counts[color] || 0) + 1;
  }
  const sorted = Object.entries(counts).sort((a, b) => b[1] - a[1]);

  const container = document.getElementById("color-table");
  container.innerHTML = "";
  sorted.forEach(([color, count]) => {
    const pct = Math.round((count / total) * 100);
    const row = document.createElement("div");
    row.className = "cc-row";
    row.innerHTML =
      `<div class="cc-dot"  style="background:${COLOR_HEX[color]}"></div>` +
      `<span class="cc-name">${COLOR_KR[color]}</span>` +
      `<span class="cc-num">${count}개</span>` +
      `<div class="cc-track"><div class="cc-fill" style="width:${pct}%;background:${COLOR_HEX[color]}"></div></div>` +
      `<span class="cc-pct">${pct}%</span>`;
    container.appendChild(row);
  });

  document.getElementById("color-total").textContent = `합계: ${total}개 블록`;
}

// [조립 시작] → smooth scroll → 섹션 C 시뮬레이션 자동 시작
document.getElementById("btn-assemble").addEventListener("click", () => {
  document.getElementById("section-c").scrollIntoView({behavior: "smooth", block: "start"});
  setTimeout(() => triggerStart(secA.gridSize), 600);
});
```

---

## 5. static/style.css

**경로:** `lego_assembler/gui/static/style.css`

GitHub 다크 테마 기반. CSS 변수, 섹션 A~D 전체 레이아웃, 상태 배지 애니메이션, 오류 카드 오버레이 스타일 포함.

```css
/* ── 전역 변수 & 리셋 ─────────────────────────────────── */
:root {
  --bg:        #0d1117;
  --bg2:       #161b22;
  --bg3:       #21262d;
  --border:    #30363d;
  --text:      #c9d1d9;
  --text2:     #8b949e;
  --blue:      #1f6feb;
  --blue-lt:   #58a6ff;
  --green:     #238636;
  --red:       #da3633;
  --yellow:    #d29922;
  --radius:    8px;
}

*, *::before, *::after { box-sizing: border-box; margin: 0; padding: 0; }

body {
  background: var(--bg);
  color: var(--text);
  font-family: 'Segoe UI', system-ui, sans-serif;
  font-size: 14px;
  min-width: 1280px;
}

/* ── 공통: 섹션 래퍼 ─────────────────────────────────── */
.section {
  padding: 28px 36px 32px;
  border-bottom: 1px solid var(--border);
}

.section-header {
  display: flex;
  align-items: center;
  justify-content: space-between;
  margin-bottom: 24px;
}

.section-title {
  font-size: 18px;
  font-weight: 600;
  color: var(--text);
  letter-spacing: -0.3px;
}

.section-sub-badge {
  padding: 4px 12px;
  background: var(--bg3);
  border: 1px solid var(--border);
  border-radius: 20px;
  font-size: 12px;
  color: var(--text2);
  font-family: monospace;
}

/* ── 공통: 버튼 ──────────────────────────────────────── */
.btn {
  padding: 7px 16px;
  border: 1px solid transparent;
  border-radius: var(--radius);
  font-size: 13px;
  font-weight: 500;
  cursor: pointer;
  transition: background 0.15s, border-color 0.15s, opacity 0.15s;
  white-space: nowrap;
  font-family: inherit;
}

.btn:disabled { opacity: 0.38; cursor: not-allowed; }

.btn-sm { padding: 5px 12px; font-size: 12px; }

/* ── 섹션 A: 공통 설정 블록 ──────────────────────────── */
.setting-block {
  display: flex;
  flex-direction: column;
  gap: 10px;
}

.setting-label {
  font-size: 11px;
  font-weight: 700;
  text-transform: uppercase;
  letter-spacing: 0.6px;
  color: var(--text2);
}

.setting-sub {
  font-size: 12px;
  color: var(--text2);
  margin-top: -4px;
}

/* ── 섹션 A: 레이아웃 ────────────────────────────────── */
.sec-a-body {
  display: grid;
  grid-template-columns: 400px 1fr;
  gap: 32px;
  margin-bottom: 24px;
}

/* ── 섹션 A: 업로드 영역 ─────────────────────────────── */
.upload-col {
  display: flex;
  flex-direction: column;
  gap: 10px;
}

.upload-zone {
  position: relative;
  width: 100%;
  height: 300px;
  border: 2px dashed var(--border);
  border-radius: 12px;
  cursor: pointer;
  overflow: hidden;
  display: flex;
  align-items: center;
  justify-content: center;
  transition: border-color 0.2s, background 0.2s;
}

.upload-zone:hover,
.upload-zone.dragover {
  border-color: var(--blue);
  background: rgba(31, 111, 235, 0.05);
}

.upload-idle {
  display: flex;
  flex-direction: column;
  align-items: center;
  gap: 10px;
  pointer-events: none;
  text-align: center;
}

.upload-icon {
  font-size: 36px;
  color: var(--text2);
  opacity: 0.6;
}

.upload-hint {
  font-size: 14px;
  color: var(--text2);
  line-height: 1.6;
}

.upload-sub {
  font-size: 11px;
  color: var(--text2);
  opacity: 0.6;
}

.upload-preview {
  position: absolute;
  inset: 0;
  width: 100%;
  height: 100%;
  object-fit: contain;
  display: none;
  background: var(--bg2);
}

.upload-preview.visible { display: block; }

.upload-filename {
  font-size: 12px;
  color: var(--text2);
  padding: 0 4px;
  white-space: nowrap;
  overflow: hidden;
  text-overflow: ellipsis;
}

/* ── 섹션 A: 설정 패널 ───────────────────────────────── */
.settings-col {
  display: flex;
  flex-direction: column;
  gap: 28px;
  padding-top: 4px;
}

/* 격자 슬라이더 */
.slider-row {
  display: flex;
  align-items: center;
  gap: 12px;
}

.slider-tick {
  font-size: 12px;
  color: var(--text2);
  font-family: monospace;
  min-width: 16px;
}

.grid-slider {
  flex: 1;
  -webkit-appearance: none;
  appearance: none;
  height: 4px;
  background: var(--bg3);
  border-radius: 2px;
  outline: none;
  cursor: pointer;
}

.grid-slider::-webkit-slider-thumb {
  -webkit-appearance: none;
  appearance: none;
  width: 18px;
  height: 18px;
  border-radius: 50%;
  background: var(--blue);
  cursor: pointer;
  border: 2px solid rgba(255,255,255,0.2);
  transition: transform 0.1s;
}

.grid-slider::-webkit-slider-thumb:hover { transform: scale(1.15); }

.grid-slider::-moz-range-thumb {
  width: 18px;
  height: 18px;
  border-radius: 50%;
  background: var(--blue);
  cursor: pointer;
  border: 2px solid rgba(255,255,255,0.2);
}

.grid-badge {
  font-family: monospace;
  font-size: 15px;
  font-weight: 700;
  color: var(--blue-lt);
  min-width: 72px;
  text-align: right;
}

/* 보유 색상 팔레트 */
.owned-palette {
  display: flex;
  gap: 8px;
  flex-wrap: wrap;
}

.owned-swatch {
  position: relative;
  width: 38px;
  height: 38px;
  border-radius: 7px;
  border: 2px solid rgba(255,255,255,0.18);
  cursor: pointer;
  transition: opacity 0.2s, border-color 0.2s, transform 0.12s;
}

.owned-swatch:hover { transform: scale(1.1); }

.owned-swatch.not-owned {
  opacity: 0.25;
  border-color: transparent;
}

.owned-swatch.not-owned::after {
  content: "✕";
  position: absolute;
  inset: 0;
  display: flex;
  align-items: center;
  justify-content: center;
  font-size: 14px;
  color: rgba(255,255,255,0.6);
}

/* 웹캠 */
.cam-row {
  display: flex;
  align-items: center;
  gap: 10px;
  flex-wrap: wrap;
}

.cam-badge {
  display: flex;
  align-items: center;
  gap: 7px;
  padding: 5px 12px;
  background: var(--bg3);
  border: 1px solid var(--border);
  border-radius: 6px;
  font-size: 12px;
  white-space: nowrap;
}

.cam-dot {
  width: 8px;
  height: 8px;
  border-radius: 50%;
  background: var(--text2);
  flex-shrink: 0;
  transition: background 0.3s;
}

.cam-select {
  background: var(--bg3);
  border: 1px solid var(--border);
  color: var(--text);
  padding: 5px 10px;
  border-radius: 6px;
  font-size: 13px;
  cursor: pointer;
  font-family: inherit;
}

.btn-cam {
  background: var(--bg3);
  border-color: var(--border);
  color: var(--text2);
}
.btn-cam:hover { border-color: var(--blue-lt); color: var(--blue-lt); }

/* 총 블록 수 */
.total-block { margin-top: auto; }

.total-num-row {
  display: flex;
  align-items: baseline;
  gap: 6px;
}

.total-num {
  font-size: 40px;
  font-weight: 700;
  font-family: monospace;
  color: var(--text);
  line-height: 1;
}

.total-unit {
  font-size: 16px;
  color: var(--text2);
}

/* 분석 시작 버튼 줄 */
.sec-a-footer {
  display: flex;
  align-items: center;
  gap: 16px;
  padding-top: 20px;
  border-top: 1px solid var(--border);
}

.btn-analyze {
  background: var(--blue);
  border-color: var(--blue);
  color: #fff;
  padding: 9px 28px;
  font-size: 14px;
}
.btn-analyze:hover:not(:disabled) { background: #388bfd; border-color: #388bfd; }
.btn-analyze:disabled {
  background: var(--bg3);
  border-color: var(--border);
  color: var(--text2);
}

.analyze-hint {
  font-size: 12px;
  color: var(--text2);
}

/* ── 섹션 B: 레이아웃 ────────────────────────────────── */
.sec-b-body {
  display: grid;
  grid-template-columns: 340px 340px 1fr;
  gap: 24px;
  margin-bottom: 24px;
}

.b-col {
  display: flex;
  flex-direction: column;
  gap: 12px;
}

.b-col-label {
  font-size: 11px;
  font-weight: 700;
  text-transform: uppercase;
  letter-spacing: 0.6px;
  color: var(--text2);
  padding-bottom: 8px;
  border-bottom: 1px solid var(--border);
}

.b-image-box {
  width: 320px;
  height: 320px;
  background: var(--bg2);
  border: 1px solid var(--border);
  border-radius: 8px;
  overflow: hidden;
  display: flex;
  align-items: center;
  justify-content: center;
}

.b-image-box img {
  max-width: 100%;
  max-height: 100%;
  object-fit: contain;
  display: none;
}

.b-no-image {
  font-size: 13px;
  color: var(--text2);
  opacity: 0.5;
}

.b-canvas-box {
  width: 320px;
  height: 320px;
  border: 1px solid var(--border);
  border-radius: 8px;
  overflow: hidden;
  background: var(--bg2);
}

#b-canvas { display: block; }

/* 색상 테이블 */
.b-table-col {
  display: flex;
  flex-direction: column;
  gap: 12px;
}

.color-table {
  display: flex;
  flex-direction: column;
  gap: 8px;
  max-height: 288px;
  overflow-y: auto;
  padding-right: 4px;
  scrollbar-width: thin;
  scrollbar-color: var(--bg3) transparent;
}

.cc-row {
  display: flex;
  align-items: center;
  gap: 10px;
}

.cc-dot {
  width: 14px;
  height: 14px;
  border-radius: 3px;
  border: 1px solid rgba(255,255,255,0.1);
  flex-shrink: 0;
}

.cc-name {
  width: 60px;
  font-size: 13px;
  color: var(--text);
  flex-shrink: 0;
}

.cc-num {
  width: 40px;
  font-size: 13px;
  font-family: monospace;
  color: var(--text);
  text-align: right;
  flex-shrink: 0;
}

.cc-track {
  flex: 1;
  height: 6px;
  background: var(--bg3);
  border-radius: 3px;
  overflow: hidden;
}

.cc-fill {
  height: 100%;
  border-radius: 3px;
  transition: width 0.5s ease;
}

.cc-pct {
  width: 36px;
  font-size: 11px;
  color: var(--text2);
  text-align: right;
  flex-shrink: 0;
}

.color-total {
  padding-top: 10px;
  border-top: 1px solid var(--border);
  font-size: 13px;
  color: var(--text2);
}

/* 조립 시작 버튼 줄 */
.sec-b-footer {
  display: flex;
  justify-content: flex-end;
  padding-top: 20px;
  border-top: 1px solid var(--border);
}

.btn-assemble {
  background: var(--green);
  border-color: #2ea043;
  color: #fff;
  padding: 10px 36px;
  font-size: 15px;
  font-weight: 600;
}
.btn-assemble:hover { background: #2ea043; }

/* ── 섹션 C: 상태 배지 ───────────────────────────────── */
.status-badge {
  display: flex;
  align-items: center;
  gap: 8px;
  padding: 6px 14px;
  background: var(--bg2);
  border: 1px solid var(--border);
  border-radius: 20px;
  font-size: 13px;
  font-weight: 500;
  transition: border-color 0.3s;
}

.status-dot {
  width: 8px;
  height: 8px;
  border-radius: 50%;
  background: var(--text2);
  flex-shrink: 0;
  transition: background 0.3s;
}

.status-dot.pulse { animation: dot-pulse 1.4s ease-in-out infinite; }
.status-dot.flash { animation: dot-flash 0.7s ease-in-out infinite; }

@keyframes dot-pulse {
  0%, 100% { opacity: 1; transform: scale(1); }
  50%       { opacity: 0.25; transform: scale(0.72); }
}

@keyframes dot-flash {
  0%, 100% { opacity: 1; }
  50%       { opacity: 0.1; }
}

.state-IDLE    .status-text { color: var(--text2); }
.state-RUNNING .status-text { color: var(--blue-lt); }
.state-PAUSED  .status-text { color: var(--yellow); }
.state-ERROR   .status-text { color: var(--red); }
.state-DONE    .status-text { color: var(--green); }

.state-RUNNING { border-color: var(--blue) !important; }
.state-PAUSED  { border-color: var(--yellow) !important; }
.state-ERROR   { border-color: var(--red) !important; }
.state-DONE    { border-color: var(--green) !important; }

/* ── 섹션 C: 진행률 바 ───────────────────────────────── */
.progress-row {
  display: flex;
  align-items: center;
  gap: 14px;
  margin-bottom: 16px;
}

.progress-track {
  flex: 1;
  height: 10px;
  background: var(--bg3);
  border-radius: 5px;
  overflow: hidden;
}

.progress-fill {
  height: 100%;
  width: 0%;
  background: linear-gradient(90deg, var(--blue) 0%, var(--blue-lt) 100%);
  border-radius: 5px;
  transition: width 0.6s cubic-bezier(0.4, 0, 0.2, 1);
}

.progress-meta {
  display: flex;
  align-items: center;
  gap: 6px;
  font-size: 13px;
  color: var(--text2);
  white-space: nowrap;
  min-width: 110px;
  justify-content: flex-end;
}

.progress-sep { opacity: 0.4; }

/* ── 섹션 C: 컨트롤 ──────────────────────────────────── */
.controls-row {
  display: flex;
  align-items: center;
  gap: 8px;
  margin-bottom: 20px;
}

.ctrl-divider {
  width: 1px;
  height: 28px;
  background: var(--border);
  margin: 0 4px;
}

.btn-demo {
  background: var(--green);
  border-color: #2ea043;
  color: #fff;
}
.btn-demo:hover:not(:disabled) { background: #2ea043; }

.btn-pause {
  background: var(--bg3);
  border-color: var(--border);
  color: var(--text);
}
.btn-pause:hover:not(:disabled) { border-color: var(--blue-lt); color: var(--blue-lt); }

.btn-recal {
  background: var(--bg3);
  border-color: var(--border);
  color: var(--text);
}
.btn-recal:hover:not(:disabled) { border-color: var(--yellow); color: var(--yellow); }

.btn-fix {
  background: var(--bg3);
  border-color: var(--border);
  color: var(--text2);
}
.btn-fix.active { border-color: var(--red); color: var(--red); }
.btn-fix:hover:not(:disabled) { border-color: var(--red); color: var(--red); }

/* ── 섹션 C: 3열 레이아웃 ────────────────────────────── */
.tri-grid {
  display: grid;
  grid-template-columns: 370px 1fr 340px;
  gap: 16px;
  align-items: start;
}

.panel {
  background: var(--bg2);
  border: 1px solid var(--border);
  border-radius: var(--radius);
  overflow: hidden;
}

.panel-header {
  display: flex;
  align-items: center;
  justify-content: space-between;
  padding: 10px 14px;
  border-bottom: 1px solid var(--border);
  background: var(--bg3);
}

.panel-title {
  font-size: 13px;
  font-weight: 600;
  color: var(--text);
}

.badge-sim {
  font-size: 10px;
  font-weight: 700;
  letter-spacing: 0.5px;
  padding: 2px 7px;
  background: rgba(31,111,235,0.15);
  border: 1px solid rgba(31,111,235,0.4);
  border-radius: 4px;
  color: var(--blue-lt);
}

.canvas-wrap {
  display: flex;
  justify-content: center;
  padding: 16px;
}

.webcam-footer {
  padding: 8px 14px;
  border-top: 1px solid var(--border);
  font-size: 12px;
  color: var(--text2);
  font-family: monospace;
  background: var(--bg3);
  min-height: 32px;
}

.compare-wrap {
  display: flex;
  align-items: flex-start;
  justify-content: center;
  padding: 16px 12px;
}

.grid-block {
  display: flex;
  flex-direction: column;
  align-items: center;
  gap: 8px;
}

.grid-label {
  font-size: 11px;
  font-weight: 600;
  letter-spacing: 0.5px;
  text-transform: uppercase;
  color: var(--text2);
}

.compare-divider {
  width: 1px;
  background: var(--border);
  align-self: stretch;
  margin: 0 16px;
}

.cur-pos-bar {
  padding: 6px 14px;
  border-top: 1px solid var(--border);
  font-size: 12px;
  color: var(--text2);
  font-family: monospace;
  background: var(--bg3);
  min-height: 30px;
}

.btn-log-clear {
  background: none;
  border: none;
  font-size: 11px;
  color: var(--text2);
  cursor: pointer;
  padding: 2px 6px;
  border-radius: 4px;
}
.btn-log-clear:hover { background: var(--bg); color: var(--text); }

/* ── 섹션 D: 결과 요약 ───────────────────────────────────── */
.sec-d { border-bottom: none; }

.done-badge {
  padding: 5px 16px;
  background: rgba(35, 134, 54, 0.12);
  border: 1px solid var(--green);
  border-radius: 20px;
  font-size: 13px;
  font-weight: 600;
  color: #3fb950;
  letter-spacing: 0.2px;
}

.result-cards {
  display: grid;
  grid-template-columns: repeat(3, 1fr);
  gap: 20px;
  margin-bottom: 32px;
}

.result-card {
  padding: 36px 24px 28px;
  border: 1px solid var(--border);
  border-radius: 12px;
  background: var(--bg2);
  display: flex;
  flex-direction: column;
  align-items: center;
  gap: 10px;
  text-align: center;
  animation: card-reveal 0.45s cubic-bezier(0.22, 1, 0.36, 1) both;
}

.result-card:nth-child(2) { animation-delay: 0.1s; }
.result-card:nth-child(3) { animation-delay: 0.2s; }

@keyframes card-reveal {
  from { opacity: 0; transform: translateY(20px); }
  to   { opacity: 1; transform: translateY(0); }
}

.card-green { border-color: rgba(35, 134, 54, 0.5);  background: rgba(35, 134, 54, 0.06);  }
.card-red   { border-color: rgba(218, 54, 51, 0.5);  background: rgba(218, 54, 51, 0.06);  }
.card-blue  { border-color: rgba(31, 111, 235, 0.5); background: rgba(31, 111, 235, 0.06); }

.card-icon {
  font-size: 26px;
  opacity: 0.65;
  line-height: 1;
}

.card-val {
  font-size: 56px;
  font-weight: 700;
  font-family: monospace;
  line-height: 1;
  letter-spacing: -2px;
}

.card-green .card-val { color: #3fb950; }
.card-red   .card-val { color: #f85149; }
.card-blue  .card-val { color: var(--blue-lt); }

.card-label {
  font-size: 12px;
  font-weight: 700;
  color: var(--text2);
  text-transform: uppercase;
  letter-spacing: 0.6px;
}

.card-sub {
  font-size: 13px;
  color: var(--text2);
}

.result-actions {
  display: flex;
  justify-content: center;
  padding-top: 4px;
}

.btn-download {
  background: var(--bg2);
  border: 1px solid var(--border);
  color: var(--text);
  padding: 10px 28px;
  font-size: 14px;
  border-radius: var(--radius);
  cursor: pointer;
  font-family: inherit;
  transition: border-color 0.15s, color 0.15s;
}
.btn-download:hover { border-color: var(--blue-lt); color: var(--blue-lt); }

.log-stream {
  height: 360px;
  overflow-y: auto;
  padding: 8px 0;
  font-family: 'Consolas', 'Courier New', monospace;
  font-size: 11.5px;
  line-height: 1.6;
  scrollbar-width: thin;
  scrollbar-color: var(--bg3) transparent;
}

.log-stream::-webkit-scrollbar { width: 4px; }
.log-stream::-webkit-scrollbar-thumb { background: var(--bg3); border-radius: 2px; }

.log-entry {
  display: flex;
  gap: 6px;
  padding: 2px 14px;
}

.log-entry:hover { background: rgba(255,255,255,0.03); }

.log-ts    { color: #4d5566; flex-shrink: 0; }
.log-level { font-weight: 600; flex-shrink: 0; width: 46px; }
.log-text  { color: var(--text2); word-break: break-all; }

.log-info  .log-level { color: #4c8ac5; }
.log-warn  .log-level { color: var(--yellow); }
.log-error .log-level { color: var(--red); }
.log-error .log-text  { color: #f5a0a0; }

/* ── 섹션 C: 다음 블록 바 ────────────────────────────── */
.next-bar {
  display: flex;
  align-items: center;
  gap: 10px;
  margin-top: 14px;
  padding: 12px 18px;
  background: var(--bg2);
  border: 1px solid var(--border);
  border-radius: var(--radius);
  font-size: 14px;
}

.next-label {
  font-size: 11px;
  font-weight: 700;
  text-transform: uppercase;
  letter-spacing: 0.5px;
  color: var(--text2);
  margin-right: 4px;
}

.next-pos   { font-family: monospace; color: var(--blue-lt); }
.next-sep   { color: var(--border); }

.next-swatch {
  width: 20px;
  height: 20px;
  border-radius: 4px;
  border: 1px solid rgba(255,255,255,0.12);
  display: none;
  flex-shrink: 0;
}

.next-name { color: var(--text); font-weight: 500; }

/* ── 오류 카드 오버레이 ──────────────────────────────── */
.err-overlay {
  display: none;
  position: fixed;
  inset: 0;
  background: rgba(0,0,0,0.72);
  z-index: 1000;
  align-items: center;
  justify-content: center;
  backdrop-filter: blur(3px);
}

.err-overlay.visible { display: flex; }

.err-card {
  background: var(--bg2);
  border: 1px solid var(--red);
  border-radius: 12px;
  width: 460px;
  box-shadow: 0 20px 60px rgba(0,0,0,0.6), 0 0 0 1px rgba(218,54,51,0.15);
  animation: card-in 0.2s ease;
}

@keyframes card-in {
  from { transform: scale(0.94) translateY(-12px); opacity: 0; }
  to   { transform: scale(1) translateY(0); opacity: 1; }
}

.err-card-head {
  display: flex;
  align-items: center;
  gap: 10px;
  padding: 16px 20px;
  border-bottom: 1px solid var(--border);
  background: rgba(218,54,51,0.08);
  border-radius: 12px 12px 0 0;
}

.err-icon { font-size: 20px; }

.err-card-head h3 {
  font-size: 15px;
  font-weight: 600;
  color: #f5a0a0;
}

.err-card-body {
  padding: 20px;
  display: flex;
  flex-direction: column;
  gap: 16px;
}

.err-location {
  font-family: monospace;
  font-size: 13px;
  color: var(--text2);
}

.err-colors {
  display: flex;
  align-items: center;
  gap: 20px;
}

.err-color-item {
  display: flex;
  flex-direction: column;
  align-items: center;
  gap: 6px;
}

.color-swatch-lg {
  width: 56px;
  height: 56px;
  border-radius: 8px;
  border: 2px solid rgba(255,255,255,0.12);
}

.color-tag {
  font-size: 11px;
  color: var(--text2);
  text-transform: uppercase;
  letter-spacing: 0.5px;
}

.color-nm { font-size: 13px; font-weight: 500; }

.err-arrow {
  font-size: 24px;
  color: var(--text2);
  padding-bottom: 20px;
}

.err-msg {
  font-size: 13px;
  color: var(--text2);
  line-height: 1.5;
}

.err-fix { display: flex; flex-direction: column; gap: 10px; }

.err-fix-label {
  font-size: 11px;
  font-weight: 700;
  color: var(--text2);
  text-transform: uppercase;
  letter-spacing: 0.4px;
}

.err-palette { display: flex; gap: 8px; flex-wrap: wrap; }

.palette-swatch {
  width: 36px;
  height: 36px;
  border-radius: 6px;
  border: 2px solid transparent;
  cursor: pointer;
  transition: transform 0.12s, border-color 0.12s;
}

.palette-swatch:hover {
  transform: scale(1.18);
  border-color: rgba(255,255,255,0.5);
}

.err-card-foot {
  display: flex;
  justify-content: flex-end;
  padding: 14px 20px;
  border-top: 1px solid var(--border);
  background: var(--bg3);
  border-radius: 0 0 12px 12px;
}

.btn-dismiss {
  background: var(--bg2);
  border: 1px solid var(--border);
  color: var(--text2);
  padding: 7px 18px;
  border-radius: var(--radius);
  font-size: 13px;
  cursor: pointer;
  transition: border-color 0.15s, color 0.15s;
  font-family: inherit;
}
.btn-dismiss:hover { border-color: var(--text2); color: var(--text); }
```

---

## 6. config/colors.yaml

**경로:** `lego_assembler/config/colors.yaml`

```yaml
# 블록 색상별 HSV 범위 (추후 실제 보정값으로 교체)
colors:
  red:
    lower: [0, 120, 70]
    upper: [10, 255, 255]
    hex: "#e3000b"
  blue:
    lower: [100, 150, 50]
    upper: [130, 255, 255]
    hex: "#006cb7"
  yellow:
    lower: [20, 100, 100]
    upper: [35, 255, 255]
    hex: "#ffcd00"
  green:
    lower: [40, 70, 50]
    upper: [80, 255, 255]
    hex: "#00a650"
  white:
    lower: [0, 0, 200]
    upper: [180, 30, 255]
    hex: "#ffffff"
  black:
    lower: [0, 0, 0]
    upper: [180, 255, 50]
    hex: "#1a1a1a"
  orange:
    lower: [10, 150, 100]
    upper: [20, 255, 255]
    hex: "#f47920"
  gray:
    lower: [0, 0, 100]
    upper: [180, 30, 200]
    hex: "#9e9e9e"
```

---

## 7. config/robot.yaml

**경로:** `lego_assembler/config/robot.yaml`

```yaml
# 두산 로봇 설정 (추후 실제 값으로 교체)
robot:
  model: "M0609"
  ip: "192.168.1.100"
  port: 12345
  speed: 50          # 기본 속도 (%)
  acceleration: 30   # 기본 가속도 (%)

workspace:
  origin: [300, 0, 150]   # 작업 원점 (mm)
  block_size: 8            # 블록 단위 크기 (mm)
  grid_offset_x: 0
  grid_offset_y: 0

camera:
  device_id: 0
  width: 1280
  height: 720
  fps: 30
```

---

## 8. requirements.txt

**경로:** `lego_assembler/requirements.txt`

```
flask
flask-socketio
opencv-python
pyyaml
numpy
```

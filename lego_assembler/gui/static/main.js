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
// TODO: [실제 이미지 처리 연결 시] 서버 측 이미지→격자 변환 결과로 payload 교체
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

// TODO: [실제 이미지 처리 연결 시] 서버에서 받은 grid 데이터로 직접 그리도록 교체
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

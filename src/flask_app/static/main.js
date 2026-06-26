const socket = io();

const COLOR_HEX = {
  red: "#e3000b", blue: "#006cb7", yellow: "#ffcd00", green: "#00a650",
};

let currentGrid = null;
let currentBlockMap = null;
let GRID_W = 16;
let GRID_H = 8;
let selectedColor = "red";

// ── 색상 팔레트 생성 ──

const palette = document.getElementById("color-palette");
for (const [name, hex] of Object.entries(COLOR_HEX)) {
  const btn = document.createElement("div");
  btn.className = "palette-btn" + (name === selectedColor ? " selected" : "");
  btn.style.background = hex;
  btn.title = name;
  btn.addEventListener("click", () => {
    document.querySelectorAll(".palette-btn").forEach(b => b.classList.remove("selected"));
    btn.classList.add("selected");
    selectedColor = name;
  });
  palette.appendChild(btn);
}

// ── 이미지 업로드 ──

const fileInput = document.getElementById("file-input");
const preview   = document.getElementById("preview");

fileInput.addEventListener("change", (e) => {
  const file = e.target.files[0];
  if (!file) return;
  const reader = new FileReader();
  reader.onload = (ev) => {
    preview.src = ev.target.result;
    preview.style.display = "block";
    document.getElementById("btn-analyze").disabled = false;
  };
  reader.readAsDataURL(file);
});

// ── 분석 요청 ──

document.getElementById("btn-analyze").addEventListener("click", () => {
  if (!preview.src) return;
  GRID_W = parseInt(document.getElementById("input-cols").value) || 16;
  GRID_H = parseInt(document.getElementById("input-rows").value) || 8;
  socket.emit("upload_image", {
    image_data: preview.src,
    grid_rows: GRID_H,
    grid_cols: GRID_W,
  });
  addLog("INFO", `이미지 분석 요청 전송 (${GRID_W}×${GRID_H})`);
});

// ── 격자 드래그 편집 ──

const canvas = document.getElementById("grid-canvas");
let painting = false;
let paintButton = -1;
let lastPaintedCell = null;

function getCellFromEvent(e) {
  const rect = canvas.getBoundingClientRect();
  const scaleX = canvas.width / rect.width;
  const scaleY = canvas.height / rect.height;
  const cs = Math.floor(canvas.width / GRID_W);
  const col = Math.floor((e.clientX - rect.left) * scaleX / cs);
  const row = Math.floor((e.clientY - rect.top) * scaleY / cs);
  if (row < 0 || row >= GRID_H || col < 0 || col >= GRID_W) return null;
  return { row, col };
}

function paintCell(cell, button) {
  if (!cell || !currentGrid) return;
  if (lastPaintedCell && lastPaintedCell.row === cell.row && lastPaintedCell.col === cell.col) return;
  lastPaintedCell = cell;

  if (button === 2) {
    currentGrid[cell.row][cell.col] = "";
    currentBlockMap = null;
    drawGrid(currentGrid);
  } else {
    currentGrid[cell.row][cell.col] = selectedColor;
    currentBlockMap = null;
    drawGrid(currentGrid);
  }
}

canvas.addEventListener("mousedown", (e) => {
  if (!currentGrid) return;
  e.preventDefault();
  painting = true;
  paintButton = e.button;
  lastPaintedCell = null;
  paintCell(getCellFromEvent(e), e.button);
});

canvas.addEventListener("mousemove", (e) => {
  if (!painting) return;
  paintCell(getCellFromEvent(e), paintButton);
});

canvas.addEventListener("mouseup", () => { painting = false; });
canvas.addEventListener("mouseleave", () => { painting = false; });

canvas.addEventListener("contextmenu", (e) => { e.preventDefault(); });

// ── 수정 반영 ──

document.getElementById("btn-update").addEventListener("click", () => {
  if (!currentGrid) return;
  socket.emit("update_grid", {
    grid_json: JSON.stringify(currentGrid),
  });
  addLog("INFO", "격자 수정 반영 요청");
});

// ── 조립 시작 ──

document.getElementById("btn-start").addEventListener("click", () => {
  if (!currentGrid) return;
  socket.emit("start_assembly", {
    grid_json: JSON.stringify(currentGrid),
  });
  addLog("INFO", "조립 시작 요청");
});

// ── 일시정지 / 재개 ──

document.getElementById("btn-pause").addEventListener("click", () => socket.emit("pause"));
document.getElementById("btn-resume").addEventListener("click", () => socket.emit("resume"));

// ── 서버 이벤트 수신 ──

socket.on("analysis_result", (data) => {
  if (data.success) {
    if (data.grid_cols) GRID_W = data.grid_cols;
    if (data.grid_rows) GRID_H = data.grid_rows;
    const flat = JSON.parse(data.grid_json);
    currentGrid = [];
    for (let r = 0; r < GRID_H; r++) {
      currentGrid.push(flat.slice(r * GRID_W, (r + 1) * GRID_W));
    }
    drawGrid(currentGrid);
    document.getElementById("section-result").classList.remove("hidden");
    addLog("INFO", `이미지 분석 완료 (${GRID_W}×${GRID_H})`);
  } else {
    addLog("ERROR", "분석 실패: " + data.error_message);
  }
});

socket.on("grid_updated", (data) => {
  addLog("INFO", "격자 수정 반영 완료");
});

socket.on("block_plan", (data) => {
  if (!currentGrid) return;
  currentBlockMap = buildBlockMap(data.blocks, currentGrid);
  drawGrid(currentGrid);
  addLog("INFO", "블록 분할 미리보기 표시: " + data.blocks.length + "개 블록");
});

socket.on("assembly_started", () => {
  document.getElementById("status").textContent = "조립 시작됨";
  document.getElementById("btn-pause").disabled = false;
  document.getElementById("btn-resume").disabled = false;
  addLog("INFO", "조립 시작됨");
});

socket.on("assembly_progress", (data) => {
  const pct = data.total_steps > 0
    ? Math.round((data.current_step / data.total_steps) * 100) : 0;
  document.getElementById("progress-fill").style.width = pct + "%";
  document.getElementById("progress-text").textContent =
    data.current_step + " / " + data.total_steps;
  document.getElementById("status").textContent =
    "진행 중 — " + data.current_action + " " + data.current_color;
  addLog("INFO",
    "Step " + data.current_step + ": " +
    data.current_action + " " + data.current_color);
});

socket.on("assembly_done", (data) => {
  document.getElementById("status").textContent = "조립 완료";
  document.getElementById("progress-fill").style.width = "100%";
  document.getElementById("btn-pause").disabled = true;
  document.getElementById("btn-resume").disabled = true;
  addLog("INFO", "조립 완료 — " + data.completed_steps + "개 블록");
});

socket.on("assembly_error", (data) => {
  document.getElementById("status").textContent =
    "오류 — Step " + data.failed_step;
  addLog("ERROR", "오류: " + data.error_message);
});

// ── 블록 맵 재구성 ──

function buildBlockMap(blocks, grid) {
  const map = Array.from({length: GRID_H}, () => Array(GRID_W).fill(-1));
  let tIdx = 0;
  let bid = 0;

  for (let layer = 0; layer < GRID_H; layer++) {
    const row = GRID_H - 1 - layer;

    const runs = [];
    let i = 0;
    while (i < GRID_W) {
      const color = grid[row][i];
      if (!color || color === "" || color === "empty") { i++; continue; }
      let len = 1;
      while (i + len < GRID_W && grid[row][i + len] === color) len++;
      if (len >= 2) runs.push({len, start: i});
      i += len;
    }

    const totalCells = runs.reduce((s, r) => s + r.len, 0);
    const rowTasks = [];
    let covered = 0;
    while (tIdx < blocks.length && covered < totalCells) {
      const w = blocks[tIdx].block_type === 1 ? 2 : 3;
      rowTasks.push(w);
      covered += w;
      tIdx++;
    }
    if (layer % 2 === 1) rowTasks.reverse();

    let rtIdx = 0;
    for (const run of runs) {
      let col = run.start;
      let rem = run.len;
      while (rem > 0 && rtIdx < rowTasks.length) {
        const w = rowTasks[rtIdx];
        for (let c = col; c < col + w; c++) map[row][c] = bid;
        bid++;
        col += w;
        rem -= w;
        rtIdx++;
      }
    }
  }
  return map;
}

// ── 격자 그리기 ──

function drawGrid(grid) {
  const ctx = canvas.getContext("2d");
  const cs = Math.floor(canvas.width / GRID_W);
  const h = cs * GRID_H;
  canvas.height = h;
  ctx.fillStyle = "#0d1117";
  ctx.fillRect(0, 0, canvas.width, h);
  for (let r = 0; r < GRID_H; r++) {
    for (let c = 0; c < GRID_W; c++) {
      ctx.fillStyle = COLOR_HEX[grid[r][c]] || "#333";
      ctx.fillRect(c * cs + 1, r * cs + 1, cs - 2, cs - 2);
    }
  }

  if (currentBlockMap) {
    ctx.strokeStyle = "#bf00ff";
    ctx.lineWidth = 3;
    const drawn = new Set();
    for (let r = 0; r < GRID_H; r++) {
      for (let c = 0; c < GRID_W; c++) {
        const bid = currentBlockMap[r][c];
        if (bid < 0 || drawn.has(bid)) continue;
        let endC = c;
        while (endC + 1 < GRID_W && currentBlockMap[r][endC + 1] === bid) endC++;
        ctx.strokeRect(c * cs, r * cs, (endC - c + 1) * cs, cs);
        drawn.add(bid);
      }
    }
  }
}

// ── 로그 ──

function addLog(level, text) {
  const stream = document.getElementById("log-stream");
  const el = document.createElement("div");
  el.className = "log-entry log-" + level;
  const ts = new Date().toLocaleTimeString("ko-KR", { hour12: false });
  el.textContent = "[" + ts + "] [" + level + "] " + text;
  stream.appendChild(el);
  stream.scrollTop = stream.scrollHeight;
}

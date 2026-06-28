const socket = io();

const COLOR_HEX = {
  red: "#e3000b", blue: "#006cb7", yellow: "#ffcd00", green: "#00a650",
};

let currentGrid = null;
let currentBlockMap = null;
let GRID_W = 16;
let GRID_H = 8;
let selectedColor = "red";
const CELL_ASPECT_W = 15.9;
const CELL_ASPECT_H = 19.0;

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

// ── 이미지 업로드 & ROI 선택 ──

const fileInput       = document.getElementById("file-input");
const preview         = document.getElementById("preview");
const previewWrapper  = document.getElementById("preview-wrapper");
const roiCanvas       = document.getElementById("roi-canvas");
const roiCtx          = roiCanvas.getContext("2d");
const roiHint         = document.getElementById("roi-hint");
const roiControls     = document.getElementById("roi-controls");
const btnClearRoi     = document.getElementById("btn-clear-roi");

let roi = null;          // {x0, y0, x1, y1} 원본 이미지 픽셀 기준
let roiDragging = false;
let roiDragStart = null;

function syncRoiCanvas() {
  roiCanvas.width  = preview.offsetWidth;
  roiCanvas.height = preview.offsetHeight;
  drawRoiRect();
}

function drawRoiRect() {
  roiCtx.clearRect(0, 0, roiCanvas.width, roiCanvas.height);
  if (!roi) return;
  const sx = preview.offsetWidth  / preview.naturalWidth;
  const sy = preview.offsetHeight / preview.naturalHeight;
  const x = roi.x0 * sx, y = roi.y0 * sy;
  const w = (roi.x1 - roi.x0) * sx, h = (roi.y1 - roi.y0) * sy;
  roiCtx.strokeStyle = "#00e5ff";
  roiCtx.lineWidth = 2;
  roiCtx.setLineDash([6, 3]);
  roiCtx.strokeRect(x, y, w, h);
  roiCtx.fillStyle = "rgba(0,229,255,0.08)";
  roiCtx.fillRect(x, y, w, h);
}

function canvasToImagePos(e) {
  const rect = roiCanvas.getBoundingClientRect();
  const sx = preview.naturalWidth  / preview.offsetWidth;
  const sy = preview.naturalHeight / preview.offsetHeight;
  return {
    x: Math.round(Math.max(0, Math.min(preview.naturalWidth,  (e.clientX - rect.left) * sx))),
    y: Math.round(Math.max(0, Math.min(preview.naturalHeight, (e.clientY - rect.top)  * sy))),
  };
}

roiCanvas.addEventListener("mousedown", (e) => {
  if (!preview.naturalWidth) return;
  e.preventDefault();
  roiDragging = true;
  roiDragStart = canvasToImagePos(e);
  roi = null;
  drawRoiRect();
});

roiCanvas.addEventListener("mousemove", (e) => {
  if (!roiDragging) return;
  const pos = canvasToImagePos(e);
  roi = {
    x0: Math.min(roiDragStart.x, pos.x), y0: Math.min(roiDragStart.y, pos.y),
    x1: Math.max(roiDragStart.x, pos.x), y1: Math.max(roiDragStart.y, pos.y),
  };
  drawRoiRect();
});

roiCanvas.addEventListener("mouseup", (e) => {
  if (!roiDragging) return;
  roiDragging = false;
  if (roi && (roi.x1 - roi.x0 < 10 || roi.y1 - roi.y0 < 10)) roi = null;
  roiControls.style.display = roi ? "" : "none";
  drawRoiRect();
});

roiCanvas.addEventListener("mouseleave", () => {
  if (!roiDragging) return;
  roiDragging = false;
  if (roi && (roi.x1 - roi.x0 < 10 || roi.y1 - roi.y0 < 10)) roi = null;
  roiControls.style.display = roi ? "" : "none";
  drawRoiRect();
});

btnClearRoi.addEventListener("click", () => {
  roi = null;
  roiControls.style.display = "none";
  drawRoiRect();
});

preview.addEventListener("load", () => {
  syncRoiCanvas();
  roiHint.style.display = "";
});

window.addEventListener("resize", () => {
  if (preview.naturalWidth) syncRoiCanvas();
});

fileInput.addEventListener("change", (e) => {
  const file = e.target.files[0];
  if (!file) return;
  const reader = new FileReader();
  reader.onload = (ev) => {
    roi = null;
    roiControls.style.display = "none";
    preview.src = ev.target.result;
    previewWrapper.style.display = "inline-block";
    document.getElementById("btn-analyze").disabled = false;
  };
  reader.readAsDataURL(file);
});

function getCroppedImageData() {
  if (!roi || roi.x1 - roi.x0 < 10 || roi.y1 - roi.y0 < 10) {
    return { imageData: preview.src, roiSelected: false };
  }
  const w = roi.x1 - roi.x0, h = roi.y1 - roi.y0;
  const offscreen = document.createElement("canvas");
  offscreen.width = w;
  offscreen.height = h;
  const img = new Image();
  img.src = preview.src;
  offscreen.getContext("2d").drawImage(img, roi.x0, roi.y0, w, h, 0, 0, w, h);
  return { imageData: offscreen.toDataURL("image/jpeg", 0.92), roiSelected: true };
}

// ── 분석 요청 ──

document.getElementById("btn-analyze").addEventListener("click", () => {
  if (!preview.src) return;
  GRID_W = parseInt(document.getElementById("input-cols").value) || 16;
  GRID_H = parseInt(document.getElementById("input-rows").value) || 8;
  const { imageData, roiSelected } = getCroppedImageData();
  socket.emit("upload_image", {
    image_data: imageData,
    grid_rows: GRID_H,
    grid_cols: GRID_W,
    roi_selected: roiSelected,
  });
  addLog("INFO", `이미지 분석 요청 전송 (${GRID_W}×${GRID_H})${roiSelected ? " [ROI 선택]" : ""}`);
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
  const cellWidth = canvas.width / GRID_W;
  const cellHeight = canvas.height / GRID_H;
  const col = Math.floor((e.clientX - rect.left) * scaleX / cellWidth);
  const row = Math.floor((e.clientY - rect.top) * scaleY / cellHeight);
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
    grid_rows: GRID_H,
    grid_cols: GRID_W,
  });
  const summaryEl = document.getElementById("block-summary");
  document.getElementById("block-summary-table").innerHTML = '<p style="color:#8b949e;margin:0">계산 중...</p>';
  summaryEl.classList.remove("hidden");
  addLog("INFO", "격자 수정 반영 요청");
});

// ── 조립 시작 ──

document.getElementById("btn-start").addEventListener("click", () => {
  if (!currentGrid) return;
  socket.emit("start_assembly", {
    grid_json: JSON.stringify(currentGrid),
    grid_rows: GRID_H,
    grid_cols: GRID_W,
  });
  addLog("INFO", "조립 시작 요청");
});

// ── 일시정지 / 재개 ──

document.getElementById("btn-pause").addEventListener("click", () => {
  socket.emit("pause");
  addLog("INFO", "일시정지 요청");
});
document.getElementById("btn-resume").addEventListener("click", () => {
  socket.emit("resume");
  addLog("INFO", "재개 요청");
});

// ── 서버 이벤트 수신 ──

socket.on("analysis_result", (data) => {
  if (data.success) {
    const parsed = JSON.parse(data.grid_json || "[]");
    if (Array.isArray(parsed[0])) {
      currentGrid = parsed;
      GRID_H = currentGrid.length;
      GRID_W = currentGrid[0] ? currentGrid[0].length : 0;
    } else {
      GRID_W = parseInt(data.grid_cols) || GRID_W;
      GRID_H = parseInt(data.grid_rows) || GRID_H;
      currentGrid = [];
      for (let r = 0; r < GRID_H; r++) {
        const row = parsed.slice(r * GRID_W, (r + 1) * GRID_W);
        while (row.length < GRID_W) row.push("");
        currentGrid.push(row);
      }
    }
    document.getElementById("input-cols").value = GRID_W;
    document.getElementById("input-rows").value = GRID_H;
    currentBlockMap = null;
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
  const { map, blockInfo } = buildBlockMap(data.blocks, currentGrid);
  currentBlockMap = map;
  drawGrid(currentGrid);
  showBlockSummary(blockInfo);
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

socket.on("system_log", (data) => {
  addLog("WARN", data.message);
});

// ── 블록 맵 재구성 ──

function buildBlockMap(blocks, grid) {
  const map = Array.from({length: GRID_H}, () => Array(GRID_W).fill(-1));
  const blockInfo = []; // [{color, type}]
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
      if (len >= 2) runs.push({len, start: i, color});
      i += len;
    }

    const totalCells = runs.reduce((s, r) => s + r.len, 0);
    const rowTasks = [];
    let covered = 0;
    while (tIdx < blocks.length && covered < totalCells) {
      const btype = blocks[tIdx].block_type;
      const w = btype === 1 ? 2 : 3;
      rowTasks.push({w, btype});
      covered += w;
      tIdx++;
    }
    let rtIdx = 0;
    for (const run of runs) {
      let col = run.start;
      let rem = run.len;
      while (rem > 0 && rtIdx < rowTasks.length) {
        const {w, btype} = rowTasks[rtIdx];
        for (let c = col; c < col + w; c++) map[row][c] = bid;
        blockInfo.push({color: run.color, type: btype});
        bid++;
        col += w;
        rem -= w;
        rtIdx++;
      }
    }
  }
  return {map, blockInfo};
}

// ── 격자 그리기 ──

function drawGrid(grid) {
  const ctx = canvas.getContext("2d");
  const h = Math.max(
    GRID_H,
    Math.round(canvas.width * (GRID_H * CELL_ASPECT_H) / (GRID_W * CELL_ASPECT_W))
  );
  canvas.height = h;
  const cellWidth = canvas.width / GRID_W;
  const cellHeight = canvas.height / GRID_H;
  ctx.fillStyle = "#0d1117";
  ctx.fillRect(0, 0, canvas.width, h);
  for (let r = 0; r < GRID_H; r++) {
    for (let c = 0; c < GRID_W; c++) {
      const color = grid[r] ? grid[r][c] : "";
      ctx.fillStyle = COLOR_HEX[color] || "#333";
      ctx.fillRect(
        c * cellWidth + 1,
        r * cellHeight + 1,
        Math.max(1, cellWidth - 2),
        Math.max(1, cellHeight - 2)
      );
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
        ctx.strokeRect(
          c * cellWidth,
          r * cellHeight,
          (endC - c + 1) * cellWidth,
          cellHeight
        );
        drawn.add(bid);
      }
    }
  }
}

// ── 블록 요약 ──

const COLOR_LABEL = { red: "빨강", blue: "파랑", yellow: "노랑", green: "초록" };

function showBlockSummary(blockInfo) {
  // {color → {t1: count, t2: count}}
  const stats = {};
  for (const color of Object.keys(COLOR_HEX)) stats[color] = {t1: 0, t2: 0};

  for (const {color, type} of blockInfo) {
    if (!stats[color]) continue;
    if (type === 1) stats[color].t1++;
    else            stats[color].t2++;
  }

  const activeColors = Object.keys(COLOR_HEX).filter(c => stats[c].t1 + stats[c].t2 > 0);
  let totalT1 = 0, totalT2 = 0;

  const rows = activeColors.map(color => {
    const {t1, t2} = stats[color];
    totalT1 += t1; totalT2 += t2;
    return `
      <tr>
        <td><span class="summary-swatch" style="background:${COLOR_HEX[color]}"></span> ${COLOR_LABEL[color] || color}</td>
        <td class="summary-count">${t1}개</td>
        <td class="summary-count">${t2}개</td>
        <td class="summary-count">${t1 + t2}개</td>
      </tr>`;
  }).join("");

  document.getElementById("block-summary-table").innerHTML = `
    <table class="summary-table">
      <thead>
        <tr>
          <th>색상</th>
          <th class="summary-count">유형1 (2칸)</th>
          <th class="summary-count">유형2 (3칸)</th>
          <th class="summary-count">합계</th>
        </tr>
      </thead>
      <tbody>${rows || '<tr><td colspan="4" style="color:#8b949e">블록 없음</td></tr>'}</tbody>
      <tfoot>
        <tr>
          <td><strong>합계</strong></td>
          <td class="summary-count"><strong>${totalT1}개</strong></td>
          <td class="summary-count"><strong>${totalT2}개</strong></td>
          <td class="summary-count"><strong>${totalT1 + totalT2}개</strong></td>
        </tr>
      </tfoot>
    </table>`;

  document.getElementById("block-summary").classList.remove("hidden");
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

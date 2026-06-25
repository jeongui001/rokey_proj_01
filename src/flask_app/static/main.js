const socket = io();

const COLOR_HEX = {
  red: "#e3000b", blue: "#006cb7", yellow: "#ffcd00", green: "#00a650",
  white: "#f0f0f0", black: "#2a2a2a", pink: "#f06292", purple: "#9c27b0",
};

let currentGrid = null;
const GRID_W = 24;
const GRID_H = 10;
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
  socket.emit("upload_image", {
    image_data: preview.src,
  });
  addLog("INFO", "이미지 분석 요청 전송");
});

// ── 격자 클릭 편집 ──

const canvas = document.getElementById("grid-canvas");

canvas.addEventListener("click", (e) => {
  if (!currentGrid) return;
  const rect = canvas.getBoundingClientRect();
  const cs = Math.floor(canvas.width / GRID_W);
  const col = Math.floor((e.clientX - rect.left) / cs);
  const row = Math.floor((e.clientY - rect.top) / cs);
  if (row < 0 || row >= GRID_H || col < 0 || col >= GRID_W) return;

  currentGrid[row][col] = selectedColor;
  drawGrid(currentGrid);
  addLog("INFO", `셀 (${row},${col}) → ${selectedColor}`);
});

canvas.addEventListener("contextmenu", (e) => {
  e.preventDefault();
  if (!currentGrid) return;
  const rect = canvas.getBoundingClientRect();
  const cs = Math.floor(canvas.width / GRID_W);
  const col = Math.floor((e.clientX - rect.left) / cs);
  const row = Math.floor((e.clientY - rect.top) / cs);
  if (row < 0 || row >= GRID_H || col < 0 || col >= GRID_W) return;

  currentGrid[row][col] = "";
  drawGrid(currentGrid);
  addLog("INFO", `셀 (${row},${col}) 비움`);
});

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
    const flat = JSON.parse(data.grid_json);
    currentGrid = [];
    for (let r = 0; r < GRID_H; r++) {
      currentGrid.push(flat.slice(r * GRID_W, (r + 1) * GRID_W));
    }
    drawGrid(currentGrid);
    document.getElementById("section-result").classList.remove("hidden");
    addLog("INFO", "이미지 분석 완료");
  } else {
    addLog("ERROR", "분석 실패: " + data.error_message);
  }
});

socket.on("grid_updated", (data) => {
  addLog("INFO", "격자 수정 반영 완료");
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

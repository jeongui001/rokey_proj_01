"""
ROI 4점 좌표 확인 스크립트 — 8종류 연속 측정.

사용법:
  python3 tools/roi_check.py

8가지 (유형, 색상) 조합을 순서대로 처리.
각 조합:
  1. 해당 블록을 카메라 앞에 위치 → 아무 곳이나 클릭 → 화면 고정
  2. 4점 클릭 (좌상→우상→우하→좌하) → 저장 → 자동으로 다음 조합
  '건너뜀' 버튼으로 현재 조합 스킵 가능

저장: tools/roi_results/{type}_{color}/roi_1_*.txt + snapshot_1_*.jpg
완료 후: python3 tools/build_config.py 실행
"""

import cv2
import matplotlib.pyplot as plt
import matplotlib.animation as animation
from matplotlib.widgets import Button
import numpy as np
from pathlib import Path
from datetime import datetime

DEVICE = 2
RESULTS_DIR = Path(__file__).parent / "roi_results"

COMBINATIONS = [
    ("2x2", "yellow"),
    ("2x2", "red"),
    ("2x2", "blue"),
    ("2x2", "green"),
    ("3x2", "yellow"),
    ("3x2", "red"),
    ("3x2", "blue"),
    ("3x2", "green"),
]

POINT_COLORS = ["red", "lime", "blue", "orange"]
POINT_LABELS = ["1 TL", "2 TR", "3 BR", "4 BL"]

# ── 전역 상태 ──────────────────────────────────────────────────────────────────
_combo_idx: int = 0
_frozen: bool = False
_points: list[tuple[int, int]] = []
_latest_frame: np.ndarray | None = None
_frozen_frame: np.ndarray | None = None
_drawn_artists: list = []
_done: list[str] = []

_cap = None
_fig = None
_ax = None
_im = None


def _cur() -> tuple[str, str]:
    return COMBINATIONS[_combo_idx]


def _folder() -> str:
    b, c = _cur()
    return f"{b}_{c}"


def _update_title() -> None:
    b, c = _cur()
    n = len(COMBINATIONS)
    idx = _combo_idx + 1
    if not _frozen:
        _ax.set_title(
            f"[{idx}/{n}]  {b} {c}  —  Click anywhere to freeze",
            fontsize=12,
        )
    else:
        done = len(_points)
        label = POINT_LABELS[done] if done < 4 else "done"
        _ax.set_title(
            f"[{idx}/{n}]  {b} {c}  —  Click 4 points ({done}/4): {label}",
            fontsize=12,
        )


def _save(frame: np.ndarray, pts: list[tuple[int, int]]) -> None:
    folder = RESULTS_DIR / _folder()
    folder.mkdir(parents=True, exist_ok=True)
    ts = datetime.now().strftime("%Y%m%d_%H%M%S")

    txt = folder / f"roi_1_{ts}.txt"
    lines = [f"# {_folder()} ROI 4점 (좌상, 우상, 우하, 좌하)"]
    for label, (x, y) in zip(["좌상", "우상", "우하", "좌하"], pts):
        lines.append(f"{label}: ({x}, {y})")
    txt.write_text("\n".join(lines), encoding="utf-8")

    img_path = folder / f"snapshot_1_{ts}.jpg"
    cv2.imwrite(str(img_path), cv2.cvtColor(frame, cv2.COLOR_RGB2BGR))

    pts_str = ", ".join(f"({x}, {y})" for x, y in pts)
    b, c = _cur()
    print(f"  [{_combo_idx+1}/{len(COMBINATIONS)}] {b} {c}  →  [{pts_str}]")
    _done.append(_folder())


def _advance() -> None:
    global _combo_idx, _frozen, _points, _frozen_frame, _drawn_artists

    _combo_idx += 1
    _frozen = False
    _points = []
    _frozen_frame = None
    for a in _drawn_artists:
        a.remove()
    _drawn_artists = []

    if _combo_idx >= len(COMBINATIONS):
        _finish()
        return

    b, c = _cur()
    print(f"\n[{_combo_idx+1}/{len(COMBINATIONS)}]  다음: {b} {c}  —  블록 교체 후 클릭")
    _update_title()
    plt.draw()


def _finish() -> None:
    skipped = [f"{b}_{c}" for b, c in COMBINATIONS if f"{b}_{c}" not in _done]
    print(f"\n완료: {_done}")
    if skipped:
        print(f"건너뜀: {skipped}")
    print("\n다음 단계: python3 tools/build_config.py")
    plt.close(_fig)


def _on_click(event) -> None:
    global _frozen, _frozen_frame, _drawn_artists

    if event.inaxes is None or event.xdata is None:
        return
    if _combo_idx >= len(COMBINATIONS):
        return

    if not _frozen:
        _frozen = True
        _frozen_frame = _latest_frame.copy() if _latest_frame is not None else None
        _update_title()
        plt.draw()
        return

    if len(_points) >= 4:
        return

    x, y = int(event.xdata), int(event.ydata)
    _points.append((x, y))
    idx = len(_points) - 1

    dot, = _ax.plot(x, y, "o", color=POINT_COLORS[idx], markersize=10, zorder=5)
    ann = _ax.annotate(
        POINT_LABELS[idx], (x, y),
        textcoords="offset points", xytext=(8, 8),
        color=POINT_COLORS[idx], fontsize=11, fontweight="bold", zorder=5,
    )
    _drawn_artists += [dot, ann]

    if len(_points) >= 2:
        xs = [p[0] for p in _points]
        ys = [p[1] for p in _points]
        if len(_points) == 4:
            xs.append(_points[0][0])
            ys.append(_points[0][1])
        line, = _ax.plot(xs, ys, "w--", linewidth=1.2, zorder=4)
        _drawn_artists.append(line)

    _update_title()
    plt.draw()

    if len(_points) == 4:
        _save(_frozen_frame, _points)
        _advance()


def _on_skip(_event) -> None:
    b, c = _cur()
    print(f"  [{_combo_idx+1}/{len(COMBINATIONS)}] {b} {c}  건너뜀")
    _advance()


def _update_frame(_, im):
    global _latest_frame
    if _frozen or _cap is None or not _cap.isOpened():
        return (im,)
    ok, frame = _cap.read()
    if not ok or frame is None:
        return (im,)
    rgb = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)
    _latest_frame = rgb
    im.set_data(rgb)
    return (im,)


def main() -> None:
    global _cap, _fig, _ax, _im, _latest_frame

    _cap = cv2.VideoCapture(DEVICE)
    if not _cap.isOpened():
        print(f"[오류] 카메라 열기 실패: /dev/video{DEVICE}")
        return

    ok, first = _cap.read()
    if not ok or first is None:
        print("[오류] 첫 프레임 캡처 실패")
        _cap.release()
        return

    first_rgb = cv2.cvtColor(first, cv2.COLOR_BGR2RGB)
    _latest_frame = first_rgb

    b, c = COMBINATIONS[0]
    print(f"측정 시작 — 총 {len(COMBINATIONS)}개 조합")
    print(f"[1/{len(COMBINATIONS)}]  먼저: {b} {c}  —  블록 위치 조정 후 클릭")

    _fig = plt.figure(figsize=(10, 7))
    plt.subplots_adjust(bottom=0.12)
    _ax = _fig.add_subplot(1, 1, 1)
    _im = _ax.imshow(first_rgb)
    _ax.axis("off")
    _update_title()

    ax_skip = _fig.add_axes([0.75, 0.02, 0.20, 0.06])
    btn_skip = Button(ax_skip, "Skip ->")
    btn_skip.on_clicked(_on_skip)

    _fig.canvas.mpl_connect("button_press_event", _on_click)

    ani = animation.FuncAnimation(
        _fig, _update_frame, fargs=(_im,),
        interval=50, blit=True, cache_frame_data=False,
    )

    plt.show()
    _cap.release()


if __name__ == "__main__":
    main()

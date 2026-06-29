"""
ROI + HoughCircles 설정 자동 빌드 스크립트.

사용법:
  python3 tools/build_config.py

roi_check.py 실행 후 tools/roi_results/ 에 저장된 8개 폴더를 순서대로 처리.
각 폴더:
  - ROI 좌표 자동 파싱 + 원근 변환 적용
  - 슬라이더로 HoughCircles 파라미터 실시간 조정
  - '다음 →' 버튼으로 다음 폴더 이동
모든 폴더 완료 후 webcam_checker_node.py 에 붙여넣을 설정 출력.
"""

from __future__ import annotations

import re
from pathlib import Path

import cv2
import matplotlib.pyplot as plt
from matplotlib.widgets import Button, Slider
import numpy as np

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

TYPE_MAP = {"2x2": 1, "3x2": 2}
INIT_HOUGH = dict(dp=1.2, min_dist=20, param1=50, param2=30, min_r=5, max_r=50, clip_limit=2.0)

_SLIDER_SPECS = [
    ("clip_limit", "CLAHE clip", 1.0, 8.0,  0.5),
    ("dp",         "dp",         0.5, 3.0,  0.1),
    ("min_dist",   "minDist",    5,   150,   1),
    ("param1",     "param1",     10,  250,   1),
    ("param2",     "param2",     5,   100,   1),
    ("min_r",      "minRadius",  1,   100,   1),
    ("max_r",      "maxRadius",  10,  200,   1),
]


# ── 유틸 ──────────────────────────────────────────────────────────────────────

def _parse_roi(folder: Path) -> list[tuple[int, int]] | None:
    txts = sorted(folder.glob("roi_*.txt"), reverse=True)
    if not txts:
        return None
    try:
        text = txts[0].read_text(encoding="utf-8")
        matches = re.findall(r"\((\d+),\s*(\d+)\)", text)
        pts = [(int(x), int(y)) for x, y in matches]
        return pts[:4] if len(pts) >= 4 else None
    except Exception:
        return None


def _load_snapshot(folder: Path) -> np.ndarray | None:
    snaps = sorted(folder.glob("snapshot_*.jpg"), reverse=True)
    if not snaps:
        return None
    img = cv2.imread(str(snaps[0]))
    return img  # BGR 그대로 반환 — 노드와 동일한 파이프라인


def _warp(image: np.ndarray, pts: list[tuple[int, int]] | None) -> np.ndarray:
    if pts is None:
        return image
    src = np.array(pts, dtype=np.float32)
    tl, tr, br, bl = src
    w = int(max(np.linalg.norm(tr - tl), np.linalg.norm(br - bl)))
    h = int(max(np.linalg.norm(bl - tl), np.linalg.norm(br - tr)))
    dst = np.array([[0, 0], [w-1, 0], [w-1, h-1], [0, h-1]], dtype=np.float32)
    M = cv2.getPerspectiveTransform(src, dst)
    return cv2.warpPerspective(image, M, (w, h))


def _detect(image_bgr: np.ndarray, p: dict) -> tuple[np.ndarray, int]:
    gray = cv2.cvtColor(image_bgr, cv2.COLOR_BGR2GRAY)  # 노드와 동일
    clahe = cv2.createCLAHE(clipLimit=p.get("clip_limit", 1.0), tileGridSize=(8, 8))
    gray = clahe.apply(gray)
    blurred = cv2.GaussianBlur(gray, (9, 9), 2)
    circles = cv2.HoughCircles(
        blurred, cv2.HOUGH_GRADIENT,
        dp=p["dp"], minDist=p["min_dist"],
        param1=p["param1"], param2=p["param2"],
        minRadius=int(p["min_r"]), maxRadius=int(p["max_r"]),
    )
    result = cv2.cvtColor(image_bgr, cv2.COLOR_BGR2RGB)  # matplotlib 표시용으로만 RGB 변환
    count = 0
    if circles is not None:
        count = int(circles.shape[1])
        for cx, cy, r in circles[0]:
            cv2.circle(result, (int(cx), int(cy)), int(r), (255, 50, 50), 2)
            cv2.circle(result, (int(cx), int(cy)), 3, (255, 50, 50), -1)
    return result, count


# ── 슬라이더 UI (폴더 1개) ────────────────────────────────────────────────────

def _tune(label: str, warped: np.ndarray) -> dict:
    """슬라이더 UI로 파라미터 조정 후 확정값 반환."""
    params = dict(INIT_HOUGH)
    confirmed: list[dict] = []

    result, count = _detect(warped, params)

    fig = plt.figure(figsize=(12, 10))
    fig.suptitle(label, fontsize=14, fontweight="bold")
    ax_img = fig.add_axes([0.05, 0.40, 0.9, 0.54])
    ax_img.set_title(f"Detected: {count}", fontsize=12)
    ax_img.axis("off")
    im = ax_img.imshow(result)

    sliders: dict[str, Slider] = {}
    for i, (key, lbl, vmin, vmax, vstep) in enumerate(_SLIDER_SPECS):
        ax_s = fig.add_axes([0.15, 0.32 - i * 0.04, 0.65, 0.025])
        sliders[key] = Slider(ax_s, lbl, vmin, vmax, valinit=params[key], valstep=vstep)

    ax_btn = fig.add_axes([0.78, 0.01, 0.18, 0.04])
    btn = Button(ax_btn, "Next ->")

    def _update(_):
        for k, sl in sliders.items():
            params[k] = sl.val
        res, cnt = _detect(warped, params)
        im.set_data(res)
        ax_img.set_title(f"Circles detected: {cnt}", fontsize=12)
        fig.canvas.draw_idle()

    def _confirm(_):
        for k, sl in sliders.items():
            params[k] = sl.val
        confirmed.append(dict(params))
        plt.close(fig)

    for sl in sliders.values():
        sl.on_changed(_update)
    btn.on_clicked(_confirm)

    plt.show()
    return confirmed[0] if confirmed else params


# ── 출력 ──────────────────────────────────────────────────────────────────────

def _format(
    roi_map: dict[tuple[int, str], list | None],
    hough_map: dict[tuple[int, str], dict],
) -> str:
    lines = [
        "# ── webcam_checker_node.py 에 붙여넣기 ──────────────────────────────",
        "BLOCK_ROI: dict[tuple[int, str], Optional[list[tuple[int, int]]]] = {",
    ]
    for (bt, color) in sorted(roi_map):
        tag = "2x2" if bt == 1 else "3x2"
        pts = roi_map[(bt, color)]
        lines.append(f"    ({bt}, {color!r}): {repr(pts)},  # {tag}")
    lines += ["}", ""]

    lines.append("HOUGH_PARAMS: dict[tuple[int, str], dict] = {")
    for (bt, color) in sorted(hough_map):
        tag = "2x2" if bt == 1 else "3x2"
        p = hough_map[(bt, color)]
        lines.append(
            f"    ({bt}, {color!r}): dict("
            f"clip_limit={p['clip_limit']:.1f}, "
            f"dp={p['dp']:.1f}, min_dist={int(p['min_dist'])}, "
            f"param1={int(p['param1'])}, param2={int(p['param2'])}, "
            f"min_r={int(p['min_r'])}, max_r={int(p['max_r'])}),  # {tag}"
        )
    lines.append("}")
    lines.append("# ─────────────────────────────────────────────────────────────────")
    return "\n".join(lines)


# ── 메인 ──────────────────────────────────────────────────────────────────────

def main() -> None:
    if not RESULTS_DIR.exists():
        print(f"[오류] 폴더 없음: {RESULTS_DIR}")
        print("  roi_check.py 를 먼저 실행하세요.")
        return

    roi_map: dict[tuple[int, str], list | None] = {}
    hough_map: dict[tuple[int, str], dict] = {}

    targets = []
    for btype_str, color in COMBINATIONS:
        folder = RESULTS_DIR / f"{btype_str}_{color}"
        if folder.exists():
            targets.append((folder, btype_str, color))
        else:
            print(f"[건너뜀] 폴더 없음: {folder.name}")

    if not targets:
        print("[오류] 처리할 폴더 없음.")
        return

    print(f"처리할 폴더 {len(targets)}개\n")

    for i, (folder, btype_str, color) in enumerate(targets, 1):
        bt = TYPE_MAP[btype_str]
        label = f"[{i}/{len(targets)}]  {btype_str} {color}"
        print(label)

        img = _load_snapshot(folder)
        if img is None:
            print(f"  [건너뜀] 스냅샷 없음")
            roi_map[(bt, color)] = None
            continue

        roi = _parse_roi(folder)
        if roi is None:
            print(f"  [경고] ROI 없음 — 전체 이미지 사용")
        roi_map[(bt, color)] = roi

        warped = _warp(img, roi)
        tuned = _tune(label, warped)
        hough_map[(bt, color)] = tuned

    print("\n\n" + "=" * 70)
    print(_format(roi_map, hough_map))
    print("=" * 70 + "\n")


if __name__ == "__main__":
    main()

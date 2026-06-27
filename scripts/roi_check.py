"""
ROI 4점 좌표 확인 스크립트.

사용법:
  python3 scripts/roi_check.py

절차:
  1. 로봇을 pick_pose로 이동시킨 상태에서 실행
  2. 이미지 창에서 블록 스터드 영역의 꼭짓점 4개를 시계 방향으로 클릭
     순서: 좌상 → 우상 → 우하 → 좌하
  3. 4점 클릭 완료 후 창을 닫으면 좌표 출력
  4. 원근 변환 결과 미리보기도 함께 표시
"""

import cv2
import matplotlib.pyplot as plt
import numpy as np

DEVICE = 2  # /dev/video2

_points: list[tuple[int, int]] = []


def capture_frame() -> np.ndarray | None:
    cap = cv2.VideoCapture(DEVICE)
    if not cap.isOpened():
        print(f"[오류] 카메라를 열 수 없습니다: /dev/video{DEVICE}")
        return None
    ok, frame = cap.read()
    cap.release()
    if not ok or frame is None:
        print("[오류] 프레임 캡처 실패")
        return None
    return cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)


def perspective_warp(image: np.ndarray, pts: list[tuple[int, int]]) -> np.ndarray:
    src = np.array(pts, dtype=np.float32)
    tl, tr, br, bl = src
    w = int(max(np.linalg.norm(tr - tl), np.linalg.norm(br - bl)))
    h = int(max(np.linalg.norm(bl - tl), np.linalg.norm(br - tr)))
    dst = np.array([[0, 0], [w-1, 0], [w-1, h-1], [0, h-1]], dtype=np.float32)
    M = cv2.getPerspectiveTransform(src, dst)
    return cv2.warpPerspective(image, M, (w, h))


def _on_click(event):
    if event.inaxes != _ax_main:
        return
    if len(_points) >= 4:
        return

    x, y = int(event.xdata), int(event.ydata)
    _points.append((x, y))

    labels = ["1 좌상", "2 우상", "3 우하", "4 좌하"]
    colors = ["red", "green", "blue", "orange"]
    idx = len(_points) - 1
    _ax_main.plot(x, y, "o", color=colors[idx], markersize=8)
    _ax_main.annotate(labels[idx], (x, y), textcoords="offset points",
                      xytext=(6, 6), color=colors[idx], fontsize=10, fontweight="bold")

    if len(_points) >= 2:
        xs = [p[0] for p in _points] + [_points[0][0]]
        ys = [p[1] for p in _points] + [_points[0][1]]
        if len(_ax_main.lines) > 1:
            _ax_main.lines[-1].remove()
        _ax_main.plot(xs[:len(_points)+1], ys[:len(_points)+1], "w--", linewidth=1)

    if len(_points) == 4:
        warped = perspective_warp(_frame, _points)
        _ax_preview.imshow(warped)
        _ax_preview.set_title("원근 변환 결과 미리보기")
        print("\n4점 선택 완료 — 창을 닫으면 좌표가 출력됩니다.")

    plt.draw()


def main():
    global _ax_main, _ax_preview, _frame

    _frame = capture_frame()
    if _frame is None:
        return

    print("이미지 창에서 꼭짓점 4개를 시계 방향으로 클릭하세요.")
    print("  순서: 좌상(1) → 우상(2) → 우하(3) → 좌하(4)")

    fig, (_ax_main, _ax_preview) = plt.subplots(1, 2, figsize=(14, 6))
    _ax_main.imshow(_frame)
    _ax_main.set_title("클릭으로 4점 선택 (좌상→우상→우하→좌하)")
    _ax_preview.set_title("원근 변환 결과 (4점 선택 후 표시)")
    _ax_preview.axis("off")

    fig.canvas.mpl_connect("button_press_event", _on_click)
    plt.tight_layout()
    plt.show()

    if len(_points) < 4:
        print("4점 미선택 — 종료")
        return

    print("\n─── 결과 ───────────────────────────────────")
    for i, (x, y) in enumerate(_points):
        labels = ["좌상", "우상", "우하", "좌하"]
        print(f"  {labels[i]}: ({x}, {y})")
    print()
    pts_str = ", ".join(f"({x}, {y})" for x, y in _points)
    print("webcam_checker_node.py 의 BLOCK_ROI 에 붙여넣기:")
    print(f"  1: [{pts_str}],  # 2x2")
    print(f"  2: [{pts_str}],  # 3x2 — 별도 측정 필요")
    print("────────────────────────────────────────────")


if __name__ == "__main__":
    main()

from __future__ import annotations

from typing import Iterable, Mapping

import cv2
import numpy as np

from .geometry import normalized_roi_to_pixels
from .models import SegmentationResult


def _project_normalized_points(points: np.ndarray, roi_pixels: np.ndarray) -> np.ndarray:
    source = np.asarray(
        [[0.0, 0.0], [1.0, 0.0], [1.0, 1.0], [0.0, 1.0]],
        dtype=np.float32,
    )
    homography = cv2.getPerspectiveTransform(source, roi_pixels.astype(np.float32))
    return cv2.perspectiveTransform(
        points.astype(np.float32).reshape(-1, 1, 2), homography
    ).reshape(-1, 2)


def _fallback_bgr(instance_id: int) -> tuple[int, int, int]:
    # Deterministic high-contrast colour without global random state.
    return (
        int(64 + (instance_id * 97) % 192),
        int(64 + (instance_id * 57) % 192),
        int(64 + (instance_id * 137) % 192),
    )


def draw_instance_overlay(
    image: np.ndarray,
    segmentation: SegmentationResult,
    *,
    alpha: float = 0.42,
    draw_boxes: bool = True,
    draw_labels: bool = True,
    draw_grid_size: int = 0,
) -> np.ndarray:
    output = image.copy()
    alpha = float(np.clip(alpha, 0.0, 1.0))

    for instance in segmentation.instances:
        if instance.mask.shape != image.shape[:2]:
            continue
        if instance.color:
            r, g, b = instance.rgb
            colour = (int(b), int(g), int(r))
        else:
            colour = _fallback_bgr(instance.instance_id)
        mask = instance.mask.astype(bool)
        if np.any(mask):
            coloured = np.empty_like(output)
            coloured[:] = colour
            output[mask] = cv2.addWeighted(
                output[mask], 1.0 - alpha, coloured[mask], alpha, 0.0
            )
            contours, _ = cv2.findContours(
                (mask.astype(np.uint8) * 255), cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE
            )
            cv2.drawContours(output, contours, -1, colour, 2)

        x0, y0, x1, y1 = [int(round(value)) for value in instance.bbox_xyxy]
        if draw_boxes:
            cv2.rectangle(output, (x0, y0), (max(x0, x1 - 1), max(y0, y1 - 1)), colour, 2)
        if draw_labels:
            label = f'#{instance.instance_id} {instance.class_name} {instance.score:.2f}'
            if instance.color:
                label += f'/{instance.color}'
            cv2.putText(
                output,
                label,
                (max(0, x0), max(14, y0 - 5)),
                cv2.FONT_HERSHEY_SIMPLEX,
                0.45,
                colour,
                1,
                cv2.LINE_AA,
            )
            centroid = tuple(int(round(value)) for value in instance.centroid_uv)
            cv2.circle(output, centroid, 3, colour, -1)

    if draw_grid_size > 0:
        height, width = output.shape[:2]
        x_edges = np.rint(np.linspace(0, width, draw_grid_size + 1)).astype(int)
        y_edges = np.rint(np.linspace(0, height, draw_grid_size + 1)).astype(int)
        for x in x_edges:
            cv2.line(output, (int(x), 0), (int(x), height - 1), (235, 235, 235), 1)
        for y in y_edges:
            cv2.line(output, (0, int(y)), (width - 1, int(y)), (235, 235, 235), 1)

    return output


def draw_workspace_overlay(
    image: np.ndarray,
    roi_normalized: Iterable[Iterable[float]],
    grid_size: int,
    *,
    mismatches: Mapping[tuple[int, int], str] | None = None,
    match_rate: float | None = None,
    passed: bool | None = None,
) -> np.ndarray:
    if grid_size < 1:
        raise ValueError('grid_size must be at least 1.')

    overlay = image.copy()
    height, width = overlay.shape[:2]
    roi_pixels = normalized_roi_to_pixels(roi_normalized, width, height)

    cv2.polylines(overlay, [np.rint(roi_pixels).astype(np.int32)], True, (255, 255, 255), 2)
    for index in range(1, grid_size):
        fraction = index / grid_size
        vertical = _project_normalized_points(
            np.asarray([[fraction, 0.0], [fraction, 1.0]]), roi_pixels
        )
        horizontal = _project_normalized_points(
            np.asarray([[0.0, fraction], [1.0, fraction]]), roi_pixels
        )
        cv2.line(
            overlay,
            tuple(np.rint(vertical[0]).astype(int)),
            tuple(np.rint(vertical[1]).astype(int)),
            (180, 180, 180),
            1,
        )
        cv2.line(
            overlay,
            tuple(np.rint(horizontal[0]).astype(int)),
            tuple(np.rint(horizontal[1]).astype(int)),
            (180, 180, 180),
            1,
        )

    if mismatches:
        for (row, col), reason in mismatches.items():
            center = _project_normalized_points(
                np.asarray([[(col + 0.5) / grid_size, (row + 0.5) / grid_size]]),
                roi_pixels,
            )[0]
            center_xy = tuple(np.rint(center).astype(int))
            cv2.circle(overlay, center_xy, 9, (0, 0, 255), 2)
            cv2.putText(
                overlay,
                reason,
                (center_xy[0] + 10, center_xy[1] - 6),
                cv2.FONT_HERSHEY_SIMPLEX,
                0.4,
                (0, 0, 255),
                1,
                cv2.LINE_AA,
            )

    if match_rate is not None:
        status = 'PASS' if passed else 'FAIL'
        cv2.putText(
            overlay,
            f'{status} {match_rate:.1f}%',
            (12, 28),
            cv2.FONT_HERSHEY_SIMPLEX,
            0.8,
            (0, 220, 0) if passed else (0, 0, 255),
            2,
            cv2.LINE_AA,
        )

    return overlay

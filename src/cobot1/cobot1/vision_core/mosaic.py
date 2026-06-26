from __future__ import annotations

from typing import Sequence

import cv2
import numpy as np

from .models import CellSample

DEFAULT_GRID_ROWS = 10
DEFAULT_GRID_COLS = 24
DEFAULT_CELL_ASPECT_WIDTH = 15.9
DEFAULT_CELL_ASPECT_HEIGHT = 19.0


def validate_bgr_image(image: np.ndarray) -> None:
    if image is None or image.size == 0:
        raise ValueError('Input image is empty.')
    if image.ndim != 3 or image.shape[2] != 3:
        raise ValueError('Input image must be a BGR image with three channels.')


def fit_image(
    image: np.ndarray,
    mode: str = 'center_crop',
    *,
    target_aspect: float | None = None,
    smart_crop_min_scale: float = 0.80,
) -> np.ndarray:
    """Fit an arbitrary image before row/column grid sampling."""

    validate_bgr_image(image)
    height, width = image.shape[:2]
    mode = mode.strip().lower()

    if mode == 'center_crop':
        side = min(height, width)
        y0 = (height - side) // 2
        x0 = (width - side) // 2
        return image[y0:y0 + side, x0:x0 + side].copy()

    if mode == 'smart_crop':
        aspect = _positive_aspect(target_aspect, width / float(height))
        return _smart_crop_to_aspect(
            image,
            aspect,
            float(np.clip(smart_crop_min_scale, 0.35, 1.0)),
        )

    raise ValueError(f'Unsupported fit mode: {mode}')


def _positive_aspect(target_aspect: float | None, fallback: float) -> float:
    if target_aspect is None or not np.isfinite(target_aspect) or target_aspect <= 0.0:
        return max(0.05, float(fallback))
    return float(target_aspect)


def _smart_crop_to_aspect(
    image: np.ndarray,
    target_aspect: float,
    min_scale: float,
) -> np.ndarray:
    height, width = image.shape[:2]
    saliency = _saliency_map(image)
    max_width, max_height = _window_for_aspect(width, height, target_aspect)
    crop_width = max(1, int(round(max_width * min_scale)))
    crop_height = max(1, int(round(crop_width / target_aspect)))
    if crop_height > max_height:
        crop_height = max_height
        crop_width = max(1, int(round(crop_height * target_aspect)))

    weight_sum = float(saliency.sum())
    if weight_sum <= 1e-6:
        center_x, center_y = width * 0.5, height * 0.5
    else:
        yy, xx = np.mgrid[0:height, 0:width]
        center_x = float((xx * saliency).sum() / weight_sum)
        center_y = float((yy * saliency).sum() / weight_sum)

    x0 = int(np.clip(round(center_x - crop_width * 0.5), 0, width - crop_width))
    y0 = int(np.clip(round(center_y - crop_height * 0.5), 0, height - crop_height))
    return image[y0:y0 + crop_height, x0:x0 + crop_width].copy()


def _window_for_aspect(width: int, height: int, target_aspect: float) -> tuple[int, int]:
    current_aspect = width / float(height)
    if current_aspect > target_aspect:
        return max(1, int(round(height * target_aspect))), height
    return width, max(1, int(round(width / target_aspect)))


def _saliency_map(image: np.ndarray) -> np.ndarray:
    hsv = cv2.cvtColor(image, cv2.COLOR_BGR2HSV)
    gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
    grad_x = cv2.Sobel(gray, cv2.CV_32F, 1, 0, ksize=3)
    grad_y = cv2.Sobel(gray, cv2.CV_32F, 0, 1, ksize=3)
    edge = cv2.magnitude(grad_x, grad_y)
    edge = edge / max(1.0, float(edge.max()))

    saturation = hsv[:, :, 1].astype(np.float32) / 255.0
    value = hsv[:, :, 2].astype(np.float32) / 255.0
    mid_value = 1.0 - np.abs(value - 0.56) * 1.55
    mid_value = np.clip(mid_value, 0.0, 1.0)

    height, width = image.shape[:2]
    yy, xx = np.mgrid[0:height, 0:width]
    center = np.exp(
        -(
            ((xx - width * 0.5) / max(1.0, width * 0.40)) ** 2
            + ((yy - height * 0.55) / max(1.0, height * 0.42)) ** 2
        )
    ).astype(np.float32)

    saliency = edge * 0.46 + saturation * 0.22 + mid_value * 0.14 + center * 0.18
    sky_like = (
        (hsv[:, :, 0] >= 85)
        & (hsv[:, :, 0] <= 112)
        & (hsv[:, :, 1] >= 45)
        & (hsv[:, :, 2] >= 130)
    )
    bright_neutral = (hsv[:, :, 1] <= 35) & (hsv[:, :, 2] >= 190)
    saliency[sky_like] *= 0.25
    saliency[bright_neutral] *= 0.35
    return cv2.GaussianBlur(saliency.astype(np.float32), (0, 0), 5.0)


def render_cells(
    cells: Sequence[CellSample],
    grid_rows: int,
    output_width: int,
    output_height: int,
    *,
    grid_cols: int | None = None,
    draw_grid: bool = True,
    grid_thickness: int = 1,
    blocks: Sequence[dict] | None = None,
) -> np.ndarray:
    grid_rows = int(grid_rows)
    grid_cols = grid_rows if grid_cols is None else int(grid_cols)
    if grid_rows < 1 or grid_cols < 1:
        raise ValueError('grid rows and columns must be at least 1.')
    if output_width < grid_cols or output_height < grid_rows:
        raise ValueError('Output dimensions must be at least as large as the grid.')

    image = np.zeros((output_height, output_width, 3), dtype=np.uint8)
    x_edges = np.rint(np.linspace(0, output_width, grid_cols + 1)).astype(int)
    y_edges = np.rint(np.linspace(0, output_height, grid_rows + 1)).astype(int)

    by_position = {(cell.row, cell.col): cell for cell in cells}
    for row in range(grid_rows):
        for col in range(grid_cols):
            cell = by_position.get((row, col))
            if cell is None:
                continue
            r, g, b = cell.rgb
            image[y_edges[row]:y_edges[row + 1], x_edges[col]:x_edges[col + 1]] = (b, g, r)

    if draw_grid and grid_thickness > 0:
        for x in x_edges[1:-1]:
            cv2.line(image, (int(x), 0), (int(x), output_height - 1), (32, 32, 32), grid_thickness)
        for y in y_edges[1:-1]:
            cv2.line(image, (0, int(y)), (output_width - 1, int(y)), (32, 32, 32), grid_thickness)

    for block in blocks or ():
        row = int(block['row'])
        col = int(block['col'])
        width = int(block.get('width', 1))
        height = int(block.get('height', 1))
        x0, x1 = int(x_edges[col]), int(x_edges[min(grid_cols, col + width)])
        y0, y1 = int(y_edges[row]), int(y_edges[min(grid_rows, row + height)])
        cv2.rectangle(image, (x0, y0), (max(x0, x1 - 1), max(y0, y1 - 1)), (245, 245, 245), 2)

    return image


def preview_size_for_cell_aspect(
    grid_rows: int,
    grid_cols: int,
    cell_aspect_width: float,
    cell_aspect_height: float,
    preferred_height: int,
) -> tuple[int, int]:
    grid_rows = int(grid_rows)
    grid_cols = int(grid_cols)
    if grid_rows < 1 or grid_cols < 1:
        raise ValueError('grid rows and columns must be at least 1.')
    if cell_aspect_width <= 0.0 or cell_aspect_height <= 0.0:
        raise ValueError('cell aspect values must be positive.')
    output_height = max(grid_rows, int(preferred_height))
    total_aspect = (grid_cols * cell_aspect_width) / (grid_rows * cell_aspect_height)
    output_width = max(grid_cols, int(round(output_height * total_aspect)))
    return output_width, output_height

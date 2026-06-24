from __future__ import annotations

from typing import Sequence

import cv2
import numpy as np

from .models import CellSample


def validate_bgr_image(image: np.ndarray) -> None:
    if image is None or image.size == 0:
        raise ValueError('Input image is empty.')
    if image.ndim != 3 or image.shape[2] != 3:
        raise ValueError('Input image must be a BGR image with three channels.')


def fit_image(
    image: np.ndarray,
    mode: str = 'center_crop',
    *,
    letterbox_bgr: tuple[int, int, int] = (0, 0, 0),
) -> np.ndarray:
    """Fit an arbitrary image to the square domain used for N x N sampling."""

    validate_bgr_image(image)
    height, width = image.shape[:2]
    mode = mode.strip().lower()

    if mode == 'center_crop':
        side = min(height, width)
        y0 = (height - side) // 2
        x0 = (width - side) // 2
        return image[y0:y0 + side, x0:x0 + side].copy()

    if mode == 'letterbox':
        side = max(height, width)
        canvas = np.empty((side, side, 3), dtype=image.dtype)
        canvas[:] = np.asarray(letterbox_bgr, dtype=image.dtype)
        y0 = (side - height) // 2
        x0 = (side - width) // 2
        canvas[y0:y0 + height, x0:x0 + width] = image
        return canvas

    if mode == 'stretch':
        side = max(height, width)
        return cv2.resize(image, (side, side), interpolation=cv2.INTER_LINEAR)

    raise ValueError(f'Unsupported fit mode: {mode}')


def render_cells(
    cells: Sequence[CellSample],
    grid_size: int,
    output_width: int,
    output_height: int,
    *,
    draw_grid: bool = True,
    grid_thickness: int = 1,
) -> np.ndarray:
    if grid_size < 1:
        raise ValueError('grid_size must be at least 1.')
    if output_width < grid_size or output_height < grid_size:
        raise ValueError('Output dimensions must be at least as large as grid_size.')

    image = np.zeros((output_height, output_width, 3), dtype=np.uint8)
    x_edges = np.rint(np.linspace(0, output_width, grid_size + 1)).astype(int)
    y_edges = np.rint(np.linspace(0, output_height, grid_size + 1)).astype(int)

    by_position = {(cell.row, cell.col): cell for cell in cells}
    for row in range(grid_size):
        for col in range(grid_size):
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

    return image

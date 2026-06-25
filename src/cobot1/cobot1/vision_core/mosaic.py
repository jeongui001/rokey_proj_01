from __future__ import annotations

from typing import Sequence

import cv2
import numpy as np

from .models import CellSample

DEFAULT_GRID_ROWS = 10
DEFAULT_GRID_COLS = 10
DEFAULT_CELL_ASPECT_WIDTH = 15.9
DEFAULT_CELL_ASPECT_HEIGHT = 38.0


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
    """Fit an arbitrary image before row/column grid sampling."""

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

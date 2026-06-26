from __future__ import annotations

import cv2
import numpy as np

from .models import CellSample
from .mosaic import validate_bgr_image
from .palette import Palette


BLOCK_COLORS = ('red', 'yellow', 'green', 'blue')
BACKGROUND = 'background'
UNKNOWN = 'unknown'
NON_BLOCK_COLORS = {BACKGROUND, UNKNOWN, ''}
UNKNOWN_RGB = (70, 70, 70)


def _rgb_for_name(
    palette: Palette,
    name: str,
    empty_palette_name: str = 'empty',
) -> tuple[int, int, int]:
    if name == BACKGROUND:
        return palette.empty_entry(empty_palette_name).rgb
    if name == UNKNOWN:
        return UNKNOWN_RGB
    return palette.get(name).rgb


def _palette_lab(palette: Palette, empty_palette_name: str) -> dict[str, np.ndarray]:
    rgb_values = [
        _rgb_for_name(palette, name, empty_palette_name)
        for name in (*BLOCK_COLORS, BACKGROUND)
    ]
    lab = cv2.cvtColor(np.asarray(rgb_values, dtype=np.uint8).reshape(-1, 1, 3), cv2.COLOR_RGB2LAB)
    return {
        name: lab[index, 0].astype(np.float32)
        for index, name in enumerate((*BLOCK_COLORS, BACKGROUND))
    }


def quantize_image_to_grid(
    image_bgr: np.ndarray,
    palette: Palette,
    grid_rows: int = 8,
    grid_cols: int = 16,
    config: dict | None = None,
) -> tuple[np.ndarray, list[CellSample]]:
    validate_bgr_image(image_bgr)
    grid_rows, grid_cols = int(grid_rows), int(grid_cols)
    if grid_rows < 1 or grid_cols < 1:
        raise ValueError('grid_rows and grid_cols must be at least 1.')

    cfg = dict(config or {})
    inner_ratio = float(np.clip(cfg.get('inner_cell_ratio', 0.70), 0.20, 1.0))
    background_distance = float(cfg.get('background_lab_distance', 34.0))
    unknown_distance = float(cfg.get('unknown_lab_distance', 72.0))
    empty_palette_name = str(cfg.get('empty_palette_name', 'empty'))

    height, width = image_bgr.shape[:2]
    x_edges = np.rint(np.linspace(0, width, grid_cols + 1)).astype(int)
    y_edges = np.rint(np.linspace(0, height, grid_rows + 1)).astype(int)
    lab_palette = _palette_lab(palette, empty_palette_name)
    grid = np.empty((grid_rows, grid_cols), dtype=object)

    for row in range(grid_rows):
        for col in range(grid_cols):
            x0, x1 = int(x_edges[col]), int(x_edges[col + 1])
            y0, y1 = int(y_edges[row]), int(y_edges[row + 1])
            pad_x = int(round((x1 - x0) * (1.0 - inner_ratio) / 2.0))
            pad_y = int(round((y1 - y0) * (1.0 - inner_ratio) / 2.0))
            sample = image_bgr[y0 + pad_y:max(y0 + pad_y + 1, y1 - pad_y),
                               x0 + pad_x:max(x0 + pad_x + 1, x1 - pad_x)]
            median_bgr = np.median(sample.reshape(-1, 3), axis=0).astype(np.uint8)
            hsv = cv2.cvtColor(median_bgr.reshape(1, 1, 3), cv2.COLOR_BGR2HSV)[0, 0]
            lab = cv2.cvtColor(median_bgr.reshape(1, 1, 3), cv2.COLOR_BGR2LAB)[0, 0].astype(np.float32)

            distances = {
                name: float(np.linalg.norm(lab - value))
                for name, value in lab_palette.items()
            }
            nearest_block = min(BLOCK_COLORS, key=lambda name: distances[name])
            if distances[BACKGROUND] <= background_distance or hsv[1] < 28 or hsv[2] < 35:
                grid[row, col] = BACKGROUND
            elif distances[nearest_block] > unknown_distance:
                grid[row, col] = UNKNOWN
            else:
                grid[row, col] = nearest_block

    smoothed = smooth_grid(grid)
    return smoothed, cells_from_grid(smoothed, palette, empty_palette_name)


def smooth_grid(grid: np.ndarray) -> np.ndarray:
    fixed = np.asarray(grid, dtype=object).copy()
    rows, cols = fixed.shape
    for row in range(rows):
        for col in range(1, cols - 1):
            left, middle, right = fixed[row, col - 1], fixed[row, col], fixed[row, col + 1]
            if left == right and left not in NON_BLOCK_COLORS and middle != left:
                fixed[row, col] = left
    return fixed


def merge_blocks(grid: np.ndarray) -> list[dict]:
    grid = np.asarray(grid, dtype=object)
    rows, cols = grid.shape
    blocks: list[dict] = []
    for row in range(rows):
        col = 0
        while col < cols:
            cell_colour = grid[row, col]
            if cell_colour in NON_BLOCK_COLORS:
                col += 1
                continue

            width, block_colour = _merged_width(grid[row, col:col + 3], 3)
            if width == 0:
                width, block_colour = _merged_width(grid[row, col:col + 2], 2)
            if width == 0:
                width = 1
                block_colour = cell_colour

            blocks.append({
                'row': int(row),
                'col': int(col),
                'width': int(width),
                'height': 1,
                'color': str(block_colour),
            })
            col += width
    return blocks


def _merged_width(values: np.ndarray, width: int) -> tuple[int, str]:
    if len(values) < width or BACKGROUND in values:
        return 0, ''
    valid = [str(value) for value in values if value not in NON_BLOCK_COLORS]
    if not valid:
        return 0, ''
    colour = max(set(valid), key=valid.count)
    if width == 3 and valid.count(colour) >= 2:
        return 3, colour
    if width == 2 and len(valid) == 2 and valid[0] == valid[1]:
        return 2, colour
    return 0, ''


def cells_from_grid(
    grid: np.ndarray,
    palette: Palette,
    empty_palette_name: str = 'empty',
) -> list[CellSample]:
    cells: list[CellSample] = []
    rows, cols = np.asarray(grid, dtype=object).shape
    for row in range(rows):
        for col in range(cols):
            colour = str(grid[row, col])
            cells.append(
                CellSample(
                    row=row,
                    col=col,
                    color=colour,
                    rgb=_rgb_for_name(palette, colour, empty_palette_name),
                    occupied=colour not in NON_BLOCK_COLORS,
                    confidence=1.0,
                    source_uv=((col + 0.5) / cols, (row + 0.5) / rows),
                )
            )
    return cells

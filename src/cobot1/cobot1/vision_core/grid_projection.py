from __future__ import annotations

import cv2
import numpy as np

from .models import CellSample
from .mosaic import validate_bgr_image


DEFAULT_BLOCK_COLORS = ('red', 'yellow', 'green', 'blue')
BACKGROUND = 'background'
UNKNOWN = 'unknown'
EMPTY = 'empty'
EXCLUDED_BLOCK_COLORS = {'white', 'black'}
NON_BLOCK_COLORS = {BACKGROUND, UNKNOWN, EMPTY, '', *EXCLUDED_BLOCK_COLORS}
RGB = tuple[int, int, int]


def _rgb_for_name(
    palette: dict[str, RGB],
    empty_rgb: RGB,
    name: str,
) -> RGB:
    if name in NON_BLOCK_COLORS:
        return empty_rgb
    return palette[name]


def _block_colors(palette: dict[str, RGB]) -> tuple[str, ...]:
    return tuple(name for name in DEFAULT_BLOCK_COLORS if name in palette)


def _palette_lab(
    palette: dict[str, RGB],
    empty_rgb: RGB,
    block_colors: tuple[str, ...],
) -> dict[str, np.ndarray]:
    rgb_values = [
        _rgb_for_name(palette, empty_rgb, name)
        for name in (*block_colors, BACKGROUND)
    ]
    lab = cv2.cvtColor(np.asarray(rgb_values, dtype=np.uint8).reshape(-1, 1, 3), cv2.COLOR_RGB2LAB)
    return {
        name: lab[index, 0].astype(np.float32)
        for index, name in enumerate((*block_colors, BACKGROUND))
    }


def _border_background_mask(image_bgr: np.ndarray, cfg: dict) -> np.ndarray | None:
    hsv = cv2.cvtColor(image_bgr, cv2.COLOR_BGR2HSV)
    border_fraction = float(np.clip(cfg.get('border_fraction', 0.04), 0.01, 0.25))
    border_distance = float(cfg.get('border_lab_distance', 28.0))
    max_border_saturation = int(cfg.get('border_background_max_saturation', 55))
    height, width = image_bgr.shape[:2]
    border = max(1, int(round(min(height, width) * border_fraction)))

    border_pixels = np.concatenate([
        image_bgr[:border, :, :].reshape(-1, 3),
        image_bgr[-border:, :, :].reshape(-1, 3),
        image_bgr[:, :border, :].reshape(-1, 3),
        image_bgr[:, -border:, :].reshape(-1, 3),
    ])
    border_hsv = cv2.cvtColor(border_pixels.reshape(-1, 1, 3), cv2.COLOR_BGR2HSV).reshape(-1, 3)
    if float(np.median(border_hsv[:, 1])) > max_border_saturation:
        return None

    border_bgr = np.median(border_pixels, axis=0).astype(np.uint8)
    border_lab = cv2.cvtColor(border_bgr.reshape(1, 1, 3), cv2.COLOR_BGR2LAB)[0, 0].astype(np.float32)
    lab = cv2.cvtColor(image_bgr, cv2.COLOR_BGR2LAB).astype(np.float32)
    neutral_background = (
        (hsv[:, :, 1] <= int(cfg.get('neutral_background_max_saturation', 35)))
        & (hsv[:, :, 2] >= int(cfg.get('neutral_background_min_value', 155)))
    )
    candidate = (
        (np.linalg.norm(lab - border_lab, axis=2) <= border_distance)
        | neutral_background
    ).astype(np.uint8)

    flood = np.zeros((height + 2, width + 2), dtype=np.uint8)
    connected = candidate.copy()
    for x in range(width):
        if connected[0, x] == 1:
            cv2.floodFill(connected, flood, (x, 0), 2)
        if connected[height - 1, x] == 1:
            cv2.floodFill(connected, flood, (x, height - 1), 2)
    for y in range(height):
        if connected[y, 0] == 1:
            cv2.floodFill(connected, flood, (0, y), 2)
        if connected[y, width - 1] == 1:
            cv2.floodFill(connected, flood, (width - 1, y), 2)
    return connected == 2


def _colour_masks(
    image_bgr: np.ndarray,
    block_colors: tuple[str, ...],
    cfg: dict,
) -> dict[str, np.ndarray]:
    hsv = cv2.cvtColor(image_bgr, cv2.COLOR_BGR2HSV)
    masks: dict[str, np.ndarray] = {}

    if 'red' in block_colors:
        red_s = int(cfg.get('red_hue_min_saturation', cfg.get('hue_min_saturation', 60)))
        red_v = int(cfg.get('red_hue_min_value', cfg.get('hue_min_value', 45)))
        red1 = cv2.inRange(hsv, (0, red_s, red_v), (int(cfg.get('red_hue_max', 10)), 255, 255))
        red2 = cv2.inRange(hsv, (int(cfg.get('red_hue_min_2', 170)), red_s, red_v), (179, 255, 255))
        masks['red'] = cv2.bitwise_or(red1, red2)
    if 'yellow' in block_colors:
        masks['yellow'] = cv2.inRange(
            hsv,
            (
                int(cfg.get('yellow_hue_min', 11)),
                int(cfg.get('yellow_hue_min_saturation', cfg.get('hue_min_saturation', 60))),
                int(cfg.get('yellow_hue_min_value', cfg.get('hue_min_value', 45))),
            ),
            (int(cfg.get('yellow_hue_max', 42)), 255, 255),
        )
    if 'green' in block_colors:
        masks['green'] = cv2.inRange(
            hsv,
            (
                int(cfg.get('green_hue_min', 43)),
                int(cfg.get('green_hue_min_saturation', cfg.get('hue_min_saturation', 60))),
                int(cfg.get('green_hue_min_value', cfg.get('hue_min_value', 45))),
            ),
            (int(cfg.get('green_hue_max', 87)), 255, 255),
        )
    if 'blue' in block_colors:
        hue_mask = cv2.inRange(
            hsv,
            (int(cfg.get('blue_hue_min', 88)), 0, 0),
            (int(cfg.get('blue_hue_max', 130)), 255, 255),
        )
        normal = cv2.inRange(
            hsv,
            (0, int(cfg.get('blue_hue_min_saturation', 45)), int(cfg.get('blue_hue_min_value', 110))),
            (179, 255, 255),
        )
        dark = cv2.inRange(
            hsv,
            (0, int(cfg.get('blue_dark_min_saturation', 100)), int(cfg.get('blue_dark_min_value', 70))),
            (179, 255, 255),
        )
        masks['blue'] = cv2.bitwise_and(hue_mask, cv2.bitwise_or(normal, dark))

    return {colour: _clean_colour_mask(mask, cfg) for colour, mask in masks.items()}


def _clean_colour_mask(mask: np.ndarray, cfg: dict) -> np.ndarray:
    kernel_size = int(cfg.get('color_mask_kernel_size', 3))
    if kernel_size > 1:
        kernel = np.ones((kernel_size, kernel_size), dtype=np.uint8)
        mask = cv2.morphologyEx(mask, cv2.MORPH_OPEN, kernel)
        mask = cv2.morphologyEx(mask, cv2.MORPH_CLOSE, kernel)

    min_area = int(cfg.get('color_mask_min_blob_area', 10))
    if min_area <= 1:
        return mask

    count, labels, stats, _ = cv2.connectedComponentsWithStats(mask, connectivity=8)
    cleaned = np.zeros_like(mask)
    for label in range(1, count):
        if int(stats[label, cv2.CC_STAT_AREA]) >= min_area:
            cleaned[labels == label] = 255
    return cleaned


def _vote_cell_colour(
    pixels_bgr: np.ndarray,
    block_colors: tuple[str, ...],
    lab_palette: dict[str, np.ndarray],
    cfg: dict,
    mask_scores: dict[str, float] | None = None,
) -> str:
    pixels = pixels_bgr.reshape(-1, 3)
    if pixels.size == 0:
        return BACKGROUND

    if mask_scores:
        mask_colour, mask_score = max(mask_scores.items(), key=lambda item: item[1])
        if mask_score >= float(cfg.get('component_mask_feature_fraction', 0.28)):
            return mask_colour

    median_bgr = np.median(pixels, axis=0).astype(np.uint8)
    median_lab = cv2.cvtColor(
        median_bgr.reshape(1, 1, 3),
        cv2.COLOR_BGR2LAB,
    )[0, 0].astype(np.float32)
    nearest = min(
        block_colors,
        key=lambda name: float(np.linalg.norm(median_lab - lab_palette[name])),
    )
    distance = float(np.linalg.norm(median_lab - lab_palette[nearest]))
    return nearest if distance <= float(cfg.get('unknown_lab_distance', 96.0)) else BACKGROUND


def quantize_image_to_grid(
    image_bgr: np.ndarray,
    palette: dict[str, RGB],
    empty_rgb: RGB,
    grid_rows: int = 10,
    grid_cols: int = 10,
    config: dict | None = None,
) -> tuple[np.ndarray, list[CellSample]]:
    validate_bgr_image(image_bgr)
    grid_rows, grid_cols = int(grid_rows), int(grid_cols)
    if grid_rows < 1 or grid_cols < 1:
        raise ValueError('grid_rows and grid_cols must be at least 1.')

    cfg = dict(config or {})
    inner_ratio = float(np.clip(cfg.get('inner_cell_ratio', 0.70), 0.20, 1.0))
    background_distance = float(cfg.get('background_lab_distance', 34.0))
    min_foreground_fraction = float(np.clip(cfg.get('min_foreground_fraction', 0.08), 0.0, 1.0))
    min_foreground_pixels = int(cfg.get('min_foreground_pixels', 8))

    height, width = image_bgr.shape[:2]
    x_edges = np.rint(np.linspace(0, width, grid_cols + 1)).astype(int)
    y_edges = np.rint(np.linspace(0, height, grid_rows + 1)).astype(int)
    block_colors = _block_colors(palette)
    if not block_colors:
        raise ValueError('palette must contain at least one block colour.')
    lab_palette = _palette_lab(palette, empty_rgb, block_colors)
    background_mask = _border_background_mask(image_bgr, cfg)
    colour_masks = _colour_masks(image_bgr, block_colors, cfg)
    grid = np.empty((grid_rows, grid_cols), dtype=object)

    for row in range(grid_rows):
        for col in range(grid_cols):
            x0, x1 = int(x_edges[col]), int(x_edges[col + 1])
            y0, y1 = int(y_edges[row]), int(y_edges[row + 1])
            pad_x = int(round((x1 - x0) * (1.0 - inner_ratio) / 2.0))
            pad_y = int(round((y1 - y0) * (1.0 - inner_ratio) / 2.0))
            ys = slice(y0 + pad_y, max(y0 + pad_y + 1, y1 - pad_y))
            xs = slice(x0 + pad_x, max(x0 + pad_x + 1, x1 - pad_x))
            sample = image_bgr[ys, xs]
            if background_mask is not None:
                foreground = sample[~background_mask[ys, xs]]
                min_pixels = max(min_foreground_pixels, int(round(sample.shape[0] * sample.shape[1] * min_foreground_fraction)))
                if foreground.shape[0] < min_pixels:
                    grid[row, col] = BACKGROUND
                    continue
                pixels = foreground
            else:
                pixels = sample.reshape(-1, 3)
            median_bgr = np.median(pixels.reshape(-1, 3), axis=0).astype(np.uint8)
            median_lab = cv2.cvtColor(median_bgr.reshape(1, 1, 3), cv2.COLOR_BGR2LAB)[0, 0].astype(np.float32)

            background_distance_for_cell = float(np.linalg.norm(median_lab - lab_palette[BACKGROUND]))
            if background_mask is None and background_distance_for_cell <= background_distance:
                grid[row, col] = BACKGROUND
                continue

            mask_area = max(1, sample.shape[0] * sample.shape[1])
            mask_scores = {
                colour_name: float(np.count_nonzero(mask[ys, xs])) / float(mask_area)
                for colour_name, mask in colour_masks.items()
            }
            grid[row, col] = _vote_cell_colour(
                pixels,
                block_colors,
                lab_palette,
                cfg,
                mask_scores,
            )

    cleaned = clean_grid_for_bricks(smooth_grid(grid), cfg)
    return cleaned, cells_from_grid(cleaned, palette, empty_rgb)


def smooth_grid(grid: np.ndarray) -> np.ndarray:
    fixed = np.asarray(grid, dtype=object).copy()
    rows, cols = fixed.shape
    for row in range(rows):
        for col in range(1, cols - 1):
            left, middle, right = fixed[row, col - 1], fixed[row, col], fixed[row, col + 1]
            if left == right and left not in NON_BLOCK_COLORS and middle in NON_BLOCK_COLORS:
                fixed[row, col] = left
    return fixed


def clean_grid_for_bricks(grid: np.ndarray, cfg: dict) -> np.ndarray:
    """Remove obvious one-cell artifacts while keeping 2/3-wide brick runs."""

    if not bool(cfg.get('brick_cleanup', True)):
        return np.asarray(grid, dtype=object).copy()

    fixed = np.asarray(grid, dtype=object).copy()
    if bool(cfg.get('fill_single_cell_gaps', True)):
        fixed = _fill_short_horizontal_gaps(fixed, int(cfg.get('max_horizontal_gap_cells', 2)))
    fixed = _fill_small_background_holes(
        fixed,
        int(cfg.get('max_background_hole_cells', 3)),
        int(cfg.get('min_hole_neighbour_cells', 3)),
    )
    fixed = _remove_small_colour_islands(
        fixed,
        int(cfg.get('max_colour_island_cells', 1)),
        int(cfg.get('min_island_neighbour_cells', 3)),
    )
    if bool(cfg.get('fix_single_cell_runs', True)):
        fixed = _remove_single_cell_runs(fixed)
    return fixed


def _fill_short_horizontal_gaps(grid: np.ndarray, max_gap: int) -> np.ndarray:
    fixed = np.asarray(grid, dtype=object).copy()
    rows, cols = fixed.shape
    for row in range(rows):
        col = 0
        while col < cols:
            if fixed[row, col] not in NON_BLOCK_COLORS:
                col += 1
                continue

            start = col
            while col < cols and fixed[row, col] in NON_BLOCK_COLORS:
                col += 1
            if start == 0 or col == cols or col - start > max_gap:
                continue

            left = fixed[row, start - 1]
            right = fixed[row, col]
            if left == right and left not in NON_BLOCK_COLORS:
                fixed[row, start:col] = left
    return fixed


def _fill_small_background_holes(
    grid: np.ndarray,
    max_cells: int,
    min_neighbours: int,
) -> np.ndarray:
    fixed = np.asarray(grid, dtype=object).copy()
    rows, cols = fixed.shape
    visited = np.zeros((rows, cols), dtype=bool)

    for row in range(rows):
        for col in range(cols):
            if visited[row, col] or fixed[row, col] not in NON_BLOCK_COLORS:
                continue
            component, touches_border = _component(fixed, row, col, visited, NON_BLOCK_COLORS)
            if touches_border or len(component) > max_cells:
                continue
            fill_colour = _dominant_neighbour_colour(fixed, component, min_neighbours)
            if fill_colour:
                for r, c in component:
                    fixed[r, c] = fill_colour
    return fixed


def _remove_small_colour_islands(
    grid: np.ndarray,
    max_cells: int,
    min_neighbours: int,
) -> np.ndarray:
    fixed = np.asarray(grid, dtype=object).copy()
    rows, cols = fixed.shape
    visited = np.zeros((rows, cols), dtype=bool)

    for row in range(rows):
        for col in range(cols):
            colour = fixed[row, col]
            if visited[row, col] or colour in NON_BLOCK_COLORS:
                continue
            component, _ = _component(fixed, row, col, visited, {colour})
            if len(component) > max_cells:
                continue
            replacement = _dominant_neighbour_colour(
                fixed,
                component,
                min_neighbours,
                ignored_colours={colour},
            )
            for r, c in component:
                fixed[r, c] = replacement or BACKGROUND
    return fixed


def _component(
    grid: np.ndarray,
    row: int,
    col: int,
    visited: np.ndarray,
    colours: set,
) -> tuple[list[tuple[int, int]], bool]:
    rows, cols = grid.shape
    stack = [(row, col)]
    visited[row, col] = True
    cells: list[tuple[int, int]] = []
    touches_border = False

    while stack:
        r, c = stack.pop()
        cells.append((r, c))
        touches_border = touches_border or r in (0, rows - 1) or c in (0, cols - 1)
        for nr, nc in _neighbour4(r, c, rows, cols):
            if not visited[nr, nc] and grid[nr, nc] in colours:
                visited[nr, nc] = True
                stack.append((nr, nc))
    return cells, touches_border


def _dominant_neighbour_colour(
    grid: np.ndarray,
    cells: list[tuple[int, int]],
    min_neighbours: int,
    ignored_colours: set | None = None,
) -> str:
    rows, cols = grid.shape
    inside = set(cells)
    ignored = ignored_colours or set()
    counts: dict[str, int] = {}

    for row, col in cells:
        for nr in range(max(0, row - 1), min(rows, row + 2)):
            for nc in range(max(0, col - 1), min(cols, col + 2)):
                if (nr, nc) in inside or (nr == row and nc == col):
                    continue
                colour = str(grid[nr, nc])
                if colour in NON_BLOCK_COLORS or colour in ignored:
                    continue
                counts[colour] = counts.get(colour, 0) + 1

    if not counts:
        return ''
    colour, count = max(counts.items(), key=lambda item: item[1])
    return colour if count >= min_neighbours else ''


def _neighbour4(row: int, col: int, rows: int, cols: int):
    for nr, nc in ((row - 1, col), (row + 1, col), (row, col - 1), (row, col + 1)):
        if 0 <= nr < rows and 0 <= nc < cols:
            yield nr, nc


def _remove_single_cell_runs(grid: np.ndarray) -> np.ndarray:
    fixed = np.asarray(grid, dtype=object).copy()
    for _ in range(3):
        original = fixed.copy()
        changed = False
        for row in range(fixed.shape[0]):
            runs = _row_runs(original[row])
            for index, (start, end, colour) in enumerate(runs):
                if colour in NON_BLOCK_COLORS or end - start > 1:
                    continue
                replacement = _neighbour_run_colour(runs, index)
                fixed[row, start] = replacement
                changed = changed or replacement != colour
        if not changed:
            break
    return fixed


def _row_runs(row: np.ndarray) -> list[tuple[int, int, str]]:
    runs: list[tuple[int, int, str]] = []
    col = 0
    while col < len(row):
        colour = str(row[col])
        start = col
        while col < len(row) and str(row[col]) == colour:
            col += 1
        runs.append((start, col, colour))
    return runs


def _neighbour_run_colour(
    runs: list[tuple[int, int, str]],
    index: int,
) -> str:
    choices = []
    for neighbour_index in (index - 1, index + 1):
        if 0 <= neighbour_index < len(runs):
            start, end, colour = runs[neighbour_index]
            if colour not in NON_BLOCK_COLORS:
                choices.append((end - start, colour))
    if not choices:
        return BACKGROUND
    return max(choices)[1]


def merge_blocks(grid: np.ndarray) -> list[dict]:
    grid = np.asarray(grid, dtype=object)
    rows, cols = grid.shape
    blocks: list[dict] = []
    for row in range(rows):
        col = 0
        while col < cols:
            colour = grid[row, col]
            if colour in NON_BLOCK_COLORS:
                col += 1
                continue

            start = col
            while col < cols and grid[row, col] == colour:
                col += 1

            offset = 0
            for width in _brick_widths(col - start):
                blocks.append({
                    'row': int(row),
                    'col': int(start + offset),
                    'width': int(width),
                    'height': 1,
                    'color': str(colour),
                })
                offset += width
    return blocks


def _brick_widths(run_length: int) -> list[int]:
    if run_length < 2:
        return []
    if run_length % 3 == 0:
        return [3] * (run_length // 3)
    if run_length % 3 == 1:
        return [2, 2] + [3] * ((run_length - 4) // 3)
    return [2] + [3] * ((run_length - 2) // 3)


def cells_from_grid(
    grid: np.ndarray,
    palette: dict[str, RGB],
    empty_rgb: RGB,
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
                    rgb=_rgb_for_name(palette, empty_rgb, colour),
                    occupied=colour not in NON_BLOCK_COLORS,
                    confidence=1.0,
                    source_uv=((col + 0.5) / cols, (row + 0.5) / rows),
                )
            )
    return cells

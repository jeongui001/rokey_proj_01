from __future__ import annotations

import cv2
import numpy as np

from .models import CellSample


def draw_grid_lines(image: np.ndarray, grid_rows: int, grid_cols: int, colour=(235, 235, 235)) -> None:
    height, width = image.shape[:2]
    x_edges = np.rint(np.linspace(0, width, int(grid_cols) + 1)).astype(int)
    y_edges = np.rint(np.linspace(0, height, int(grid_rows) + 1)).astype(int)
    for x in x_edges:
        cv2.line(image, (int(x), 0), (int(x), height - 1), colour, 1)
    for y in y_edges:
        cv2.line(image, (0, int(y)), (width - 1, int(y)), colour, 1)


def draw_grid_overlay(
    image: np.ndarray,
    cells: list[CellSample],
    blocks: list[dict],
    grid_rows: int,
    grid_cols: int,
    *,
    alpha: float = 0.35,
) -> np.ndarray:
    output = image.copy()
    height, width = output.shape[:2]
    x_edges = np.rint(np.linspace(0, width, grid_cols + 1)).astype(int)
    y_edges = np.rint(np.linspace(0, height, grid_rows + 1)).astype(int)
    alpha = float(np.clip(alpha, 0.0, 1.0))

    for cell in cells:
        if not cell.occupied:
            continue
        x0, x1 = int(x_edges[cell.col]), int(x_edges[cell.col + 1])
        y0, y1 = int(y_edges[cell.row]), int(y_edges[cell.row + 1])
        r, g, b = cell.rgb
        colour = np.asarray((b, g, r), dtype=np.float32)
        patch = output[y0:y1, x0:x1].astype(np.float32)
        output[y0:y1, x0:x1] = np.clip(
            patch * (1.0 - alpha) + colour * alpha,
            0,
            255,
        ).astype(np.uint8)

    draw_grid_lines(output, grid_rows, grid_cols)
    for block in blocks:
        row = int(block['row'])
        col = int(block['col'])
        block_width = int(block.get('width', 1))
        x0, x1 = int(x_edges[col]), int(x_edges[min(grid_cols, col + block_width)])
        y0, y1 = int(y_edges[row]), int(y_edges[row + 1])
        cv2.rectangle(output, (x0, y0), (max(x0, x1 - 1), max(y0, y1 - 1)), (255, 255, 255), 2)
    return output

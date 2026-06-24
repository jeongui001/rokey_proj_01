from __future__ import annotations

from typing import Iterable, Sequence

import cv2
import numpy as np

from .geometry import normalized_roi_to_pixels
from .models import CellMismatch, CellSample, ComparisonResult
from .mosaic import render_cells


def rectify_image(
    image: np.ndarray,
    camera_matrix: Sequence[float] | np.ndarray,
    distortion: Sequence[float] | np.ndarray,
) -> np.ndarray:
    matrix = np.asarray(camera_matrix, dtype=np.float64).reshape(3, 3)
    coefficients = np.asarray(distortion, dtype=np.float64)
    if matrix[0, 0] <= 0.0 or matrix[1, 1] <= 0.0:
        raise ValueError('Camera matrix is not calibrated.')
    if coefficients.size == 0 or not np.any(np.abs(coefficients) > 1e-12):
        return image.copy()
    return cv2.undistort(image, matrix, coefficients, None, matrix)


def warp_workspace(
    image: np.ndarray,
    roi_normalized: Iterable[Iterable[float]],
    output_size: int,
) -> np.ndarray:
    if output_size < 1:
        raise ValueError('output_size must be positive.')
    height, width = image.shape[:2]
    source = normalized_roi_to_pixels(roi_normalized, width, height)
    destination = np.asarray(
        [
            [0.0, 0.0],
            [output_size - 1.0, 0.0],
            [output_size - 1.0, output_size - 1.0],
            [0.0, output_size - 1.0],
        ],
        dtype=np.float32,
    )
    homography = cv2.getPerspectiveTransform(source, destination)
    return cv2.warpPerspective(image, homography, (output_size, output_size))


def compare_cells(
    expected_cells: Sequence[CellSample],
    observed_cells: Sequence[CellSample],
    *,
    min_observation_confidence: float = 0.45,
    min_expected_confidence: float = 0.0,
    min_alignment_coverage: float = 0.18,
    max_centroid_offset_ratio: float = 0.90,
    max_overlapping_instances: int = 1,
) -> ComparisonResult:
    expected_by_position = {(cell.row, cell.col): cell for cell in expected_cells}
    observed_by_position = {(cell.row, cell.col): cell for cell in observed_cells}
    positions = sorted(set(expected_by_position) | set(observed_by_position))

    mismatches: list[CellMismatch] = []
    matched = 0
    for position in positions:
        expected = expected_by_position.get(position)
        observed = observed_by_position.get(position)
        if expected is None or observed is None:
            raise ValueError(f'Models have inconsistent grid positions at {position}.')

        reason = ''
        details = ''
        if expected.confidence < min_expected_confidence:
            reason = 'UNCERTAIN'
            details = (
                f'expected confidence {expected.confidence:.3f} '
                f'< {min_expected_confidence:.3f}'
            )
        elif observed.confidence < min_observation_confidence:
            reason = 'UNCERTAIN'
            details = (
                f'observation confidence {observed.confidence:.3f} '
                f'< {min_observation_confidence:.3f}'
            )
        elif expected.occupied and not observed.occupied:
            reason = 'MISSING'
            details = f'expected {expected.color}, observed empty'
        elif not expected.occupied and observed.occupied:
            reason = 'EXTRA'
            details = f'expected empty, observed {observed.color}'
        elif expected.color != observed.color:
            reason = 'WRONG_COLOR'
            details = f'expected {expected.color}, observed {observed.color}'
        elif observed.occupied and observed.overlapping_instances > max_overlapping_instances:
            reason = 'INSTANCE_CONFLICT'
            details = (
                f'{observed.overlapping_instances} masks overlap cell; '
                f'maximum allowed is {max_overlapping_instances}'
            )
        elif observed.occupied and observed.mask_coverage < min_alignment_coverage:
            reason = 'MISALIGNED'
            details = (
                f'mask coverage {observed.mask_coverage:.3f} '
                f'< {min_alignment_coverage:.3f}'
            )
        elif (
            observed.occupied
            and np.isfinite(observed.centroid_offset_ratio)
            and observed.centroid_offset_ratio > max_centroid_offset_ratio
        ):
            reason = 'MISALIGNED'
            details = (
                f'centroid offset ratio {observed.centroid_offset_ratio:.3f} '
                f'> {max_centroid_offset_ratio:.3f}'
            )
        else:
            matched += 1

        if reason:
            mismatches.append(
                CellMismatch(
                    row=position[0],
                    col=position[1],
                    reason=reason,
                    expected=expected,
                    observed=observed,
                    details=details,
                )
            )

    total = len(positions)
    match_rate = 100.0 * matched / total if total else 0.0
    return ComparisonResult(
        match_rate=match_rate,
        matched_cells=matched,
        total_cells=total,
        mismatches=mismatches,
    )


def render_observed_mosaic(
    cells: Sequence[CellSample],
    grid_size: int,
    pixels_per_cell: int,
    *,
    grid_thickness: int = 1,
) -> np.ndarray:
    size = max(grid_size, grid_size * pixels_per_cell)
    return render_cells(
        cells,
        grid_size,
        size,
        size,
        draw_grid=True,
        grid_thickness=grid_thickness,
    )

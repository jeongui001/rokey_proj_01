from __future__ import annotations

import math
from typing import Mapping

import cv2
import numpy as np

from .models import CellSample, GridProjectionResult, InstancePrediction, SegmentationResult
from .mosaic import validate_bgr_image
from .palette import Palette, PaletteEntry


def _normalised_weights(raw: Mapping[str, float]) -> dict[str, float]:
    weights = {
        'instance': max(0.0, float(raw.get('instance', 0.45))),
        'coverage': max(0.0, float(raw.get('coverage', 0.35))),
        'color': max(0.0, float(raw.get('color', 0.20))),
    }
    total = sum(weights.values())
    if total <= 0.0:
        return {'instance': 1.0 / 3.0, 'coverage': 1.0 / 3.0, 'color': 1.0 / 3.0}
    return {key: value / total for key, value in weights.items()}


def _eroded_mask(mask: np.ndarray, erosion_px: int) -> np.ndarray:
    if erosion_px <= 0:
        return mask
    size = 2 * erosion_px + 1
    kernel = cv2.getStructuringElement(cv2.MORPH_ELLIPSE, (size, size))
    eroded = cv2.erode(mask.astype(np.uint8), kernel, iterations=1).astype(bool)
    return eroded if np.any(eroded) else mask


def _class_palette_entry(
    instance: InstancePrediction,
    palette: Palette,
    class_to_palette: Mapping[str, str],
) -> PaletteEntry | None:
    class_key = instance.class_name.strip().lower()
    mapped_name = class_to_palette.get(class_key)
    if mapped_name and palette.has(mapped_name):
        return palette.get(mapped_name)
    # A model trained directly with palette class names needs no explicit map.
    palette_names = {name.lower(): name for name in palette.names(include_unoccupied=False)}
    direct_name = palette_names.get(class_key)
    return palette.get(direct_name) if direct_name else None


def _resolve_color(
    instance: InstancePrediction,
    pixels_bgr: np.ndarray,
    palette: Palette,
    config: dict,
) -> tuple[PaletteEntry, float]:
    mode = str(config.get('color_source', 'class_then_pixels')).strip().lower()
    mapping = {
        str(key).strip().lower(): str(value).strip()
        for key, value in dict(config.get('class_to_palette', {})).items()
    }
    class_entry = _class_palette_entry(instance, palette, mapping)
    if mode == 'class':
        if class_entry is None:
            raise ValueError(
                f'No class_to_palette mapping for segmentation class "{instance.class_name}".'
            )
        return class_entry, 1.0
    if mode == 'class_then_pixels' and class_entry is not None:
        return class_entry, 1.0
    if mode not in {'pixels', 'class_then_pixels'}:
        raise ValueError(f'Unsupported grid_projection.color_source: {mode}')
    entry, confidence, _ = palette.classify_masked_pixels(
        pixels_bgr, include_unoccupied=False
    )
    return entry, confidence


def assign_instance_colors(
    image_bgr: np.ndarray,
    segmentation: SegmentationResult,
    palette: Palette,
    config: dict,
) -> None:
    erosion_px = int(config.get('mask_erosion_px', 1))
    min_pixels = int(config.get('min_color_pixels', 12))
    for instance in segmentation.instances:
        mask = _eroded_mask(instance.mask, erosion_px)
        pixels = image_bgr[mask]
        if pixels.shape[0] < min_pixels:
            pixels = image_bgr[instance.mask]
        if pixels.shape[0] == 0:
            continue
        entry, confidence = _resolve_color(instance, pixels, palette, config)
        instance.color = entry.name
        instance.rgb = entry.rgb
        instance.color_confidence = float(confidence)


def project_instances_to_grid(
    image_bgr: np.ndarray,
    segmentation: SegmentationResult,
    grid_size: int,
    palette: Palette,
    config: dict,
) -> GridProjectionResult:
    """Assign dominant instance masks to N x N cells and classify masked colours."""

    validate_bgr_image(image_bgr)
    if grid_size < 1:
        raise ValueError('grid_size must be at least 1.')
    height, width = image_bgr.shape[:2]
    if (segmentation.image_width, segmentation.image_height) != (width, height):
        raise ValueError(
            'Segmentation image size does not match the image used for grid projection: '
            f'{segmentation.image_width}x{segmentation.image_height} vs {width}x{height}.'
        )
    for instance in segmentation.instances:
        if instance.mask.shape != (height, width):
            raise ValueError(
                f'Instance {instance.instance_id} mask shape {instance.mask.shape} '
                f'does not match image shape {(height, width)}.'
            )

    assign_instance_colors(image_bgr, segmentation, palette, config)
    empty_entry = palette.empty_entry(str(config.get('empty_palette_name', 'empty')))
    min_cell_coverage = float(config.get('min_cell_coverage', 0.12))
    conflict_coverage = float(config.get('conflict_cell_coverage', 0.08))
    min_instance_confidence = float(config.get('min_instance_confidence', 0.0))
    coverage_saturation = max(1e-6, float(config.get('coverage_saturation', 0.60)))
    erosion_px = int(config.get('mask_erosion_px', 1))
    min_color_pixels = int(config.get('min_color_pixels', 12))
    weights = _normalised_weights(dict(config.get('confidence_weights', {})))

    x_edges = np.rint(np.linspace(0, width, grid_size + 1)).astype(int)
    y_edges = np.rint(np.linspace(0, height, grid_size + 1)).astype(int)
    cells: list[CellSample] = []

    eligible = [
        instance for instance in segmentation.instances
        if instance.score >= min_instance_confidence and instance.area > 0
    ]

    for row in range(grid_size):
        for col in range(grid_size):
            x0, x1 = int(x_edges[col]), int(x_edges[col + 1])
            y0, y1 = int(y_edges[row]), int(y_edges[row + 1])
            cell_width = max(1, x1 - x0)
            cell_height = max(1, y1 - y0)
            cell_area = float(cell_width * cell_height)
            centre = ((x0 + x1 - 1) / 2.0, (y0 + y1 - 1) / 2.0)

            overlaps: list[tuple[float, float, InstancePrediction, int]] = []
            for instance in eligible:
                overlap_pixels = int(np.count_nonzero(instance.mask[y0:y1, x0:x1]))
                if overlap_pixels <= 0:
                    continue
                coverage = overlap_pixels / cell_area
                overlaps.append((coverage, instance.score, instance, overlap_pixels))
            overlaps.sort(key=lambda item: (item[0], item[1]), reverse=True)
            overlapping_instances = sum(1 for item in overlaps if item[0] >= conflict_coverage)

            if not overlaps or overlaps[0][0] < min_cell_coverage:
                max_coverage = overlaps[0][0] if overlaps else 0.0
                empty_confidence = float(
                    np.clip(1.0 - max_coverage / max(min_cell_coverage, 1e-6), 0.0, 1.0)
                )
                cells.append(
                    CellSample(
                        row=row,
                        col=col,
                        color=empty_entry.name,
                        rgb=empty_entry.rgb,
                        occupied=False,
                        confidence=empty_confidence,
                        mask_coverage=max_coverage,
                        overlapping_instances=overlapping_instances,
                        source_uv=centre,
                    )
                )
                continue

            coverage, _, instance, _ = overlaps[0]
            local_mask = instance.mask[y0:y1, x0:x1]
            eroded_local = _eroded_mask(local_mask, erosion_px)
            local_image = image_bgr[y0:y1, x0:x1]
            pixels = local_image[eroded_local]
            if pixels.shape[0] < min_color_pixels:
                pixels = local_image[local_mask]
            if pixels.shape[0] < min_color_pixels:
                pixels = image_bgr[instance.mask]
            entry, color_confidence = _resolve_color(instance, pixels, palette, config)

            coverage_confidence = float(np.clip(coverage / coverage_saturation, 0.0, 1.0))
            confidence = float(
                weights['instance'] * instance.score
                + weights['coverage'] * coverage_confidence
                + weights['color'] * color_confidence
            )
            centroid_u, centroid_v = instance.centroid_uv
            half_width = max(0.5, cell_width / 2.0)
            half_height = max(0.5, cell_height / 2.0)
            centroid_offset = max(
                abs(centroid_u - centre[0]) / half_width,
                abs(centroid_v - centre[1]) / half_height,
            )
            cells.append(
                CellSample(
                    row=row,
                    col=col,
                    color=entry.name,
                    rgb=entry.rgb,
                    occupied=entry.occupied,
                    confidence=confidence,
                    instance_id=instance.instance_id,
                    class_id=instance.class_id,
                    class_name=instance.class_name,
                    instance_confidence=instance.score,
                    mask_coverage=float(coverage),
                    overlapping_instances=overlapping_instances,
                    source_uv=centre,
                    instance_centroid_uv=(centroid_u, centroid_v),
                    centroid_offset_ratio=float(centroid_offset),
                )
            )

    return GridProjectionResult(cells=cells, segmentation=segmentation)

from __future__ import annotations

from dataclasses import dataclass, field
from typing import Optional, Tuple

import numpy as np


@dataclass
class InstancePrediction:
    """ROS-independent instance mask and metadata."""

    instance_id: int
    class_id: int
    class_name: str
    score: float
    mask: np.ndarray
    bbox_xyxy: Tuple[float, float, float, float]
    centroid_uv: Tuple[float, float]
    color: str = ''
    rgb: Tuple[int, int, int] = (0, 0, 0)
    color_confidence: float = 0.0

    def __post_init__(self) -> None:
        mask = np.asarray(self.mask)
        if mask.ndim != 2:
            raise ValueError(f'Instance mask must be 2-D, received shape {mask.shape}.')
        self.mask = mask.astype(bool, copy=False)
        self.score = float(np.clip(self.score, 0.0, 1.0))

    @property
    def area(self) -> int:
        return int(np.count_nonzero(self.mask))


@dataclass
class SegmentationResult:
    backend: str
    model_name: str
    image_width: int
    image_height: int
    instances: list[InstancePrediction] = field(default_factory=list)


@dataclass(frozen=True)
class CellSample:
    """One logical grid cell after assigning instance masks to an N x N grid."""

    row: int
    col: int
    color: str
    rgb: Tuple[int, int, int]
    occupied: bool
    confidence: float
    instance_id: int = -1
    class_id: int = -1
    class_name: str = ''
    instance_confidence: float = 0.0
    mask_coverage: float = 0.0
    overlapping_instances: int = 0
    source_uv: Optional[Tuple[float, float]] = None
    instance_centroid_uv: Optional[Tuple[float, float]] = None
    centroid_offset_ratio: float = float('nan')
    camera_uv: Optional[Tuple[float, float]] = None


@dataclass(frozen=True)
class CellMismatch:
    row: int
    col: int
    reason: str
    expected: CellSample
    observed: CellSample
    details: str = ''


@dataclass
class ComparisonResult:
    match_rate: float
    matched_cells: int
    total_cells: int
    mismatches: list[CellMismatch] = field(default_factory=list)


@dataclass
class GridProjectionResult:
    cells: list[CellSample]
    segmentation: SegmentationResult

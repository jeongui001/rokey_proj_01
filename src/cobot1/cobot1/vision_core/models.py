from __future__ import annotations

from dataclasses import dataclass
from typing import Optional, Tuple


@dataclass(frozen=True)
class CellSample:
    """One logical colour sample in the row/column mosaic grid."""

    row: int
    col: int
    color: str
    rgb: Tuple[int, int, int]
    occupied: bool
    confidence: float
    source_uv: Optional[Tuple[float, float]] = None

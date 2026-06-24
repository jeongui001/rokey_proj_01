from __future__ import annotations

from abc import ABC, abstractmethod
from typing import Iterable

import cv2
import numpy as np

from ..models import InstancePrediction, SegmentationResult


class InstanceSegmenter(ABC):
    backend_name: str = 'unknown'
    model_name: str = ''

    @abstractmethod
    def infer(self, image_bgr: np.ndarray) -> SegmentationResult:
        raise NotImplementedError

    def warmup(self) -> None:
        """Optional backend warm-up."""


def mask_geometry(mask: np.ndarray) -> tuple[tuple[float, float, float, float], tuple[float, float]]:
    binary = np.asarray(mask, dtype=np.uint8)
    ys, xs = np.nonzero(binary)
    if xs.size == 0:
        raise ValueError('Cannot derive geometry from an empty mask.')
    x0 = float(xs.min())
    y0 = float(ys.min())
    x1 = float(xs.max() + 1)
    y1 = float(ys.max() + 1)
    moments = cv2.moments(binary, binaryImage=True)
    if abs(moments['m00']) > 1e-9:
        centroid = (float(moments['m10'] / moments['m00']), float(moments['m01'] / moments['m00']))
    else:
        centroid = (float(xs.mean()), float(ys.mean()))
    return (x0, y0, x1, y1), centroid


def make_instance(
    instance_id: int,
    class_id: int,
    class_name: str,
    score: float,
    mask: np.ndarray,
    *,
    bbox_xyxy: Iterable[float] | None = None,
) -> InstancePrediction:
    binary = np.asarray(mask).astype(bool)
    if not np.any(binary):
        raise ValueError('Instance mask is empty.')
    derived_bbox, centroid = mask_geometry(binary)
    bbox = tuple(float(value) for value in bbox_xyxy) if bbox_xyxy is not None else derived_bbox
    if len(bbox) != 4:
        raise ValueError('bbox_xyxy must contain four values.')
    return InstancePrediction(
        instance_id=int(instance_id),
        class_id=int(class_id),
        class_name=str(class_name),
        score=float(score),
        mask=binary,
        bbox_xyxy=(bbox[0], bbox[1], bbox[2], bbox[3]),
        centroid_uv=centroid,
    )


def largest_contour_points(mask: np.ndarray, max_points: int = 64) -> list[tuple[float, float]]:
    binary = np.asarray(mask, dtype=np.uint8) * 255
    contours, _ = cv2.findContours(binary, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
    if not contours:
        return []
    contour = max(contours, key=cv2.contourArea)
    perimeter = cv2.arcLength(contour, True)
    epsilon = 0.005 * perimeter
    approximated = cv2.approxPolyDP(contour, epsilon, True).reshape(-1, 2)
    if max_points > 2 and len(approximated) > max_points:
        indices = np.linspace(0, len(approximated) - 1, max_points).round().astype(int)
        approximated = approximated[indices]
    return [(float(point[0]), float(point[1])) for point in approximated]

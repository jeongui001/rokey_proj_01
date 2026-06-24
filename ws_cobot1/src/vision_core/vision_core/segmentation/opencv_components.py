from __future__ import annotations

import cv2
import numpy as np

from ..models import SegmentationResult
from ..mosaic import validate_bgr_image
from .base import InstanceSegmenter, make_instance


class OpenCVComponentsSegmenter(InstanceSegmenter):
    """Classical instance-mask backend for calibration, tests and model-free demos.

    It estimates a border background in Lab space, optionally colour-clusters the
    foreground, and assigns a separate mask to every connected component. It is
    an instance-segmentation backend, but it cannot reliably split touching blocks
    of the same colour. Use the Ultralytics backend with custom block masks for
    production verification.
    """

    backend_name = 'opencv_components'

    def __init__(self, config: dict):
        self._config = dict(config)
        self.model_name = 'opencv_components'
        self._background_mode = str(config.get('background_mode', 'border_lab')).lower()
        self._border_fraction = float(config.get('border_fraction', 0.06))
        self._background_distance = float(config.get('background_lab_distance', 20.0))
        self._min_area = int(config.get('min_mask_area_px', 100))
        self._max_instances = int(config.get('max_instances', 200))
        self._morph_kernel = int(config.get('morph_kernel', 3))
        self._open_iterations = int(config.get('open_iterations', 1))
        self._close_iterations = int(config.get('close_iterations', 1))
        self._split_by_color = bool(config.get('split_by_color', True))
        self._color_clusters = int(config.get('color_clusters', 6))
        self._kmeans_max_samples = int(config.get('kmeans_max_samples', 30000))
        self._class_name = str(config.get('class_name', 'block'))
        self._class_id = int(config.get('class_id', 0))
        if not 0.0 < self._border_fraction < 0.5:
            raise ValueError('border_fraction must be in (0, 0.5).')
        if self._background_distance <= 0.0:
            raise ValueError('background_lab_distance must be positive.')
        if self._min_area < 1:
            raise ValueError('min_mask_area_px must be positive.')

    @staticmethod
    def _border_pixels(lab: np.ndarray, fraction: float) -> np.ndarray:
        height, width = lab.shape[:2]
        band_y = max(1, int(round(height * fraction)))
        band_x = max(1, int(round(width * fraction)))
        return np.concatenate(
            [
                lab[:band_y].reshape(-1, 3),
                lab[-band_y:].reshape(-1, 3),
                lab[:, :band_x].reshape(-1, 3),
                lab[:, -band_x:].reshape(-1, 3),
            ],
            axis=0,
        )

    def _foreground_mask(self, image: np.ndarray, lab: np.ndarray) -> tuple[np.ndarray, np.ndarray]:
        if self._background_mode == 'none':
            distance = np.full(image.shape[:2], self._background_distance * 2.0, dtype=np.float32)
            return np.ones(image.shape[:2], dtype=np.uint8), distance
        if self._background_mode != 'border_lab':
            raise ValueError(f'Unsupported OpenCV background_mode: {self._background_mode}')

        border = self._border_pixels(lab, self._border_fraction).astype(np.float32)
        background = np.median(border, axis=0)
        distance = np.linalg.norm(lab.astype(np.float32) - background, axis=2)
        foreground = (distance >= self._background_distance).astype(np.uint8)

        kernel_size = max(1, self._morph_kernel)
        if kernel_size % 2 == 0:
            kernel_size += 1
        kernel = cv2.getStructuringElement(cv2.MORPH_ELLIPSE, (kernel_size, kernel_size))
        if self._open_iterations > 0:
            foreground = cv2.morphologyEx(
                foreground, cv2.MORPH_OPEN, kernel, iterations=self._open_iterations
            )
        if self._close_iterations > 0:
            foreground = cv2.morphologyEx(
                foreground, cv2.MORPH_CLOSE, kernel, iterations=self._close_iterations
            )
        return foreground, distance

    def _cluster_labels(self, lab: np.ndarray, foreground: np.ndarray) -> np.ndarray:
        labels = np.full(foreground.shape, -1, dtype=np.int32)
        points = lab[foreground.astype(bool)].astype(np.float32)
        if points.shape[0] == 0:
            return labels
        if not self._split_by_color or self._color_clusters <= 1:
            labels[foreground.astype(bool)] = 0
            return labels

        cluster_count = max(1, min(self._color_clusters, points.shape[0]))
        if points.shape[0] > self._kmeans_max_samples:
            rng = np.random.default_rng(0)
            sampled = points[rng.choice(points.shape[0], self._kmeans_max_samples, replace=False)]
        else:
            sampled = points

        cv2.setRNGSeed(0)
        criteria = (cv2.TERM_CRITERIA_EPS + cv2.TERM_CRITERIA_MAX_ITER, 40, 0.2)
        _, _, centers = cv2.kmeans(
            sampled,
            cluster_count,
            None,
            criteria,
            3,
            cv2.KMEANS_PP_CENTERS,
        )
        distances = np.linalg.norm(points[:, None, :] - centers[None, :, :], axis=2)
        point_labels = np.argmin(distances, axis=1).astype(np.int32)
        labels[foreground.astype(bool)] = point_labels
        return labels

    def infer(self, image_bgr: np.ndarray) -> SegmentationResult:
        validate_bgr_image(image_bgr)
        blurred = cv2.GaussianBlur(image_bgr, (5, 5), 0)
        lab = cv2.cvtColor(blurred, cv2.COLOR_BGR2LAB)
        foreground, background_distance = self._foreground_mask(blurred, lab)
        cluster_labels = self._cluster_labels(lab, foreground)

        candidates = []
        cluster_ids = [int(value) for value in np.unique(cluster_labels) if value >= 0]
        for cluster_id in cluster_ids:
            cluster_mask = (cluster_labels == cluster_id).astype(np.uint8)
            count, components, stats, _ = cv2.connectedComponentsWithStats(
                cluster_mask, connectivity=8
            )
            for component_id in range(1, count):
                area = int(stats[component_id, cv2.CC_STAT_AREA])
                if area < self._min_area:
                    continue
                mask = components == component_id
                mean_distance = float(np.mean(background_distance[mask]))
                score = float(np.clip(mean_distance / (self._background_distance * 2.0), 0.25, 1.0))
                candidates.append((area, score, mask))

        candidates.sort(key=lambda item: (item[0], item[1]), reverse=True)
        instances = []
        for index, (_, score, mask) in enumerate(candidates[: self._max_instances]):
            instances.append(
                make_instance(
                    index,
                    self._class_id,
                    self._class_name,
                    score,
                    mask,
                )
            )

        height, width = image_bgr.shape[:2]
        return SegmentationResult(
            backend=self.backend_name,
            model_name=self.model_name,
            image_width=width,
            image_height=height,
            instances=instances,
        )

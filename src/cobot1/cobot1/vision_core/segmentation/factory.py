from __future__ import annotations

from typing import Mapping

from ..config import resolve_config_path, segmentation_config
from .base import InstanceSegmenter
from .opencv_components import OpenCVComponentsSegmenter
from .ultralytics_backend import UltralyticsInstanceSegmenter


def create_segmenter(
    vision_config: dict,
    role: str,
    overrides: Mapping[str, object] | None = None,
) -> InstanceSegmenter:
    config = segmentation_config(vision_config, role, overrides)
    backend = str(config.get('backend', 'opencv_components')).strip().lower()
    if 'model_path' in config:
        config['model_path'] = resolve_config_path(vision_config, str(config.get('model_path', '')))

    if backend == 'opencv_components':
        return OpenCVComponentsSegmenter(config)
    if backend == 'ultralytics':
        return UltralyticsInstanceSegmenter(config)
    raise ValueError(f'Unsupported instance-segmentation backend: {backend}')

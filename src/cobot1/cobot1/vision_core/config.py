from __future__ import annotations

import copy
import os
from pathlib import Path
from typing import Any, Mapping

import numpy as np
import yaml


SUPPORTED_SEGMENTATION_BACKENDS = {'ultralytics', 'opencv_components'}


def load_vision_config(path: str | Path) -> dict[str, Any]:
    path = Path(path).expanduser().resolve()
    if not path.is_file():
        raise FileNotFoundError(f'Vision configuration file does not exist: {path}')
    with path.open('r', encoding='utf-8') as stream:
        config = yaml.safe_load(stream) or {}
    config.setdefault('_meta', {})['config_directory'] = str(path.parent)
    config['_meta']['config_file'] = str(path)
    validate_vision_config(config)
    return config


def validate_vision_config(config: dict[str, Any]) -> None:
    if 'palette' not in config:
        raise ValueError('vision config requires a palette section.')
    if not config['palette'].get('entries'):
        raise ValueError('vision config palette.entries must not be empty.')
    if not any(not bool(item.get('occupied', True)) for item in config['palette']['entries']):
        raise ValueError('palette.entries requires at least one occupied=false background entry.')

    workspace = config.get('workspace', {})
    roi = np.asarray(workspace.get('roi_normalized', []), dtype=np.float64)
    if roi.shape != (4, 2):
        raise ValueError('workspace.roi_normalized must contain four [u, v] points.')
    if np.any(roi < 0.0) or np.any(roi > 1.0):
        raise ValueError('workspace.roi_normalized values must be in [0, 1].')

    max_grid_size = int(config.get('mosaic', {}).get('max_grid_size', 64))
    if max_grid_size < 1:
        raise ValueError('mosaic.max_grid_size must be at least 1.')

    segmentation = config.get('segmentation', {})
    for role in ('image_processor', 'verifier'):
        merged = segmentation_config(config, role)
        backend = str(merged.get('backend', 'opencv_components')).strip().lower()
        if backend not in SUPPORTED_SEGMENTATION_BACKENDS:
            raise ValueError(
                f'Unsupported segmentation backend for {role}: {backend}. '
                f'Supported: {sorted(SUPPORTED_SEGMENTATION_BACKENDS)}'
            )

    projection = config.get('grid_projection', {})
    min_coverage = float(projection.get('min_cell_coverage', 0.12))
    if not 0.0 <= min_coverage <= 1.0:
        raise ValueError('grid_projection.min_cell_coverage must be in [0, 1].')


def roi_normalized(config: dict[str, Any]) -> np.ndarray:
    return np.asarray(config['workspace']['roi_normalized'], dtype=np.float64)


def _deep_merge(base: dict[str, Any], override: Mapping[str, Any]) -> dict[str, Any]:
    result = copy.deepcopy(base)
    for key, value in override.items():
        if isinstance(value, Mapping) and isinstance(result.get(key), Mapping):
            result[key] = _deep_merge(dict(result[key]), value)
        else:
            result[key] = copy.deepcopy(value)
    return result


def segmentation_config(
    config: dict[str, Any],
    role: str,
    overrides: Mapping[str, Any] | None = None,
) -> dict[str, Any]:
    root = config.get('segmentation', {})
    merged = _deep_merge(dict(root.get('defaults', {})), dict(root.get(role, {})))
    if overrides:
        cleaned = {key: value for key, value in overrides.items() if value not in ('', None)}
        merged = _deep_merge(merged, cleaned)
    merged['role'] = role
    return merged


def resolve_config_path(config: dict[str, Any], raw_path: str) -> str:
    value = os.path.expandvars(os.path.expanduser(str(raw_path).strip()))
    if not value:
        return ''
    path = Path(value)
    if not path.is_absolute():
        base = Path(config.get('_meta', {}).get('config_directory', '.'))
        path = base / path
    return str(path.resolve())

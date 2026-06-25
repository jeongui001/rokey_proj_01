from __future__ import annotations

from pathlib import Path
from typing import Any

import yaml


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

    max_grid_size = int(config.get('mosaic', {}).get('max_grid_size', 64))
    if max_grid_size < 1:
        raise ValueError('mosaic.max_grid_size must be at least 1.')

    projection = config.get('grid_projection', {})
    inner_ratio = float(projection.get('inner_cell_ratio', 0.70))
    if not 0.0 < inner_ratio <= 1.0:
        raise ValueError('grid_projection.inner_cell_ratio must be in (0, 1].')
    for key in ('background_lab_distance', 'unknown_lab_distance'):
        if float(projection.get(key, 1.0)) <= 0.0:
            raise ValueError(f'grid_projection.{key} must be positive.')
    overlay_alpha = float(projection.get('overlay_alpha', 0.42))
    if not 0.0 <= overlay_alpha <= 1.0:
        raise ValueError('grid_projection.overlay_alpha must be in [0, 1].')

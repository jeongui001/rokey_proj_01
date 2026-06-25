from __future__ import annotations

from dataclasses import dataclass
from math import exp
from typing import Iterable, Sequence

import cv2
import numpy as np


@dataclass(frozen=True)
class PaletteEntry:
    name: str
    rgb: tuple[int, int, int]
    occupied: bool = True

    def __post_init__(self) -> None:
        if len(self.rgb) != 3 or any(value < 0 or value > 255 for value in self.rgb):
            raise ValueError(f'Invalid RGB value for palette entry {self.name}: {self.rgb}')


class Palette:
    """Nearest-colour palette classifier using OpenCV Lab space."""

    def __init__(self, entries: Sequence[PaletteEntry], confidence_scale: float = 45.0):
        if not entries:
            raise ValueError('Palette must contain at least one entry.')
        if confidence_scale <= 0:
            raise ValueError('confidence_scale must be positive.')

        self.entries = list(entries)
        self.confidence_scale = float(confidence_scale)
        rgb_array = np.asarray([entry.rgb for entry in self.entries], dtype=np.uint8).reshape(-1, 1, 3)
        self._lab = cv2.cvtColor(rgb_array, cv2.COLOR_RGB2LAB).reshape(-1, 3).astype(np.float32)
        self._by_name = {entry.name: entry for entry in self.entries}
        if len(self._by_name) != len(self.entries):
            raise ValueError('Palette entry names must be unique.')

    @classmethod
    def from_config(cls, config: dict) -> 'Palette':
        palette_config = config.get('palette', config)
        raw_entries = palette_config.get('entries', [])
        entries = [
            PaletteEntry(
                name=str(item['name']),
                rgb=tuple(int(value) for value in item['rgb']),
                occupied=bool(item.get('occupied', True)),
            )
            for item in raw_entries
        ]
        return cls(entries, confidence_scale=float(palette_config.get('confidence_scale', 45.0)))

    def get(self, name: str) -> PaletteEntry:
        try:
            return self._by_name[name]
        except KeyError as exc:
            raise KeyError(f'Unknown palette colour: {name}') from exc

    def has(self, name: str) -> bool:
        return name in self._by_name

    def empty_entry(self, preferred_name: str = 'empty') -> PaletteEntry:
        if preferred_name and preferred_name in self._by_name:
            entry = self._by_name[preferred_name]
            if not entry.occupied:
                return entry
        for entry in self.entries:
            if not entry.occupied:
                return entry
        raise ValueError(
            'Palette needs at least one occupied=false entry for background cells.'
        )

    def names(self, include_unoccupied: bool = True) -> list[str]:
        return [
            entry.name for entry in self.entries
            if include_unoccupied or entry.occupied
        ]

    def classify_bgr(
        self,
        bgr: Iterable[float],
        *,
        include_unoccupied: bool = True,
    ) -> tuple[PaletteEntry, float, float]:
        """Return ``(entry, confidence, Lab distance)``."""

        bgr_array = np.clip(np.asarray(tuple(bgr), dtype=np.float32), 0, 255).astype(np.uint8)
        if bgr_array.shape != (3,):
            raise ValueError(f'Expected BGR triplet, received shape {bgr_array.shape}.')

        rgb_array = bgr_array[::-1].reshape(1, 1, 3)
        lab = cv2.cvtColor(rgb_array, cv2.COLOR_RGB2LAB).reshape(3).astype(np.float32)

        candidate_indices = [
            index for index, entry in enumerate(self.entries)
            if include_unoccupied or entry.occupied
        ]
        if not candidate_indices:
            raise ValueError('No palette candidates are enabled for this classification.')

        candidate_lab = self._lab[candidate_indices]
        distances = np.linalg.norm(candidate_lab - lab, axis=1)
        local_index = int(np.argmin(distances))
        global_index = candidate_indices[local_index]
        distance = float(distances[local_index])
        confidence = float(exp(-((distance / self.confidence_scale) ** 2)))
        return self.entries[global_index], confidence, distance

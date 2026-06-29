import numpy as np
import pytest
from cobot1.webcam_checker_node import (
    HOUGH_PARAMS,
    count_circles,
    perspective_crop,
)


TEST_HOUGH = next(iter(HOUGH_PARAMS.values()))


def _make_circle_image(n: int, size: int = 200) -> np.ndarray:
    """n개의 원이 그려진 BGR 이미지를 생성한다."""
    img = np.zeros((size, size, 3), dtype=np.uint8)
    spacing = size // (n + 1)
    for i in range(n):
        cx = spacing * (i + 1)
        cy = size // 2
        cv2.circle(img, (cx, cy), 15, (200, 200, 200), -1)
    return img


import cv2  # noqa: E402 (import after helper that uses it)


def test_count_circles_zero():
    blank = np.zeros((200, 200, 3), dtype=np.uint8)
    assert count_circles(blank, TEST_HOUGH) == 0


def test_count_circles_four():
    img = _make_circle_image(4)
    result = count_circles(img, TEST_HOUGH)
    assert result >= 4


def test_count_circles_six():
    img = _make_circle_image(6, size=300)
    result = count_circles(img, TEST_HOUGH)
    assert result >= 6


def test_perspective_crop_none_returns_original():
    img = np.zeros((100, 100, 3), dtype=np.uint8)
    result = perspective_crop(img, None)
    assert result is img


def test_perspective_crop_applies_crop():
    img = np.zeros((100, 100, 3), dtype=np.uint8)
    result = perspective_crop(
        img,
        [(10, 20), (60, 20), (60, 50), (10, 50)],
    )
    assert result.shape == (30, 50, 3)

from __future__ import annotations

from typing import Iterable, Sequence

import cv2
import numpy as np


def quaternion_to_rotation_matrix(x: float, y: float, z: float, w: float) -> np.ndarray:
    quaternion = np.asarray([x, y, z, w], dtype=np.float64)
    norm = float(np.linalg.norm(quaternion))
    if norm < 1e-12:
        raise ValueError('Quaternion norm is zero.')
    x, y, z, w = quaternion / norm
    return np.asarray(
        [
            [1.0 - 2.0 * (y * y + z * z), 2.0 * (x * y - z * w), 2.0 * (x * z + y * w)],
            [2.0 * (x * y + z * w), 1.0 - 2.0 * (x * x + z * z), 2.0 * (y * z - x * w)],
            [2.0 * (x * z - y * w), 2.0 * (y * z + x * w), 1.0 - 2.0 * (x * x + y * y)],
        ],
        dtype=np.float64,
    )


def transform_matrix(
    translation: Sequence[float],
    quaternion_xyzw: Sequence[float],
) -> np.ndarray:
    if len(translation) != 3 or len(quaternion_xyzw) != 4:
        raise ValueError('translation must have 3 values and quaternion must have 4 values.')
    matrix = np.eye(4, dtype=np.float64)
    matrix[:3, :3] = quaternion_to_rotation_matrix(*quaternion_xyzw)
    matrix[:3, 3] = np.asarray(translation, dtype=np.float64)
    return matrix


def normalized_roi_to_pixels(
    roi_normalized: Iterable[Iterable[float]],
    image_width: int,
    image_height: int,
) -> np.ndarray:
    roi = np.asarray(roi_normalized, dtype=np.float64)
    if roi.shape != (4, 2):
        raise ValueError('ROI must contain four [u, v] points.')
    if image_width <= 0 or image_height <= 0:
        raise ValueError('Image dimensions must be positive.')
    pixels = roi.copy()
    pixels[:, 0] *= image_width - 1
    pixels[:, 1] *= image_height - 1
    return pixels.astype(np.float32)


def grid_centers_in_roi(
    grid_size: int,
    roi_normalized: Iterable[Iterable[float]],
    image_width: int,
    image_height: int,
) -> list[tuple[float, float]]:
    """Map normalized grid centres through a quadrilateral perspective transform."""

    if grid_size < 1:
        raise ValueError('grid_size must be at least 1.')
    destination = normalized_roi_to_pixels(roi_normalized, image_width, image_height)
    source = np.asarray(
        [[0.0, 0.0], [1.0, 0.0], [1.0, 1.0], [0.0, 1.0]],
        dtype=np.float32,
    )
    homography = cv2.getPerspectiveTransform(source, destination)

    points = []
    for row in range(grid_size):
        for col in range(grid_size):
            points.append([(col + 0.5) / grid_size, (row + 0.5) / grid_size])
    mapped = cv2.perspectiveTransform(
        np.asarray(points, dtype=np.float32).reshape(-1, 1, 2), homography
    ).reshape(-1, 2)
    return [(float(point[0]), float(point[1])) for point in mapped]


def pixel_to_camera_ray(
    u: float,
    v: float,
    camera_matrix: Sequence[float] | np.ndarray,
    distortion: Sequence[float] | np.ndarray | None = None,
) -> np.ndarray:
    camera_matrix = np.asarray(camera_matrix, dtype=np.float64).reshape(3, 3)
    if camera_matrix[0, 0] <= 0.0 or camera_matrix[1, 1] <= 0.0:
        raise ValueError('Camera matrix is not calibrated.')

    if distortion is not None and np.any(np.abs(np.asarray(distortion, dtype=np.float64)) > 1e-12):
        normalized = cv2.undistortPoints(
            np.asarray([[[u, v]]], dtype=np.float64),
            camera_matrix,
            np.asarray(distortion, dtype=np.float64),
        )[0, 0]
        ray = np.asarray([normalized[0], normalized[1], 1.0], dtype=np.float64)
    else:
        ray = np.linalg.inv(camera_matrix) @ np.asarray([u, v, 1.0], dtype=np.float64)

    norm = float(np.linalg.norm(ray))
    if norm < 1e-12:
        raise ValueError('Computed camera ray has zero length.')
    return ray / norm


def intersect_ray_with_axis_plane(
    ray_origin: Sequence[float],
    ray_direction: Sequence[float],
    fixed_axis: str,
    fixed_value: float,
) -> np.ndarray:
    axis = fixed_axis.strip().lower()
    axis_index = {'x': 0, 'y': 1}.get(axis)
    if axis_index is None:
        raise ValueError('fixed_axis must be "x" or "y".')

    origin = np.asarray(ray_origin, dtype=np.float64)
    direction = np.asarray(ray_direction, dtype=np.float64)
    denominator = float(direction[axis_index])
    if abs(denominator) < 1e-9:
        raise ValueError(f'Camera ray is parallel to the {axis}={fixed_value} plane.')

    distance = (float(fixed_value) - float(origin[axis_index])) / denominator
    if distance <= 0.0:
        raise ValueError('The configured assembly plane lies behind the camera ray origin.')
    return origin + distance * direction


def pixel_to_base_on_axis_plane(
    u: float,
    v: float,
    camera_matrix: Sequence[float] | np.ndarray,
    distortion: Sequence[float] | np.ndarray | None,
    base_from_camera: np.ndarray,
    fixed_axis: str,
    fixed_value: float,
) -> np.ndarray:
    base_from_camera = np.asarray(base_from_camera, dtype=np.float64)
    if base_from_camera.shape != (4, 4):
        raise ValueError('base_from_camera must be a 4 x 4 transform matrix.')

    ray_camera = pixel_to_camera_ray(u, v, camera_matrix, distortion)
    origin_base = base_from_camera[:3, 3]
    direction_base = base_from_camera[:3, :3] @ ray_camera
    direction_base /= np.linalg.norm(direction_base)
    return intersect_ray_with_axis_plane(
        origin_base, direction_base, fixed_axis, fixed_value
    )

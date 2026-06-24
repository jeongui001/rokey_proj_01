import numpy as np

from vision_core.geometry import intersect_ray_with_axis_plane


def test_intersect_ray_with_x_plane():
    point = intersect_ray_with_axis_plane([0, 0, 0], [1, 2, 3], 'x', 2.0)
    assert np.allclose(point, [2.0, 4.0, 6.0])

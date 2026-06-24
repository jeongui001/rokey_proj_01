import cv2
import numpy as np

from vision_core.segmentation.opencv_components import OpenCVComponentsSegmenter


def test_connected_component_backend_returns_instance_masks():
    image = np.full((160, 220, 3), (100, 100, 100), dtype=np.uint8)
    cv2.rectangle(image, (15, 20), (85, 140), (20, 20, 220), -1)
    cv2.rectangle(image, (135, 20), (205, 140), (220, 70, 30), -1)
    segmenter = OpenCVComponentsSegmenter({
        'background_mode': 'border_lab',
        'border_fraction': 0.05,
        'background_lab_distance': 15.0,
        'min_mask_area_px': 1000,
        'max_instances': 10,
        'morph_kernel': 3,
        'open_iterations': 1,
        'close_iterations': 1,
        'split_by_color': True,
        'color_clusters': 4,
        'class_name': 'block',
        'class_id': 0,
    })
    result = segmenter.infer(image)
    assert len(result.instances) >= 2
    assert all(instance.mask.shape == image.shape[:2] for instance in result.instances)
    assert all(instance.area >= 1000 for instance in result.instances)

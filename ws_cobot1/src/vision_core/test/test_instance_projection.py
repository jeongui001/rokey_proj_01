import numpy as np

from vision_core.grid_projection import project_instances_to_grid
from vision_core.models import SegmentationResult
from vision_core.palette import Palette, PaletteEntry
from vision_core.segmentation.base import make_instance


def _palette():
    return Palette([
        PaletteEntry('red', (220, 35, 35), True),
        PaletteEntry('blue', (35, 80, 220), True),
        PaletteEntry('empty', (95, 95, 95), False),
    ])


def _config():
    return {
        'empty_palette_name': 'empty',
        'color_source': 'pixels',
        'class_to_palette': {},
        'min_instance_confidence': 0.0,
        'min_cell_coverage': 0.10,
        'conflict_cell_coverage': 0.08,
        'coverage_saturation': 0.6,
        'mask_erosion_px': 0,
        'min_color_pixels': 1,
        'confidence_weights': {'instance': 0.4, 'coverage': 0.4, 'color': 0.2},
    }


def test_instance_masks_drive_grid_cells():
    image = np.full((100, 100, 3), (95, 95, 95), dtype=np.uint8)
    image[:50, :50] = (35, 35, 220)   # BGR red
    image[50:, 50:] = (220, 80, 35)   # BGR blue

    red_mask = np.zeros((100, 100), dtype=bool)
    red_mask[:50, :50] = True
    blue_mask = np.zeros((100, 100), dtype=bool)
    blue_mask[50:, 50:] = True
    segmentation = SegmentationResult(
        backend='test',
        model_name='synthetic',
        image_width=100,
        image_height=100,
        instances=[
            make_instance(0, 0, 'object', 0.95, red_mask),
            make_instance(1, 0, 'object', 0.90, blue_mask),
        ],
    )

    result = project_instances_to_grid(image, segmentation, 2, _palette(), _config())
    cells = {(cell.row, cell.col): cell for cell in result.cells}
    assert cells[(0, 0)].occupied and cells[(0, 0)].color == 'red'
    assert cells[(1, 1)].occupied and cells[(1, 1)].color == 'blue'
    assert not cells[(0, 1)].occupied
    assert not cells[(1, 0)].occupied
    assert cells[(0, 0)].instance_id == 0
    assert cells[(1, 1)].instance_id == 1


def test_class_to_palette_can_drive_colour():
    image = np.zeros((40, 40, 3), dtype=np.uint8)
    mask = np.ones((40, 40), dtype=bool)
    segmentation = SegmentationResult(
        backend='test',
        model_name='synthetic',
        image_width=40,
        image_height=40,
        instances=[make_instance(0, 4, 'red_block', 0.99, mask)],
    )
    config = _config()
    config['color_source'] = 'class'
    config['class_to_palette'] = {'red_block': 'red'}
    result = project_instances_to_grid(image, segmentation, 1, _palette(), config)
    assert result.cells[0].color == 'red'
    assert result.cells[0].occupied

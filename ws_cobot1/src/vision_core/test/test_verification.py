from vision_core.models import CellSample
from vision_core.verification import compare_cells


def _cell(row, col, color, occupied=True, **kwargs):
    return CellSample(
        row=row,
        col=col,
        color=color,
        rgb=(0, 0, 0),
        occupied=occupied,
        confidence=kwargs.pop('confidence', 0.9),
        mask_coverage=kwargs.pop('mask_coverage', 0.6 if occupied else 0.0),
        overlapping_instances=kwargs.pop('overlapping_instances', 1 if occupied else 0),
        centroid_offset_ratio=kwargs.pop('centroid_offset_ratio', 0.1 if occupied else float('nan')),
        **kwargs,
    )


def test_compare_detects_wrong_colour_and_missing():
    expected = [_cell(0, 0, 'red'), _cell(0, 1, 'blue')]
    observed = [_cell(0, 0, 'blue'), _cell(0, 1, 'empty', occupied=False)]
    result = compare_cells(expected, observed, min_observation_confidence=0.4)
    reasons = [item.reason for item in result.mismatches]
    assert reasons == ['WRONG_COLOR', 'MISSING']
    assert result.match_rate == 0.0


def test_compare_detects_instance_conflict():
    expected = [_cell(0, 0, 'red')]
    observed = [_cell(0, 0, 'red', overlapping_instances=2)]
    result = compare_cells(expected, observed, max_overlapping_instances=1)
    assert result.mismatches[0].reason == 'INSTANCE_CONFLICT'

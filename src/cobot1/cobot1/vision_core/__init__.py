"""ROS-independent instance segmentation, grid projection and camera geometry."""

from .grid_projection import assign_instance_colors, project_instances_to_grid
from .models import (
    CellMismatch,
    CellSample,
    ComparisonResult,
    GridProjectionResult,
    InstancePrediction,
    SegmentationResult,
)

__all__ = [
    'CellMismatch',
    'CellSample',
    'ComparisonResult',
    'GridProjectionResult',
    'InstancePrediction',
    'SegmentationResult',
    'assign_instance_colors',
    'project_instances_to_grid',
]

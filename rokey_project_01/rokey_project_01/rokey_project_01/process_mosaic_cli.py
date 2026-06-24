from __future__ import annotations

import argparse
import json
from pathlib import Path

import cv2
import rclpy
from cv_bridge import CvBridge
from rclpy.node import Node

from rokey_project_01_interfaces.srv import ProcessMosaic


def _model_to_dict(model):
    return {
        'model_id': model.model_id,
        'segmentation_backend': model.segmentation_backend,
        'segmentation_model': model.segmentation_model,
        'source_size': [int(model.source_width), int(model.source_height)],
        'grid_size': int(model.grid_size),
        'output_size': [int(model.output_width), int(model.output_height)],
        'fixed_axis': model.fixed_axis,
        'fixed_axis_value': float(model.fixed_axis_value),
        'instances': [
            {
                'instance_id': int(item.instance_id),
                'class_id': int(item.class_id),
                'class_name': item.class_name,
                'confidence': float(item.confidence),
                'bbox': [
                    int(item.roi.x_offset), int(item.roi.y_offset),
                    int(item.roi.width), int(item.roi.height),
                ],
                'centroid': [float(item.centroid.x), float(item.centroid.y)],
                'mask_area': int(item.mask_area),
                'color': item.color,
                'color_confidence': float(item.color_confidence),
            }
            for item in model.instances
        ],
        'cells': [
            {
                'index': int(cell.index),
                'row': int(cell.row),
                'col': int(cell.col),
                'color': cell.color,
                'occupied': bool(cell.occupied),
                'confidence': float(cell.confidence),
                'instance_id': int(cell.instance_id),
                'class_name': cell.class_name,
                'mask_coverage': float(cell.mask_coverage),
                'source_uv': [float(cell.source_u), float(cell.source_v)],
                'camera_uv': [float(cell.camera_u), float(cell.camera_v)],
                'target_frame': cell.target.header.frame_id,
                'target': [
                    float(cell.target.point.x),
                    float(cell.target.point.y),
                    float(cell.target.point.z),
                ],
            }
            for cell in model.cells
        ],
    }


class MosaicClient(Node):
    def __init__(self, service_name: str):
        super().__init__('process_mosaic_cli')
        self.client = self.create_client(ProcessMosaic, service_name)


def main(args=None) -> None:
    parser = argparse.ArgumentParser(description='Segment an image and call ProcessMosaic.')
    parser.add_argument('--image', required=True)
    parser.add_argument('--grid-size', type=int, required=True)
    parser.add_argument('--mosaic', default='mosaic.png')
    parser.add_argument('--segmentation', default='source_segmentation.png')
    parser.add_argument('--fitted', default='fitted_source.png')
    parser.add_argument('--model-json', default='model.json')
    parser.add_argument('--width', type=int, default=0)
    parser.add_argument('--height', type=int, default=0)
    parser.add_argument('--fixed-axis', choices=['x', 'y'], default='')
    parser.add_argument('--fixed-value', type=float, default=0.0)
    parser.add_argument('--compute-coordinates', action='store_true')
    parser.add_argument('--service', default='/image/analyze')
    parsed, ros_args = parser.parse_known_args(args)

    image = cv2.imread(parsed.image, cv2.IMREAD_COLOR)
    if image is None:
        raise SystemExit(f'Cannot read image: {parsed.image}')

    rclpy.init(args=ros_args)
    node = MosaicClient(parsed.service)
    try:
        if not node.client.wait_for_service(timeout_sec=10.0):
            raise RuntimeError(f'Service is unavailable: {parsed.service}')
        bridge = CvBridge()
        request = ProcessMosaic.Request()
        request.input_image = bridge.cv2_to_imgmsg(image, encoding='bgr8')
        request.input_image.header.frame_id = 'source_image'
        request.grid_size = parsed.grid_size
        request.output_width = parsed.width
        request.output_height = parsed.height
        request.fixed_axis = parsed.fixed_axis
        request.fixed_axis_value = parsed.fixed_value
        request.compute_robot_coordinates = parsed.compute_coordinates

        future = node.client.call_async(request)
        rclpy.spin_until_future_complete(node, future)
        response = future.result()
        if response is None:
            raise RuntimeError('Service call failed without a response.')
        if not response.success:
            raise RuntimeError(response.message)

        outputs = {
            parsed.mosaic: response.mosaic_image,
            parsed.segmentation: response.segmentation_overlay,
            parsed.fitted: response.fitted_image,
        }
        for raw_path, message in outputs.items():
            path = Path(raw_path).expanduser().resolve()
            path.parent.mkdir(parents=True, exist_ok=True)
            image_out = bridge.imgmsg_to_cv2(message, desired_encoding='bgr8')
            if not cv2.imwrite(str(path), image_out):
                raise RuntimeError(f'Failed to save image: {path}')

        model_path = Path(parsed.model_json).expanduser().resolve()
        model_path.parent.mkdir(parents=True, exist_ok=True)
        with model_path.open('w', encoding='utf-8') as stream:
            json.dump(_model_to_dict(response.model), stream, ensure_ascii=False, indent=2, allow_nan=True)
        node.get_logger().info(response.message)
    finally:
        node.destroy_node()
        rclpy.shutdown()


if __name__ == '__main__':
    main()

from __future__ import annotations

import argparse
from pathlib import Path

import cv2
import rclpy
from cv_bridge import CvBridge
from rclpy.node import Node

from vision_interfaces.srv import VerifyAssembly


class VerificationClient(Node):
    def __init__(self, service_name: str):
        super().__init__('verify_cli')
        self.client = self.create_client(VerifyAssembly, service_name)


def main(args=None) -> None:
    parser = argparse.ArgumentParser(
        description='Verify the latest camera frame against the cached expected model.'
    )
    parser.add_argument('--service', default='/vision/verify_assembly')
    parser.add_argument('--threshold', type=float, default=0.0)
    parser.add_argument('--timeout', type=float, default=2.0)
    parser.add_argument('--use-latest-frame', action='store_true')
    parser.add_argument('--overlay', default='verification_overlay.png')
    parser.add_argument('--workspace', default='verification_workspace.png')
    parser.add_argument('--segmentation', default='verification_segmentation.png')
    parser.add_argument('--observed', default='observed_mosaic.png')
    parsed, ros_args = parser.parse_known_args(args)

    rclpy.init(args=ros_args)
    node = VerificationClient(parsed.service)
    try:
        if not node.client.wait_for_service(timeout_sec=10.0):
            raise RuntimeError(f'Service is unavailable: {parsed.service}')

        request = VerifyAssembly.Request()
        request.pass_threshold = parsed.threshold
        request.wait_for_fresh_frame = not parsed.use_latest_frame
        request.timeout_sec = parsed.timeout

        future = node.client.call_async(request)
        rclpy.spin_until_future_complete(node, future)
        response = future.result()
        if response is None:
            raise RuntimeError('Service call failed without a response.')
        if not response.success:
            raise RuntimeError(response.message)

        bridge = CvBridge()
        outputs = {
            parsed.overlay: response.overlay_image,
            parsed.workspace: response.workspace_image,
            parsed.segmentation: response.segmentation_overlay,
            parsed.observed: response.observed_mosaic,
        }
        for raw_path, message in outputs.items():
            path = Path(raw_path).expanduser().resolve()
            path.parent.mkdir(parents=True, exist_ok=True)
            image = bridge.imgmsg_to_cv2(message, desired_encoding='bgr8')
            if not cv2.imwrite(str(path), image):
                raise RuntimeError(f'Failed to save image: {path}')

        result_text = 'PASS' if response.passed else 'FAIL'
        node.get_logger().info(f'{result_text}: {response.match_rate:.1f}% - {response.message}')
        for mismatch in response.mismatches:
            node.get_logger().info(
                f'mismatch ({mismatch.row}, {mismatch.col}): {mismatch.details}'
            )
    finally:
        node.destroy_node()
        rclpy.shutdown()


if __name__ == '__main__':
    main()

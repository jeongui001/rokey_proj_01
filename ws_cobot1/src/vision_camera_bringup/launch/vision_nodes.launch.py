import os

from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument
from launch.substitutions import LaunchConfiguration
from launch_ros.actions import Node
from launch_ros.parameter_descriptions import ParameterValue


def generate_launch_description():
    bringup_share = get_package_share_directory('vision_camera_bringup')
    image_share = get_package_share_directory('image_processor_node')
    verify_share = get_package_share_directory('verify_node')

    default_vision_config = os.path.join(bringup_share, 'config', 'vision.yaml')
    image_params = os.path.join(image_share, 'config', 'image_processor.yaml')
    verify_params = os.path.join(verify_share, 'config', 'verify.yaml')

    return LaunchDescription([
        DeclareLaunchArgument('vision_config_file', default_value=default_vision_config),
        DeclareLaunchArgument('calibration_ready', default_value='false'),
        DeclareLaunchArgument('base_frame', default_value='base_link'),
        DeclareLaunchArgument('camera_frame', default_value='front_camera_optical_frame'),
        DeclareLaunchArgument('image_segmenter_backend', default_value=''),
        DeclareLaunchArgument('image_model_path', default_value=''),
        DeclareLaunchArgument('verify_segmenter_backend', default_value=''),
        DeclareLaunchArgument('verify_model_path', default_value=''),
        DeclareLaunchArgument('segmentation_device', default_value=''),
        DeclareLaunchArgument('warmup_segmenters', default_value='false'),
        DeclareLaunchArgument('publish_live_segmentation', default_value='false'),
        Node(
            package='image_processor_node',
            executable='image_processor',
            name='image_processor',
            namespace='vision',
            output='screen',
            parameters=[
                image_params,
                {
                    'vision_config_file': LaunchConfiguration('vision_config_file'),
                    'calibration_ready': ParameterValue(
                        LaunchConfiguration('calibration_ready'), value_type=bool
                    ),
                    'base_frame_override': LaunchConfiguration('base_frame'),
                    'camera_frame_override': LaunchConfiguration('camera_frame'),
                    'segmentation_backend_override': LaunchConfiguration('image_segmenter_backend'),
                    'segmentation_model_path_override': LaunchConfiguration('image_model_path'),
                    'segmentation_device_override': LaunchConfiguration('segmentation_device'),
                    'warmup_segmenter': ParameterValue(
                        LaunchConfiguration('warmup_segmenters'), value_type=bool
                    ),
                },
            ],
        ),
        Node(
            package='verify_node',
            executable='verify',
            name='verify',
            namespace='vision',
            output='screen',
            parameters=[
                verify_params,
                {
                    'vision_config_file': LaunchConfiguration('vision_config_file'),
                    'segmentation_backend_override': LaunchConfiguration('verify_segmenter_backend'),
                    'segmentation_model_path_override': LaunchConfiguration('verify_model_path'),
                    'segmentation_device_override': LaunchConfiguration('segmentation_device'),
                    'warmup_segmenter': ParameterValue(
                        LaunchConfiguration('warmup_segmenters'), value_type=bool
                    ),
                    'publish_live_segmentation': ParameterValue(
                        LaunchConfiguration('publish_live_segmentation'), value_type=bool
                    ),
                },
            ],
        ),
    ])

import os

from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument
from launch.substitutions import LaunchConfiguration
from launch_ros.actions import Node
from launch_ros.parameter_descriptions import ParameterValue


def generate_launch_description():
    pkg_share = get_package_share_directory('rokey_project_01')
    default_vision_config = os.path.join(pkg_share, 'config', 'vision.yaml')
    image_params = os.path.join(pkg_share, 'config', 'image_processor.yaml')
    verify_params = os.path.join(pkg_share, 'config', 'verify.yaml')

    return LaunchDescription([
        DeclareLaunchArgument('vision_config_file', default_value=default_vision_config),
        DeclareLaunchArgument('calibration_ready', default_value='false'),

        Node(
            package='rokey_project_01',
            executable='bridge_node',
            name='bridge',
            output='screen',
        ),
        Node(
            package='rokey_project_01',
            executable='image_processor_node',
            name='image_processor',
            output='screen',
            parameters=[
                image_params,
                {
                    'vision_config_file': LaunchConfiguration('vision_config_file'),
                    'calibration_ready': ParameterValue(
                        LaunchConfiguration('calibration_ready'), value_type=bool
                    ),
                },
            ],
        ),
        Node(
            package='rokey_project_01',
            executable='sequencer_node',
            name='sequencer',
            output='screen',
        ),
        Node(
            package='rokey_project_01',
            executable='robot_controller_node',
            name='robot_controller',
            output='screen',
        ),
        Node(
            package='rokey_project_01',
            executable='verify_node',
            name='verify',
            output='screen',
            parameters=[
                verify_params,
                {
                    'vision_config_file': LaunchConfiguration('vision_config_file'),
                },
            ],
        ),
        Node(
            package='rokey_project_01',
            executable='webcam_node',
            name='webcam',
            output='screen',
        ),
        Node(
            package='rokey_project_01',
            executable='camera_node',
            name='camera',
            output='screen',
        ),
    ])

from launch import LaunchDescription
from launch_ros.actions import Node


def generate_launch_description():
    return LaunchDescription([
        Node(
            package='cobot1',
            executable='bridge_node',
            name='bridge',
            output='screen',
        ),
        Node(
            package='cobot1',
            executable='image_processor_node',
            name='image_processor',
            output='screen',
        ),
        Node(
            package='cobot1',
            executable='sequencer_node',
            name='sequencer',
            output='screen',
        ),
        Node(
            package='cobot1',
            executable='robot_controller_node',
            name='robot_controller',
            output='screen',
        ),
        Node(
            package='cobot1',
            executable='verify_node',
            name='verify',
            output='screen',
        ),
        Node(
            package='cobot1',
            executable='webcam_node',
            name='webcam',
            output='screen',
        ),
        Node(
            package='cobot1',
            executable='camera_node',
            name='camera',
            output='screen',
        ),
    ])

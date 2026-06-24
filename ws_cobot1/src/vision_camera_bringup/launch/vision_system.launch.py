import os

from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument
from launch.conditions import IfCondition
from launch.substitutions import LaunchConfiguration
from launch_ros.actions import Node
from launch_ros.parameter_descriptions import ParameterValue


def generate_launch_description():
    bringup_share = get_package_share_directory('vision_camera_bringup')
    image_share = get_package_share_directory('image_processor_node')
    verify_share = get_package_share_directory('verify_node')

    camera_params = os.path.join(bringup_share, 'config', 'usb_camera.yaml')
    default_vision_config = os.path.join(bringup_share, 'config', 'vision.yaml')
    image_params = os.path.join(image_share, 'config', 'image_processor.yaml')
    verify_params = os.path.join(verify_share, 'config', 'verify.yaml')

    use_camera_driver = LaunchConfiguration('use_camera_driver')
    publish_static_tf = LaunchConfiguration('publish_static_tf')
    calibration_ready = LaunchConfiguration('calibration_ready')
    video_device = LaunchConfiguration('video_device')
    image_width = LaunchConfiguration('image_width')
    image_height = LaunchConfiguration('image_height')
    framerate = LaunchConfiguration('framerate')
    base_frame = LaunchConfiguration('base_frame')
    camera_frame = LaunchConfiguration('camera_frame')
    vision_config_file = LaunchConfiguration('vision_config_file')

    declarations = [
        DeclareLaunchArgument('use_camera_driver', default_value='true'),
        DeclareLaunchArgument('publish_static_tf', default_value='true'),
        DeclareLaunchArgument('calibration_ready', default_value='false'),
        DeclareLaunchArgument('vision_config_file', default_value=default_vision_config),
        DeclareLaunchArgument('video_device', default_value='/dev/video0'),
        DeclareLaunchArgument('image_width', default_value='640'),
        DeclareLaunchArgument('image_height', default_value='480'),
        DeclareLaunchArgument('framerate', default_value='30.0'),
        DeclareLaunchArgument('base_frame', default_value='base_link'),
        DeclareLaunchArgument('camera_frame', default_value='front_camera_optical_frame'),
        DeclareLaunchArgument('image_segmenter_backend', default_value=''),
        DeclareLaunchArgument('image_model_path', default_value=''),
        DeclareLaunchArgument('verify_segmenter_backend', default_value=''),
        DeclareLaunchArgument('verify_model_path', default_value=''),
        DeclareLaunchArgument('segmentation_device', default_value=''),
        DeclareLaunchArgument('warmup_segmenters', default_value='false'),
        DeclareLaunchArgument('publish_live_segmentation', default_value='false'),
        # base_frame -> camera optical frame. Replace with calibrated extrinsics.
        DeclareLaunchArgument('camera_x', default_value='0.0'),
        DeclareLaunchArgument('camera_y', default_value='0.0'),
        DeclareLaunchArgument('camera_z', default_value='0.0'),
        DeclareLaunchArgument('camera_roll', default_value='0.0'),
        DeclareLaunchArgument('camera_pitch', default_value='0.0'),
        DeclareLaunchArgument('camera_yaw', default_value='0.0'),
    ]

    camera_driver = Node(
        package='usb_cam',
        executable='usb_cam_node_exe',
        name='driver',
        namespace='front_camera',
        output='screen',
        respawn=True,
        respawn_delay=2.0,
        condition=IfCondition(use_camera_driver),
        parameters=[
            camera_params,
            {
                'video_device': video_device,
                'image_width': ParameterValue(image_width, value_type=int),
                'image_height': ParameterValue(image_height, value_type=int),
                'framerate': ParameterValue(framerate, value_type=float),
                'frame_id': camera_frame,
            },
        ],
    )

    static_tf = Node(
        package='tf2_ros',
        executable='static_transform_publisher',
        name='front_camera_static_tf',
        output='screen',
        condition=IfCondition(publish_static_tf),
        arguments=[
            '--x', LaunchConfiguration('camera_x'),
            '--y', LaunchConfiguration('camera_y'),
            '--z', LaunchConfiguration('camera_z'),
            '--roll', LaunchConfiguration('camera_roll'),
            '--pitch', LaunchConfiguration('camera_pitch'),
            '--yaw', LaunchConfiguration('camera_yaw'),
            '--frame-id', base_frame,
            '--child-frame-id', camera_frame,
        ],
    )

    image_processor = Node(
        package='image_processor_node',
        executable='image_processor',
        name='image_processor',
        namespace='vision',
        output='screen',
        parameters=[
            image_params,
            {
                'vision_config_file': vision_config_file,
                'calibration_ready': ParameterValue(calibration_ready, value_type=bool),
                'base_frame_override': base_frame,
                'camera_frame_override': camera_frame,
                'segmentation_backend_override': LaunchConfiguration('image_segmenter_backend'),
                'segmentation_model_path_override': LaunchConfiguration('image_model_path'),
                'segmentation_device_override': LaunchConfiguration('segmentation_device'),
                'warmup_segmenter': ParameterValue(
                    LaunchConfiguration('warmup_segmenters'), value_type=bool
                ),
            },
        ],
    )

    verifier = Node(
        package='verify_node',
        executable='verify',
        name='verify',
        namespace='vision',
        output='screen',
        parameters=[
            verify_params,
            {
                'vision_config_file': vision_config_file,
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
    )

    return LaunchDescription(
        declarations + [camera_driver, static_tf, image_processor, verifier]
    )

from setuptools import find_packages, setup
import os
from glob import glob

package_name = 'rokey_project_01'

setup(
    name=package_name,
    version='0.1.0',
    packages=find_packages(exclude=['test']),
    data_files=[
        ('share/ament_index/resource_index/packages', ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
        (os.path.join('share', package_name, 'launch'), glob('launch/*.py')),
        (os.path.join('share', package_name, 'config'), glob('config/*.yaml')),
    ],
    install_requires=['setuptools'],
    zip_safe=True,
    maintainer='hwangjeongui',
    maintainer_email='hwangjeongui01@gmail.com',
    description='레고 조립 시스템 ROS2 노드',
    license='Apache-2.0',
    entry_points={
        'console_scripts': [
            'bridge_node = rokey_project_01.bridge_node:main',
            'image_processor_node = rokey_project_01.image_processor_node:main',
            'sequencer_node = rokey_project_01.sequencer_node:main',
            'robot_controller_node = rokey_project_01.robot_controller_node:main',
            'verify_node = rokey_project_01.verify_node:main',
            'webcam_node = rokey_project_01.webcam_node:main',
            'camera_node = rokey_project_01.camera_node:main',
            'process_mosaic_cli = rokey_project_01.process_mosaic_cli:main',
            'verify_cli = rokey_project_01.verify_cli:main',
        ],
    },
)

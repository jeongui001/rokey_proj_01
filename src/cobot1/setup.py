from setuptools import find_packages, setup
import os
from glob import glob

package_name = 'cobot1'

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
            'bridge_node = cobot1.bridge_node:main',
            'image_processor_node = cobot1.image_processor_node:main',
            'sequencer_node = cobot1.sequencer_node:main',
            'robot_controller_node = cobot1.robot_controller_node:main',
            'verify_node = cobot1.verify_node:main',
            'webcam_node = cobot1.webcam_node:main',
            'camera_node = cobot1.camera_node:main',
        ],
    },
)

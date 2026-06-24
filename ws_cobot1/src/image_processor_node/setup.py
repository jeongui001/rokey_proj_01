from glob import glob
import os
from setuptools import find_packages, setup

package_name = 'image_processor_node'

setup(
    name=package_name,
    version='0.2.0',
    packages=find_packages(exclude=['test']),
    data_files=[
        ('share/ament_index/resource_index/packages', ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
        (os.path.join('share', package_name, 'config'), glob('config/*.yaml')),
    ],
    install_requires=['setuptools'],
    zip_safe=True,
    maintainer='assembly team',
    maintainer_email='team@example.com',
    description='Instance-segmentation image-to-block mosaic and base-frame coordinate service.',
    license='Apache-2.0',
    tests_require=['pytest'],
    entry_points={
        'console_scripts': [
            'image_processor = image_processor_node.node:main',
            'process_mosaic_cli = image_processor_node.process_mosaic_cli:main',
        ],
    },
)

from glob import glob
import os
from setuptools import find_packages, setup

package_name = 'verify_node'

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
    description='Front-camera relay and instance-segmentation completed-assembly verifier.',
    license='Apache-2.0',
    tests_require=['pytest'],
    entry_points={
        'console_scripts': [
            'verify = verify_node.node:main',
            'verify_cli = verify_node.verify_cli:main',
        ],
    },
)

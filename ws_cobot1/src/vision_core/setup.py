from setuptools import find_packages, setup

package_name = 'vision_core'

setup(
    name=package_name,
    version='0.2.0',
    packages=find_packages(exclude=['test']),
    data_files=[
        ('share/ament_index/resource_index/packages', ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
    ],
    install_requires=['setuptools'],
    zip_safe=True,
    maintainer='assembly team',
    maintainer_email='team@example.com',
    description='ROS-independent instance segmentation, grid projection, camera geometry and verification.',
    license='Apache-2.0',
    tests_require=['pytest'],
)

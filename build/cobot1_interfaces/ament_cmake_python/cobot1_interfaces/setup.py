from setuptools import find_packages
from setuptools import setup

setup(
    name='cobot1_interfaces',
    version='0.1.0',
    packages=find_packages(
        include=('cobot1_interfaces', 'cobot1_interfaces.*')),
)

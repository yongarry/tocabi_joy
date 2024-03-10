#!/usr/bin/env python

from distutils.core import setup
from catkin_pkg.python_setup import generate_distutils_setup

d = generate_distutils_setup(
    packages=['tocabi_joy'],
    package_dir={'': 'src'},
    requires=['std_msgs', 'roscpp', 'sensor_msgs', 'geometry_msgs'],
    scripts=['scripts/tocabi_joy']
)

setup(**d)
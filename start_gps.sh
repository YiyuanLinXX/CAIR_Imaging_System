#!/bin/bash

# Open a new terminal and run the commands
gnome-terminal -- bash -c "source /home/cairlab/Projects/ros_temp/devel/setup.bash;roslaunch gps_publisher gps_gui.launch ; exec bash"

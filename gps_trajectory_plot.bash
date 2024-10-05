#!/bin/bash

# Check if the user provided the GPS file path
if [ "$#" -ne 1 ]; then
    echo "Usage: ./run_gps_plot.sh <gps_file_path>"
    exit 1
fi

# Run the Python script with the GPS file path
python3 /home/cairlab/Documents/common_scripts/gps_trajectory_plot.py "$1"


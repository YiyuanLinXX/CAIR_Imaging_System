#!/bin/bash

# To convert images from gray sclae PGM files to RGB PNG files, please run
# python convert_pgm2png.py 'path/to/pgm/folder' 'target/path/to/png/folder'
# if the target folder doesn't exist, the program will automatically generate the folder

# python convert_pgm2png.py '/media/yl3663/Data/UMN_2024/PGM/08_10_UMN_02/test1' '/media/yl3663/Data/UMN_2024/PGM/08_10_UMN_02/test1_result' 

# To convert images from gray scale PGM files to RGB PNG files, please run
# bash convert_pgm2png.bash 'path/to/pgm/folder' 'target/path/to/png/folder'
# python convert_pgm2png.py "$1" "$2"

python3 /home/cairlab/Documents/common_scripts/convert_pgm2png.py '/home/cairlab/Data/0920_Wellington/016E9093' '/home/cairlab/0920_Wellington/016E9093'


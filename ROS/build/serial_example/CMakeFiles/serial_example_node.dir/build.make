# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/cairlab/Projects/ROS/src

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/cairlab/Projects/ROS/build

# Include any dependencies generated for this target.
include serial_example/CMakeFiles/serial_example_node.dir/depend.make

# Include the progress variables for this target.
include serial_example/CMakeFiles/serial_example_node.dir/progress.make

# Include the compile flags for this target's objects.
include serial_example/CMakeFiles/serial_example_node.dir/flags.make

serial_example/CMakeFiles/serial_example_node.dir/src/serial_example_node.cpp.o: serial_example/CMakeFiles/serial_example_node.dir/flags.make
serial_example/CMakeFiles/serial_example_node.dir/src/serial_example_node.cpp.o: /home/cairlab/Projects/ROS/src/serial_example/src/serial_example_node.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/cairlab/Projects/ROS/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object serial_example/CMakeFiles/serial_example_node.dir/src/serial_example_node.cpp.o"
	cd /home/cairlab/Projects/ROS/build/serial_example && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/serial_example_node.dir/src/serial_example_node.cpp.o -c /home/cairlab/Projects/ROS/src/serial_example/src/serial_example_node.cpp

serial_example/CMakeFiles/serial_example_node.dir/src/serial_example_node.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/serial_example_node.dir/src/serial_example_node.cpp.i"
	cd /home/cairlab/Projects/ROS/build/serial_example && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/cairlab/Projects/ROS/src/serial_example/src/serial_example_node.cpp > CMakeFiles/serial_example_node.dir/src/serial_example_node.cpp.i

serial_example/CMakeFiles/serial_example_node.dir/src/serial_example_node.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/serial_example_node.dir/src/serial_example_node.cpp.s"
	cd /home/cairlab/Projects/ROS/build/serial_example && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/cairlab/Projects/ROS/src/serial_example/src/serial_example_node.cpp -o CMakeFiles/serial_example_node.dir/src/serial_example_node.cpp.s

# Object files for target serial_example_node
serial_example_node_OBJECTS = \
"CMakeFiles/serial_example_node.dir/src/serial_example_node.cpp.o"

# External object files for target serial_example_node
serial_example_node_EXTERNAL_OBJECTS =

/home/cairlab/Projects/ROS/devel/lib/serial_example/serial_example_node: serial_example/CMakeFiles/serial_example_node.dir/src/serial_example_node.cpp.o
/home/cairlab/Projects/ROS/devel/lib/serial_example/serial_example_node: serial_example/CMakeFiles/serial_example_node.dir/build.make
/home/cairlab/Projects/ROS/devel/lib/serial_example/serial_example_node: /opt/ros/noetic/lib/libroscpp.so
/home/cairlab/Projects/ROS/devel/lib/serial_example/serial_example_node: /usr/lib/x86_64-linux-gnu/libpthread.so
/home/cairlab/Projects/ROS/devel/lib/serial_example/serial_example_node: /usr/lib/x86_64-linux-gnu/libboost_chrono.so.1.71.0
/home/cairlab/Projects/ROS/devel/lib/serial_example/serial_example_node: /usr/lib/x86_64-linux-gnu/libboost_filesystem.so.1.71.0
/home/cairlab/Projects/ROS/devel/lib/serial_example/serial_example_node: /opt/ros/noetic/lib/librosconsole.so
/home/cairlab/Projects/ROS/devel/lib/serial_example/serial_example_node: /opt/ros/noetic/lib/librosconsole_log4cxx.so
/home/cairlab/Projects/ROS/devel/lib/serial_example/serial_example_node: /opt/ros/noetic/lib/librosconsole_backend_interface.so
/home/cairlab/Projects/ROS/devel/lib/serial_example/serial_example_node: /usr/lib/x86_64-linux-gnu/liblog4cxx.so
/home/cairlab/Projects/ROS/devel/lib/serial_example/serial_example_node: /usr/lib/x86_64-linux-gnu/libboost_regex.so.1.71.0
/home/cairlab/Projects/ROS/devel/lib/serial_example/serial_example_node: /opt/ros/noetic/lib/libxmlrpcpp.so
/home/cairlab/Projects/ROS/devel/lib/serial_example/serial_example_node: /opt/ros/noetic/lib/libserial.so
/home/cairlab/Projects/ROS/devel/lib/serial_example/serial_example_node: /opt/ros/noetic/lib/libroscpp_serialization.so
/home/cairlab/Projects/ROS/devel/lib/serial_example/serial_example_node: /opt/ros/noetic/lib/librostime.so
/home/cairlab/Projects/ROS/devel/lib/serial_example/serial_example_node: /usr/lib/x86_64-linux-gnu/libboost_date_time.so.1.71.0
/home/cairlab/Projects/ROS/devel/lib/serial_example/serial_example_node: /opt/ros/noetic/lib/libcpp_common.so
/home/cairlab/Projects/ROS/devel/lib/serial_example/serial_example_node: /usr/lib/x86_64-linux-gnu/libboost_system.so.1.71.0
/home/cairlab/Projects/ROS/devel/lib/serial_example/serial_example_node: /usr/lib/x86_64-linux-gnu/libboost_thread.so.1.71.0
/home/cairlab/Projects/ROS/devel/lib/serial_example/serial_example_node: /usr/lib/x86_64-linux-gnu/libconsole_bridge.so.0.4
/home/cairlab/Projects/ROS/devel/lib/serial_example/serial_example_node: serial_example/CMakeFiles/serial_example_node.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/cairlab/Projects/ROS/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable /home/cairlab/Projects/ROS/devel/lib/serial_example/serial_example_node"
	cd /home/cairlab/Projects/ROS/build/serial_example && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/serial_example_node.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
serial_example/CMakeFiles/serial_example_node.dir/build: /home/cairlab/Projects/ROS/devel/lib/serial_example/serial_example_node

.PHONY : serial_example/CMakeFiles/serial_example_node.dir/build

serial_example/CMakeFiles/serial_example_node.dir/clean:
	cd /home/cairlab/Projects/ROS/build/serial_example && $(CMAKE_COMMAND) -P CMakeFiles/serial_example_node.dir/cmake_clean.cmake
.PHONY : serial_example/CMakeFiles/serial_example_node.dir/clean

serial_example/CMakeFiles/serial_example_node.dir/depend:
	cd /home/cairlab/Projects/ROS/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/cairlab/Projects/ROS/src /home/cairlab/Projects/ROS/src/serial_example /home/cairlab/Projects/ROS/build /home/cairlab/Projects/ROS/build/serial_example /home/cairlab/Projects/ROS/build/serial_example/CMakeFiles/serial_example_node.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : serial_example/CMakeFiles/serial_example_node.dir/depend


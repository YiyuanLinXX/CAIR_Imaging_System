cmake_minimum_required(VERSION 3.0.2)
project(gps_publisher)

## Compile as C++11, supported in ROS Kinetic and newer
# add_compile_options(-std=c++11)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  rospy
  roscpp
)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

catkin_package()

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)

set(SOURCES
    src/main.cpp
    src/mainwindow.cpp
)

add_executable(qt_gps_app ${SOURCES})
target_link_libraries(qt_gps_app Qt5::Widgets ${catkin_LIBRARIES})

find_library(UUID_LIB uuid)
if(UUID_LIB)
  message(STATUS "Found libuuid: ${UUID_LIB}")
  target_link_libraries(qt_gps_app ${UUID_LIB})
else()
  message(FATAL_ERROR "libuuid not found")
endif()

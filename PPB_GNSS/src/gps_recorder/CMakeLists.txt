cmake_minimum_required(VERSION 3.0.2)
project(gps_recorder)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  sensor_msgs
)

find_package(Boost REQUIRED COMPONENTS filesystem)


catkin_package(
  INCLUDE_DIRS include
)

include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}/include
  ${catkin_INCLUDE_DIRS}
  ${Boost_INCLUDE_DIRS}
)

add_executable(gps_recorder_node src/gps_recorder.cpp)

target_link_libraries(gps_recorder_node
  ${catkin_LIBRARIES}
  ${Boost_LIBRARIES}
)

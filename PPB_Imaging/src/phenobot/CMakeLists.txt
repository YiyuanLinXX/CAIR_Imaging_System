# %Tag(FULLTEXT)%
cmake_minimum_required(VERSION 3.10.2)
project(phenobot_camera)

#add_compile_options(-std=c++11)

#set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")
#set(CUDA_USE_STATIC_CUDA_RUNTIME OFF)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")
set(CUDA_USE_STATIC_CUDA_RUNTIME OFF)

SET(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})

## Find catkin and any catkin packages

find_package(OpenCV REQUIRED core highgui imgproc)
find_package(catkin REQUIRED COMPONENTS roscpp rospy std_msgs genmsg sensor_msgs image_transport cv_bridge serial) #cv_bridge
find_package(Boost REQUIRED filesystem system)


## Declare ROS messages and services
add_message_files(FILES Num.msg)
add_service_files(FILES AddTwoInts.srv)

## Generate added messages and services
generate_messages(DEPENDENCIES std_msgs)

## Declare a catkin package
catkin_package()


#for json
file(GLOB INCLUDE_FILES "include/json/*.h")
install(FILES ${INCLUDE_FILES} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/json)

## Build talker and listener
include_directories(include ${catkin_INCLUDE_DIRS})

include_directories(${Boost_INCLUDE_DIRS} )

include_directories("/opt/spinnaker/include")

link_directories(${Boost_LIBRARY_DIRS} "/usr/include/jsoncpp" -lb64) 

link_directories("/opt/spinnaker/lib")

#add_executable(my_subscriber src/my_subscriber.cpp)
#target_link_libraries(my_subscriber ${catkin_LIBRARIES} ${OpenCV_LIBS})
#add_dependencies(my_subscriber beginner_tutorials_generate_messages_cpp)

set(SRC src/singleCamera.cpp src/jetsonGPIO.cpp src/flirBFS.cpp src/paramListener.cpp)
set(SRC_MAIN src/main.cpp)

add_executable(main ${SRC_MAIN} ${SRC})
target_link_libraries(main -lpthread -lSpinnaker ${OpenCV_LIBS} ${Boost_LIBRARIES} ${catkin_LIBRARIES})




# %EndTag(FULLTEXT)%



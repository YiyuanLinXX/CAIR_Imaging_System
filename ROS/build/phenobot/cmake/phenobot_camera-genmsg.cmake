# generated from genmsg/cmake/pkg-genmsg.cmake.em

message(STATUS "phenobot_camera: 1 messages, 1 services")

set(MSG_I_FLAGS "-Iphenobot_camera:/home/cairlab/Projects/ROS/src/phenobot/msg;-Istd_msgs:/opt/ros/noetic/share/std_msgs/cmake/../msg")

# Find all generators
find_package(gencpp REQUIRED)
find_package(geneus REQUIRED)
find_package(genlisp REQUIRED)
find_package(gennodejs REQUIRED)
find_package(genpy REQUIRED)

add_custom_target(phenobot_camera_generate_messages ALL)

# verify that message/service dependencies have not changed since configure



get_filename_component(_filename "/home/cairlab/Projects/ROS/src/phenobot/msg/Num.msg" NAME_WE)
add_custom_target(_phenobot_camera_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "phenobot_camera" "/home/cairlab/Projects/ROS/src/phenobot/msg/Num.msg" ""
)

get_filename_component(_filename "/home/cairlab/Projects/ROS/src/phenobot/srv/AddTwoInts.srv" NAME_WE)
add_custom_target(_phenobot_camera_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "phenobot_camera" "/home/cairlab/Projects/ROS/src/phenobot/srv/AddTwoInts.srv" ""
)

#
#  langs = gencpp;geneus;genlisp;gennodejs;genpy
#

### Section generating for lang: gencpp
### Generating Messages
_generate_msg_cpp(phenobot_camera
  "/home/cairlab/Projects/ROS/src/phenobot/msg/Num.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/phenobot_camera
)

### Generating Services
_generate_srv_cpp(phenobot_camera
  "/home/cairlab/Projects/ROS/src/phenobot/srv/AddTwoInts.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/phenobot_camera
)

### Generating Module File
_generate_module_cpp(phenobot_camera
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/phenobot_camera
  "${ALL_GEN_OUTPUT_FILES_cpp}"
)

add_custom_target(phenobot_camera_generate_messages_cpp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_cpp}
)
add_dependencies(phenobot_camera_generate_messages phenobot_camera_generate_messages_cpp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/cairlab/Projects/ROS/src/phenobot/msg/Num.msg" NAME_WE)
add_dependencies(phenobot_camera_generate_messages_cpp _phenobot_camera_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/cairlab/Projects/ROS/src/phenobot/srv/AddTwoInts.srv" NAME_WE)
add_dependencies(phenobot_camera_generate_messages_cpp _phenobot_camera_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(phenobot_camera_gencpp)
add_dependencies(phenobot_camera_gencpp phenobot_camera_generate_messages_cpp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS phenobot_camera_generate_messages_cpp)

### Section generating for lang: geneus
### Generating Messages
_generate_msg_eus(phenobot_camera
  "/home/cairlab/Projects/ROS/src/phenobot/msg/Num.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/phenobot_camera
)

### Generating Services
_generate_srv_eus(phenobot_camera
  "/home/cairlab/Projects/ROS/src/phenobot/srv/AddTwoInts.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/phenobot_camera
)

### Generating Module File
_generate_module_eus(phenobot_camera
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/phenobot_camera
  "${ALL_GEN_OUTPUT_FILES_eus}"
)

add_custom_target(phenobot_camera_generate_messages_eus
  DEPENDS ${ALL_GEN_OUTPUT_FILES_eus}
)
add_dependencies(phenobot_camera_generate_messages phenobot_camera_generate_messages_eus)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/cairlab/Projects/ROS/src/phenobot/msg/Num.msg" NAME_WE)
add_dependencies(phenobot_camera_generate_messages_eus _phenobot_camera_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/cairlab/Projects/ROS/src/phenobot/srv/AddTwoInts.srv" NAME_WE)
add_dependencies(phenobot_camera_generate_messages_eus _phenobot_camera_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(phenobot_camera_geneus)
add_dependencies(phenobot_camera_geneus phenobot_camera_generate_messages_eus)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS phenobot_camera_generate_messages_eus)

### Section generating for lang: genlisp
### Generating Messages
_generate_msg_lisp(phenobot_camera
  "/home/cairlab/Projects/ROS/src/phenobot/msg/Num.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/phenobot_camera
)

### Generating Services
_generate_srv_lisp(phenobot_camera
  "/home/cairlab/Projects/ROS/src/phenobot/srv/AddTwoInts.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/phenobot_camera
)

### Generating Module File
_generate_module_lisp(phenobot_camera
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/phenobot_camera
  "${ALL_GEN_OUTPUT_FILES_lisp}"
)

add_custom_target(phenobot_camera_generate_messages_lisp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_lisp}
)
add_dependencies(phenobot_camera_generate_messages phenobot_camera_generate_messages_lisp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/cairlab/Projects/ROS/src/phenobot/msg/Num.msg" NAME_WE)
add_dependencies(phenobot_camera_generate_messages_lisp _phenobot_camera_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/cairlab/Projects/ROS/src/phenobot/srv/AddTwoInts.srv" NAME_WE)
add_dependencies(phenobot_camera_generate_messages_lisp _phenobot_camera_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(phenobot_camera_genlisp)
add_dependencies(phenobot_camera_genlisp phenobot_camera_generate_messages_lisp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS phenobot_camera_generate_messages_lisp)

### Section generating for lang: gennodejs
### Generating Messages
_generate_msg_nodejs(phenobot_camera
  "/home/cairlab/Projects/ROS/src/phenobot/msg/Num.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/phenobot_camera
)

### Generating Services
_generate_srv_nodejs(phenobot_camera
  "/home/cairlab/Projects/ROS/src/phenobot/srv/AddTwoInts.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/phenobot_camera
)

### Generating Module File
_generate_module_nodejs(phenobot_camera
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/phenobot_camera
  "${ALL_GEN_OUTPUT_FILES_nodejs}"
)

add_custom_target(phenobot_camera_generate_messages_nodejs
  DEPENDS ${ALL_GEN_OUTPUT_FILES_nodejs}
)
add_dependencies(phenobot_camera_generate_messages phenobot_camera_generate_messages_nodejs)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/cairlab/Projects/ROS/src/phenobot/msg/Num.msg" NAME_WE)
add_dependencies(phenobot_camera_generate_messages_nodejs _phenobot_camera_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/cairlab/Projects/ROS/src/phenobot/srv/AddTwoInts.srv" NAME_WE)
add_dependencies(phenobot_camera_generate_messages_nodejs _phenobot_camera_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(phenobot_camera_gennodejs)
add_dependencies(phenobot_camera_gennodejs phenobot_camera_generate_messages_nodejs)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS phenobot_camera_generate_messages_nodejs)

### Section generating for lang: genpy
### Generating Messages
_generate_msg_py(phenobot_camera
  "/home/cairlab/Projects/ROS/src/phenobot/msg/Num.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/phenobot_camera
)

### Generating Services
_generate_srv_py(phenobot_camera
  "/home/cairlab/Projects/ROS/src/phenobot/srv/AddTwoInts.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/phenobot_camera
)

### Generating Module File
_generate_module_py(phenobot_camera
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/phenobot_camera
  "${ALL_GEN_OUTPUT_FILES_py}"
)

add_custom_target(phenobot_camera_generate_messages_py
  DEPENDS ${ALL_GEN_OUTPUT_FILES_py}
)
add_dependencies(phenobot_camera_generate_messages phenobot_camera_generate_messages_py)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/cairlab/Projects/ROS/src/phenobot/msg/Num.msg" NAME_WE)
add_dependencies(phenobot_camera_generate_messages_py _phenobot_camera_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/cairlab/Projects/ROS/src/phenobot/srv/AddTwoInts.srv" NAME_WE)
add_dependencies(phenobot_camera_generate_messages_py _phenobot_camera_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(phenobot_camera_genpy)
add_dependencies(phenobot_camera_genpy phenobot_camera_generate_messages_py)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS phenobot_camera_generate_messages_py)



if(gencpp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/phenobot_camera)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/phenobot_camera
    DESTINATION ${gencpp_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_cpp)
  add_dependencies(phenobot_camera_generate_messages_cpp std_msgs_generate_messages_cpp)
endif()

if(geneus_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/phenobot_camera)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/phenobot_camera
    DESTINATION ${geneus_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_eus)
  add_dependencies(phenobot_camera_generate_messages_eus std_msgs_generate_messages_eus)
endif()

if(genlisp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/phenobot_camera)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/phenobot_camera
    DESTINATION ${genlisp_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_lisp)
  add_dependencies(phenobot_camera_generate_messages_lisp std_msgs_generate_messages_lisp)
endif()

if(gennodejs_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/phenobot_camera)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/phenobot_camera
    DESTINATION ${gennodejs_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_nodejs)
  add_dependencies(phenobot_camera_generate_messages_nodejs std_msgs_generate_messages_nodejs)
endif()

if(genpy_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/phenobot_camera)
  install(CODE "execute_process(COMMAND \"/usr/bin/python3\" -m compileall \"${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/phenobot_camera\")")
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/phenobot_camera
    DESTINATION ${genpy_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_py)
  add_dependencies(phenobot_camera_generate_messages_py std_msgs_generate_messages_py)
endif()

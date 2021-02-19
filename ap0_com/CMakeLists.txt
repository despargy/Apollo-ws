cmake_minimum_required(VERSION 3.0.2)
project(ap0_com)

## Compile as C++11, supported in ROS Kinetic and newer
# add_compile_options(-std=c++11)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  actionlib
  actionlib_msgs
  message_generation
  message_runtime
  move_base_msgs
  roscpp
  std_msgs
  ap_msgs
  tf2_ros
)

find_package(Boost REQUIRED COMPONENTS system)

## Generate actions in the 'action' folder
# add_action_files(
#   FILES
#   apMove.action
# )

generate_messages(
  DEPENDENCIES
  std_msgs  # Or other packages containing msgs
)

#add_message_files(FILES apollo.msg)
#add_service_files(FILES GetPermission.srv)



catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES ap0_com
   CATKIN_DEPENDS actionlib actionlib_msgs tf2_ros  message_runtime move_base_msgs roscpp std_msgs ap_msgs
#  DEPENDS system_lib
)

###########
## Build ##
###########

## Specify additional locations of header files
## Your package locations should be listed before other locations
include_directories(
 include
  ${catkin_INCLUDE_DIRS}
)



#add_executable(d_com
#  src/d_com.cpp
#)
#add_executable(service
#  src/service.cpp
#)

add_executable(client1
  src/client1.cpp
)

add_executable(service1
  src/service1.cpp
)

add_executable(apollo_ssrv
  src/apollo_ssrv.cpp
)
add_executable(apollo_master
  src/apollo_master.cpp
)

add_executable(apollo_ssrv_interupt
  src/apollo_ssrv_interupt.cpp
)
add_executable(apollo_master_interupt
  src/apollo_master_interupt.cpp
)

# add_executable(apollo_client_master
#  src/apollo_client_master.cpp
#)

#add_executable(service_inter
#  src/service_inter.cpp
#)

#add_dependencies(d_com ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
#target_link_libraries(d_com
#  ${catkin_LIBRARIES}
#)

add_dependencies(client1 ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(client1
  ${catkin_LIBRARIES}
)

add_dependencies(service1 ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(service1
  ${catkin_LIBRARIES}
)
add_dependencies(apollo_ssrv ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(apollo_ssrv
  ${catkin_LIBRARIES}
)
add_dependencies(apollo_master ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(apollo_master
  ${catkin_LIBRARIES}
)

add_dependencies(apollo_ssrv_interupt ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(apollo_ssrv_interupt
  ${catkin_LIBRARIES}
)
add_dependencies(apollo_master_interupt ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(apollo_master_interupt
  ${catkin_LIBRARIES}
)


#add_dependencies(apollo_client_master ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
#target_link_libraries(apollo_client_master
#  ${catkin_LIBRARIES}
#)

#add_dependencies(service_inter ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
#target_link_libraries(service_inter
#  ${catkin_LIBRARIES}
#)

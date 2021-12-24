cmake_minimum_required(VERSION 3.0.2)
project(carto_init)

add_compile_options(-std=c++11)

find_package(catkin REQUIRED COMPONENTS
  cartographer_ros_msgs
  roscpp
  rospy
  std_msgs
  geometry_msgs
  message_generation
  tf2
  tf2_ros
  tf2_geometry_msgs
)

# msg
# dynamic parameters

catkin_package(
  INCLUDE_DIRS # include/carto_init
  LIBRARIES CARTOINIT
  CATKIN_DEPENDS
  roscpp
  std_msgs
  geometry_msgs
  message_runtime
  cartographer_ros_msgs
  tf2
  tf2_ros
  DEPENDS
)

# 直接包含cartographer_ros
# add_service_files(
# FILES
# FinishTrajectory.srv
# StartTrajectory.srv
# )

include_directories(
  ${catkin_INCLUDE_DIRS}
  # ${PROJECT_SOURCE_DIR}
  ${PROJECT_SOURCE_DIR}/include
)

add_library(CARTOINIT SHARED
  src/carto_init.cc
)
target_link_libraries(CARTOINIT PUBLIC ${EXTERNAL_LIBS} ${catkin_LIBRARIES})
target_include_directories(CARTOINIT PUBLIC ${CMAKE_CURRENT_BINARY_DIR})

add_executable(${PROJECT_NAME}_node src/carto_init_node.cc)
target_link_libraries(${PROJECT_NAME}_node CARTOINIT ${catkin_LIBRARIES})

# --- install ---
install(TARGETS ${PROJECT_NAME}_node
  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)

install(
	FILES package.xml nodelet_micro.xml
	DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
)
install(
	DIRECTORY launch
	DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
)

install(TARGETS CARTOINIT
	ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
	LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
	RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)

# Install script for directory: /home/fyin/sim_env/src

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/home/fyin/sim_env/install")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  
      if (NOT EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}")
        file(MAKE_DIRECTORY "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}")
      endif()
      if (NOT EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/.catkin")
        file(WRITE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/.catkin" "")
      endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/home/fyin/sim_env/install/_setup_util.py")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/home/fyin/sim_env/install" TYPE PROGRAM FILES "/home/fyin/sim_env/build/catkin_generated/installspace/_setup_util.py")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/home/fyin/sim_env/install/env.sh")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/home/fyin/sim_env/install" TYPE PROGRAM FILES "/home/fyin/sim_env/build/catkin_generated/installspace/env.sh")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/home/fyin/sim_env/install/setup.bash;/home/fyin/sim_env/install/local_setup.bash")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/home/fyin/sim_env/install" TYPE FILE FILES
    "/home/fyin/sim_env/build/catkin_generated/installspace/setup.bash"
    "/home/fyin/sim_env/build/catkin_generated/installspace/local_setup.bash"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/home/fyin/sim_env/install/setup.sh;/home/fyin/sim_env/install/local_setup.sh")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/home/fyin/sim_env/install" TYPE FILE FILES
    "/home/fyin/sim_env/build/catkin_generated/installspace/setup.sh"
    "/home/fyin/sim_env/build/catkin_generated/installspace/local_setup.sh"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/home/fyin/sim_env/install/setup.zsh;/home/fyin/sim_env/install/local_setup.zsh")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/home/fyin/sim_env/install" TYPE FILE FILES
    "/home/fyin/sim_env/build/catkin_generated/installspace/setup.zsh"
    "/home/fyin/sim_env/build/catkin_generated/installspace/local_setup.zsh"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/home/fyin/sim_env/install/.rosinstall")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/home/fyin/sim_env/install" TYPE FILE FILES "/home/fyin/sim_env/build/catkin_generated/installspace/.rosinstall")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/home/fyin/sim_env/build/gtest/cmake_install.cmake")
  include("/home/fyin/sim_env/build/diff_wheeled_robot_bringup/cmake_install.cmake")
  include("/home/fyin/sim_env/build/diff_wheeled_robot_navigation/cmake_install.cmake")
  include("/home/fyin/sim_env/build/TEB/move_base_flex/move_base_flex/cmake_install.cmake")
  include("/home/fyin/sim_env/build/navigation/navigation/cmake_install.cmake")
  include("/home/fyin/sim_env/build/stage_controllers/cmake_install.cmake")
  include("/home/fyin/sim_env/build/TEB/move_base_flex/mbf_abstract_core/cmake_install.cmake")
  include("/home/fyin/sim_env/build/TEB/move_base_flex/mbf_msgs/cmake_install.cmake")
  include("/home/fyin/sim_env/build/velodyne_simulator/velodyne_description/cmake_install.cmake")
  include("/home/fyin/sim_env/build/velodyne_simulator/velodyne_simulator/cmake_install.cmake")
  include("/home/fyin/sim_env/build/mbot_navigation/mbot_navigation/cmake_install.cmake")
  include("/home/fyin/sim_env/build/mbot_navigation/mbot_teleop/cmake_install.cmake")
  include("/home/fyin/sim_env/build/navigation/map_server/cmake_install.cmake")
  include("/home/fyin/sim_env/build/diff_wheeled_robot_record/cmake_install.cmake")
  include("/home/fyin/sim_env/build/navigation/amcl/cmake_install.cmake")
  include("/home/fyin/sim_env/build/navigation/fake_localization/cmake_install.cmake")
  include("/home/fyin/sim_env/build/TEB/move_base_flex/mbf_utility/cmake_install.cmake")
  include("/home/fyin/sim_env/build/TEB/move_base_flex/mbf_abstract_nav/cmake_install.cmake")
  include("/home/fyin/sim_env/build/TEB/move_base_flex/mbf_simple_nav/cmake_install.cmake")
  include("/home/fyin/sim_env/build/pointcloud_to_laserscan/cmake_install.cmake")
  include("/home/fyin/sim_env/build/diff_wheeled_robot_follow/cmake_install.cmake")
  include("/home/fyin/sim_env/build/mbot_navigation/mbot_gazebo/cmake_install.cmake")
  include("/home/fyin/sim_env/build/velodyne_simulator/velodyne_gazebo_plugins/cmake_install.cmake")
  include("/home/fyin/sim_env/build/navigation/voxel_grid/cmake_install.cmake")
  include("/home/fyin/sim_env/build/navigation/costmap_2d/cmake_install.cmake")
  include("/home/fyin/sim_env/build/TEB/costmap_converter/cmake_install.cmake")
  include("/home/fyin/sim_env/build/navigation/nav_core/cmake_install.cmake")
  include("/home/fyin/sim_env/build/navigation/base_local_planner/cmake_install.cmake")
  include("/home/fyin/sim_env/build/navigation/carrot_planner/cmake_install.cmake")
  include("/home/fyin/sim_env/build/navigation/clear_costmap_recovery/cmake_install.cmake")
  include("/home/fyin/sim_env/build/navigation/dwa_local_planner/cmake_install.cmake")
  include("/home/fyin/sim_env/build/TEB/move_base_flex/mbf_costmap_core/cmake_install.cmake")
  include("/home/fyin/sim_env/build/TEB/move_base_flex/mbf_costmap_nav/cmake_install.cmake")
  include("/home/fyin/sim_env/build/navigation/move_slow_and_clear/cmake_install.cmake")
  include("/home/fyin/sim_env/build/navigation/navfn/cmake_install.cmake")
  include("/home/fyin/sim_env/build/navigation/global_planner/cmake_install.cmake")
  include("/home/fyin/sim_env/build/navigation/rotate_recovery/cmake_install.cmake")
  include("/home/fyin/sim_env/build/navigation/move_base/cmake_install.cmake")
  include("/home/fyin/sim_env/build/TEB/teb_local_planner/cmake_install.cmake")
  include("/home/fyin/sim_env/build/diff_wheeled_robot_control/cmake_install.cmake")
  include("/home/fyin/sim_env/build/diff_wheeled_robot_gazebo/cmake_install.cmake")
  include("/home/fyin/sim_env/build/mbot_navigation/mbot_description/cmake_install.cmake")

endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "/home/fyin/sim_env/build/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")

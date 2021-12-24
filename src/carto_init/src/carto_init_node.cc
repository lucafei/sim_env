/**
 * @file carto_init.cpp
 * @author Mario (nrj_robotics@163.com)
 * @brief carto_init的rosnode节点
 * @version 0.1
 * @date 2021-07-14
 *
 * @copyright Copyright Mario 2021
 *
 */

#include "carto_init.h"
#include <iostream>
#include <ros/ros.h>

int main(int argc, char **argv) {
  ros::init(argc, argv, "carto_init");
  thunder::carto_init::CartoInit carto_init("carto_init");
  ros::spin();
  return 0;
}
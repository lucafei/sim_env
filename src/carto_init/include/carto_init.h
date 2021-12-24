/**
 * @file carto_init.h
 * @author Mario (nrj_robotics@163.com)
 * @brief 手动给定cartographer初始定位
 * @version 0.1
 * @date 2021-07-15
 *
 * @copyright Copyright Mario 2021
 *
 */
#pragma once

#include <string>

#include <geometry_msgs/PointStamped.h>
#include <geometry_msgs/Pose.h>
#include <geometry_msgs/PoseStamped.h>
#include <geometry_msgs/PoseWithCovarianceStamped.h>
#include <ros/ros.h>
#include <tf2_geometry_msgs/tf2_geometry_msgs.h>
#include <tf2_ros/transform_listener.h>
// #include <geometry_msgs/PointStamped.h>
// #include <tf2_ros/message_filter.h>
// #include <message_filters/subscriber.h>

#include "cartographer_ros_msgs/FinishTrajectory.h"
#include "cartographer_ros_msgs/GetTrajectoryStates.h"
#include "cartographer_ros_msgs/StartTrajectory.h"
#include "cartographer_ros_msgs/StatusResponse.h"

namespace thunder {
namespace carto_init {

class CartoInit {
 public:
  /**
   * @brief Construct a new Carto Init object
   *
   * @param node_name
   */
  CartoInit(std::string node_name);
  ~CartoInit();
  //   CartoInit(const CartoInit &) = delete;
  //   void operator=(const CartoInit &) = delete;

 private:
  /**
   * @brief
   *
   * @param msg
   */
  void InitposeCallback(const geometry_msgs::PoseWithCovarianceStamped &msg);
  int GetCurrentID(const std::vector<int> &trajectory_id, const std::vector<int> &trajectory_state);

  // tf2_ros::TransformListener listener_;
  std::shared_ptr<tf2_ros::Buffer> buffer_;
  std::shared_ptr<tf2_ros::TransformListener> listener_;

  ros::NodeHandle nh_;
  ros::Subscriber init_pose_sub_;
  ros::ServiceClient finish_trajectory_client_;
  ros::ServiceClient start_trajectory_client_;
  ros::ServiceClient get_trajectory_client_;

  std::string carto_config_dir_;
  std::string carto_config_basename_;
};

}  // namespace carto_init
}  // namespace thunder

#include "carto_init.h"

namespace thunder {
namespace carto_init {

CartoInit::CartoInit(std::string node_name) : nh_(node_name) {
  buffer_.reset(new tf2_ros::Buffer());
  listener_.reset(new tf2_ros::TransformListener(*buffer_));
  nh_.getParam("carto_config_dir", carto_config_dir_);
  nh_.getParam("carto_config_basename", carto_config_basename_);
  init_pose_sub_ = nh_.subscribe("initialpose", 1, &CartoInit::InitposeCallback, this);
  // 连接carto
  finish_trajectory_client_ =
      // nh_.serviceClient<carto_init::FinishTrajectory>("finish_trajectory");
      nh_.serviceClient<cartographer_ros_msgs::FinishTrajectory>("finish_trajectory");
  start_trajectory_client_ = nh_.serviceClient<cartographer_ros_msgs::StartTrajectory>("start_trajectory");
  get_trajectory_client_ = nh_.serviceClient<cartographer_ros_msgs::GetTrajectoryStates>("get_trajectory_states");

  while (!ros::service::exists("finish_trajectory", 1) || !ros::service::exists("start_trajectory", 1)) {
    ROS_INFO("--- Carto_init wait for cartographer services ---");
    ros::service::waitForService("finish_trajectory", 1000000);
    ros::service::waitForService("start_trajectory", 1000000);
  }
  ROS_INFO_STREAM("client connected to" << finish_trajectory_client_.getService() << ", " << start_trajectory_client_.getService() << ", "
                                        << get_trajectory_client_.getService());
}

CartoInit::~CartoInit() {}

int CartoInit::GetCurrentID(const std::vector<int> &trajectory_id, const std::vector<int> &trajectory_state) {
  for (int i = 0; i < trajectory_id.size(); i++) {
    if (trajectory_state[i] == 0) {
      return trajectory_id[i];
    }
  }
  return -1;
}

void CartoInit::InitposeCallback(const geometry_msgs::PoseWithCovarianceStamped &msg) {
  // Get current trajecotry_id
  cartographer_ros_msgs::GetTrajectoryStates get_srv;
  // get_srv.request = "{}";
  if (!get_trajectory_client_.call(get_srv)) {
    ROS_WARN("carto_init get trajectory in error");
    return;
  }
  std::vector<int> trajectory_id(get_srv.response.trajectory_states.trajectory_id.begin(), get_srv.response.trajectory_states.trajectory_id.end());
  std::vector<int> trajectory_state(get_srv.response.trajectory_states.trajectory_state.begin(),
                                    get_srv.response.trajectory_states.trajectory_state.end());
  int id = GetCurrentID(trajectory_id, trajectory_state);
  if (id < 0) {
    ROS_WARN("No valid trajectory");
    return;
  }
  ROS_INFO_STREAM("Current Valid Trajecotry is " << id);

  // carto_init::FinishTrajectory finish_srv;
  cartographer_ros_msgs::FinishTrajectory finish_srv;
  finish_srv.request.trajectory_id = id;
  if (finish_trajectory_client_.call(finish_srv)) {
    ROS_INFO_STREAM("cartographer trajectory end: " << finish_srv.response.status.message);
  } else {
    ROS_WARN("carto_init ends trajectory in error");
    return;
  }

  geometry_msgs::PoseStamped initial_pose_origin;
  initial_pose_origin.pose = msg.pose.pose;
  initial_pose_origin.header.frame_id = "base_link";
  geometry_msgs::PoseStamped initial_pose;

  std::string target_frame = "laser_link";
  try {
    buffer_->transform(initial_pose_origin, initial_pose, target_frame);
  } catch (tf2::TransformException &ex) {
    ROS_WARN("Failure %s\n", ex.what());  // Print exception which was caught
  }

  cartographer_ros_msgs::StartTrajectory start_srv;
  start_srv.request.configuration_directory = carto_config_dir_;
  start_srv.request.configuration_basename = carto_config_basename_;
  start_srv.request.use_initial_pose = true;
  start_srv.request.initial_pose = initial_pose.pose;
  if (start_trajectory_client_.call(start_srv)) {
    ROS_INFO_STREAM("cartographer trajectory " << start_srv.response.trajectory_id << " start: " << start_srv.response.status.message);
  } else {
    ROS_WARN("carto_init starts trajectory in error");
    return;
  }
  // ROS_INFO("Successfully restart trajectory");
}

}  // namespace carto_init
}  // namespace thunder

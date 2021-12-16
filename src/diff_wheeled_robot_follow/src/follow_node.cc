/*
 * Read Record Path point from json
 */

#include "json.hpp"
#include <actionlib/client/simple_action_client.h>
#include <fstream>
#include <move_base_msgs/MoveBaseAction.h>
#include <ros/ros.h>

typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction>
    MoveBaseClient;
using json = nlohmann::json;

int main(int argc, char **argv) {

  ros::init(argc, argv, "thunder_follow");
  ros::NodeHandle n("thunder_follow");

  std::string json_path="./path.json";
  // if (!n.getParam("json_file_path", json_path))
  //   ROS_ERROR("Cannot get json_file_path");
  // else
  //   ROS_INFO_STREAM("LOAD path.json form " << json_path);

  // loop waiting for move_base
  MoveBaseClient ac("move_base", true);
  while (!ac.waitForServer(ros::Duration(10.0)) && ros::ok()) {
    ROS_INFO("Waiting for the move_base action server");
  }

  std::ifstream file(json_path);
  json json_data = json::parse(file);
  json::iterator json_it = json_data.begin();
  int json_index = 0;

  while(ros::ok()){

    move_base_msgs::MoveBaseGoal goal;
    goal.target_pose.header.frame_id = "map";
    goal.target_pose.pose.position.x = json_it.value()[0];
    goal.target_pose.pose.position.y = json_it.value()[1];
    goal.target_pose.pose.orientation.z = json_it.value()[5];
    goal.target_pose.pose.orientation.w = json_it.value()[6];

    ac.sendGoal(goal);
    ac.waitForResult();

    if (ac.getState() != actionlib::SimpleClientGoalState::SUCCEEDED)
      break;

    ROS_INFO_STREAM("Sending goal NO:" << json_index);

    json_it ++;
    json_index ++;
    if(json_it == json_data.end()){
      json_it = json_data.begin();
      json_index = 0;
    }

    ros::spinOnce();
  }
  ROS_ERROR("The base failed for some reason");
  return 0;
}

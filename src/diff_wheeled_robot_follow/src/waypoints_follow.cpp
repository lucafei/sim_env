#include <iostream>
#include "ros/ros.h"
#include <actionlib/client/simple_action_client.h>
#include <fstream>
#include <move_base_msgs/MoveBaseAction.h>
#include "json.hpp"
#include <string>
#include<cmath>
#include<vector>
#include <tf/transform_listener.h>
using namespace std;
using json = nlohmann::json;
typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

class PathReader
{
public:
    PathReader(string path_filename)
    {
        path_file.open(path_filename);
        json_data = json::parse(path_file);
    }
    vector<vector<float>> getPath()
    {
        vector<vector<float>> points;
        for( json::iterator json_it = json_data.begin();json_it!=json_data.end();json_it++)
        {
            vector<float> point;
            float x = json_it.value()[0];
            float y =json_it.value()[1];
            float z=json_it.value()[2];
            x/=10;
            y/=10;
            z/=10;
             point.emplace_back(x);
            point.emplace_back(y);
            point.emplace_back(z);
            point.emplace_back(json_it.value()[3]);
            point.emplace_back(json_it.value()[4]);
            point.emplace_back(json_it.value()[5]);
            point.emplace_back(json_it.value()[6]);
            points.emplace_back(point);
        }
        return points;
    }
private:
    ifstream path_file;
    json json_data;
};
PathReader pr("./path_E3.json");
class FollowPath
{
public:
    FollowPath(float dis_tolerance)
    {
        distance_tolerance = dis_tolerance;
        odom_frame_id="odom";
        base_frame_id="base_footprint"; //base_link
        frame_id="map";
    }

    void execute()
    {
        float distance = 10;
        auto waypoints =pr.getPath() ;
        auto size = waypoints.size();
        MoveBaseClient ac("move_base", true);
          while (!ac.waitForServer(ros::Duration(10.0)) && ros::ok()) {
    ROS_INFO("Waiting for the move_base action server");
  }
        for (int i = 0; i < size; i++)
        {
            move_base_msgs::MoveBaseGoal goal;
            goal.target_pose.header.frame_id = frame_id;
            goal.target_pose.pose.position.x = waypoints[i][0];
            goal.target_pose.pose.position.y = waypoints[i][1];
            goal.target_pose.pose.orientation.z = waypoints[i][5];
            goal.target_pose.pose.orientation.w = waypoints[i][6];
            ac.sendGoal(goal);
            ROS_INFO_STREAM("Sending goal NO: " << i);
            if (distance_tolerance <= 0)
            {
                ac.waitForResult();
                if (ac.getState() != actionlib::SimpleClientGoalState::SUCCEEDED)
                    break;
            }
            else
            {
                while (distance > distance_tolerance)
                {
                    ros::Time now = ros::Time::now();
                    listener.waitForTransform(odom_frame_id, base_frame_id,now, ros::Duration(4.0));
                    tf::StampedTransform transform;
                    listener.lookupTransform(odom_frame_id,base_frame_id,now,  transform);
                    distance = sqrt(pow(waypoints[i][0]-transform.getOrigin().getX(),2)+pow(waypoints[i][1]-transform.getOrigin().getY(),2));
                }
            }
        }
    }

private:
    float distance_tolerance;
   // MoveBaseClient ac("move_base", true);
   // PathReader pr("./path.json");
    tf::TransformListener listener;
    string odom_frame_id;
    string base_frame_id;
    string frame_id;
    //MoveBaseClient ac("move_base", true);
};

int main(int argc, char **argv)
{
    ros::init(argc, argv, "follow_path");
    ros::NodeHandle nh;
    FollowPath fp(0.5);
     fp.execute();
     return 0;
}
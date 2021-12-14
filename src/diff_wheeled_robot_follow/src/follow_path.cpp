#include <ros/ros.h>
#include <gazebo_msgs/SetModelState.h>
#include "json.hpp"
#include <iostream>
#include <fstream>
using namespace std;
using json=nlohmann::json;
int main(int argc, char **argv)
{
    ros::init(argc, argv, "gazebo_set_states_client");

    ros::NodeHandle n;
    ros::ServiceClient client = n.serviceClient<gazebo_msgs::SetModelState>("/gazebo/set_model_state");

    gazebo_msgs::SetModelState objstate;

    ifstream file("/home/fyin/sim_env/src/diff_wheeled_robot_follow/src/path_E3.json");
    json data = json::parse(file);
    json::iterator json_it = data.begin();
    ros::Rate r(2);
    while (json_it != data.end())
    {
        cout << "x:" << json_it.value()[0] << endl;
        cout << "y:" << json_it.value()[1] << endl;
        cout << "z:" << json_it.value()[2] << endl;
        cout << "orien x:" << json_it.value()[3] << endl;
        cout << "orien y:" << json_it.value()[4] << endl;
        cout << "orien z:" << json_it.value()[5] << endl;
        cout << "orien w:" << json_it.value()[6] << endl;
        objstate.request.model_state.model_name = "diff_wheeled_robot";
        float x=json_it.value()[0];x/=10.0;
        float y=json_it.value()[1];y/=10.0;
        float z=json_it.value()[2];z/=10.0;
        objstate.request.model_state.pose.position.x = x;
        objstate.request.model_state.pose.position.y = y;
        objstate.request.model_state.pose.position.z = z;
        objstate.request.model_state.pose.orientation.w = json_it.value()[6];
        objstate.request.model_state.pose.orientation.x = json_it.value()[3];
        objstate.request.model_state.pose.orientation.y = json_it.value()[4];
        objstate.request.model_state.pose.orientation.z = json_it.value()[5];
        objstate.request.model_state.twist.linear.x = 0.0;
        objstate.request.model_state.twist.linear.y = 0.0;
        objstate.request.model_state.twist.linear.z = 0.0;
        objstate.request.model_state.twist.angular.x = 0.0;
        objstate.request.model_state.twist.angular.y = 0.0;
        objstate.request.model_state.twist.angular.z = 0.0;
        objstate.request.model_state.reference_frame = "world";

        client.call(objstate);
        json_it++;
        r.sleep();
    }
}
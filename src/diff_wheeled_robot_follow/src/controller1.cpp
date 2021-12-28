
#include <ros/ros.h>
#include <ros/package.h>
#include <fstream>
#include <utility>
#include <vector>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>
#include <geometry_msgs/PointStamped.h>
#include <std_msgs/Bool.h>
#include <std_msgs/Int8.h>
#include <nav_msgs/Odometry.h>
#include <tf/transform_listener.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <math.h>
#include <string>
#include "json.hpp"
#include <boost/bind.hpp>
using namespace std;
using json = nlohmann::json;
typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

class WaypointsController1
{
public:
    WaypointsController1(string path_filename, ros::NodeHandle nh)
    {
        nh_ = nh;
        readPath(path_filename);
        frame_id = "map";
        odom_frame_id = "odom";
        base_frame_id = "base_footprint";
        controller_1_done.data = false;
        controller_2_done.data = false;
        end_on_controller_1=false;
        end_on_controller_2=false;
        goal_tolerance=1;
        controller2_status_sub = nh_.subscribe<std_msgs::Bool>("/controller2_done", 1000, boost::bind(&WaypointsController1::controller2_callback, this, _1));
        controller1_status_pub = nh_.advertise<std_msgs::Bool>("/controller1_done", 1000);
    }
    void readPath(string path_filename)
    {
        ifstream path_file;
        json json_data;
        path_file.open(path_filename);
        json_data = json::parse(path_file);
        vector<vector<float>> points;
        for (json::iterator json_it = json_data.begin(); json_it != json_data.end(); json_it++)
        {
            vector<float> point;
            float x = json_it.value()[0];
            float y = json_it.value()[1];
            float z = json_it.value()[2];
            // x/=10;
            // y/=10;
            // z/=10;
            point.emplace_back(x);
            point.emplace_back(y);
            point.emplace_back(z);
            point.emplace_back(json_it.value()[3]);
            point.emplace_back(json_it.value()[4]);
            point.emplace_back(json_it.value()[5]);
            point.emplace_back(json_it.value()[6]);
            points.emplace_back(point);
        }
        path = points;
    }
    void controller2_callback(const std_msgs::Bool::ConstPtr &msg)
    {
        if (msg->data == true)
        {
            controller_2_done.data = true;
        }
        else
        {
            controller_2_done.data = false;
        }
    }
    void execute()
    {
        MoveBaseClient ac1("/controller_1/move_base",true);
        int wait_count = 0;
        while (!ac1.waitForServer(ros::Duration(5.0)))
        {
            wait_count++;
            if (wait_count > 3)
            {
                ROS_ERROR("move_base action server did not come up, killing waypoint node...");
                ros::shutdown();
                return;
            }
            ROS_INFO("Waiting for the move_base action server 1 to come up");
        }

        int s = path.size();
        // Iterate through vector of waypoints for setting goals
        move_base_msgs::MoveBaseGoal next_goal;
        for (int iter = 0; iter < s; iter++)
        {
            //set next goal if not at last waypoint
            if (iter < (s - 2)) // this means that neither controller 1 or controller 2 are on the last waypoint so continue incrementing iter by 2
            {
                iter++;
            }
            else if (iter == (s - 2)) // this means that controller 1 is on the second last point so increment iter once more and shutdown after controller 2 is done
            {
                end_on_controller_1 = false;
                iter++;
            }
            else if (iter == (s - 1)) // this means that controller 1 is on its last waypoint and controller 2 should wait for controller 1 to shutdown
            {
                end_on_controller_1 = true;
            }
            else
            {
                ROS_ERROR("Controller 2: Error with waypoint vector iterator.");
                ros::shutdown();
            }

            next_goal.target_pose.header.frame_id = frame_id;
            next_goal.target_pose.pose.position.x = path[iter][0];
            next_goal.target_pose.pose.position.y = path[iter][1];
            next_goal.target_pose.pose.orientation.z = path[iter][5];
            next_goal.target_pose.pose.orientation.w = path[iter][6];

            if (iter == 1)
            {
                std::cout<<"keep going"<<std::endl;
                // keep going
            }
            else
            {
                while (controller_2_done.data == false)
                {
                    ros::spinOnce();
                    // wait
                }
                ROS_INFO("Controller 1: Received start signal from Controller 2");
                controller_2_done.data = false;
            }
            move_base_msgs::MoveBaseGoal goal = next_goal;
            ROS_INFO("Controller 1: Sending goal");
            ac1.sendGoal(goal); //push current goal to move_base node
            std::cout<<"have already sent goal"<<std::endl;
            if (end_on_controller_1 == false) // if this is the last point then we want to skip this step
            {
                waitForReachGoal(next_goal.target_pose.pose.position.x, next_goal.target_pose.pose.position.y, goal_tolerance);
                //   ROS_INFO("Controller 1: Sending start command to controller 2");
                controller_1_done.data = true; // once done waiting, publish that this controller is done, and to switch to the next
                controller1_status_pub.publish(controller_1_done);
                std::cout<<"published controller_1_done: "<<controller_1_done<<std::endl;
                controller_1_done.data = false; //reset
            }
            else //if on last waypoint, wait for it to acheive its goal
            {
                // ROS_ERROR("Controller 1: Waiting for result");
                ac1.waitForResult();
                // ROS_ERROR("Controller 1: have result");
                //controller_1_done.data = true; // once done waiting, publish that this controller is done, and to switch to the next
                //pub_controller_1_done.publish(controller_1_done);

                //ROS_INFO("Husky has reached all of its goals!!!\n);

                ROS_INFO("Ending controller 1 node...");
                ros::shutdown();
            }

        } // End for loop iterating through waypoint vector

        if (end_on_controller_1 == false)
        {
        }

        ROS_INFO("Ending controller 2 node...");
        ros::shutdown();
    }
    void waitForReachGoal(float x, float y, float tolerance)
    {
        float distance = 10;
        float distance_tolerance = tolerance;
        listener.waitForTransform(odom_frame_id, base_frame_id, ros::Time(), ros::Duration(4.0));
        while (distance > distance_tolerance)
        {
            ros::Time now = ros::Time::now();
            listener.waitForTransform(odom_frame_id, base_frame_id, now, ros::Duration(4.0));
            tf::StampedTransform transform;
            listener.lookupTransform(odom_frame_id, base_frame_id, now, transform);
            //std::cout<<"x:"<<transform.getOrigin().getX()<<"y:"<<transform.getOrigin().getY()<<std::endl;
            distance = sqrt(pow(x - transform.getOrigin().getX(), 2) + pow(y - transform.getOrigin().getY(), 2));
        }
        std::cout<<"exit from function waitForReachGoal"<<std::endl;
        distance = 10;
    }

private:
    vector<vector<float>> path;
    string frame_id;
    string odom_frame_id;
    string base_frame_id;
    ros::Subscriber controller2_status_sub;
    ros::Publisher controller1_status_pub;
    ros::NodeHandle nh_;
    tf::TransformListener listener;
    std_msgs::Bool controller_1_done;
    float goal_tolerance;
    std_msgs::Bool controller_2_done;
    bool end_on_controller_1;
    bool end_on_controller_2;
};

int main(int argc, char** argv)
{

    ros::init(argc, argv, "waypoint_1"); //initiate node called gps_waypoint
    ros::NodeHandle n;
    ROS_INFO("Initiated waypoint node 1");
    WaypointsController1 wc1("./path.json",n);
    wc1.execute();
    //ros::spin();
    return 0;
}
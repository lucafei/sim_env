#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <actionlib/client/simple_action_client.h>
#include <std_msgs/Bool.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>
#include <boost/bind.hpp>
#include <string>
using namespace std;
typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;
// MoveBaseClient ac1("move_base", true);
// MoveBaseClient ac2("move_base", true);
class ControllerSwitcher
{
public:
    ControllerSwitcher(int argc, char **argv, string name)
    {
        ros::init(argc, argv, name);
        nh_ptr = new ros::NodeHandle();
        vel1_empty = true;
        vel2_empty = true;
        controller_1_done = false;
        controller_2_done = false;
        controller_num = 1;
        current_vel = 1;
        cmd_vel1_sub = nh_ptr->subscribe<geometry_msgs::Twist>("/cmd_vel1", 1000, boost::bind(&ControllerSwitcher::cmd_vel1_callback, this, _1));
        cmd_vel2_sub = nh_ptr->subscribe<geometry_msgs::Twist>("/cmd_vel2", 1000, boost::bind(&ControllerSwitcher::cmd_vel2_callback, this, _1));
        controller1_sub = nh_ptr->subscribe<std_msgs::Bool>("/controller1_done", 1000, boost::bind(&ControllerSwitcher::controller1_callback, this, _1));
        controller2_sub = nh_ptr->subscribe<std_msgs::Bool>("/controller2_done", 1000, boost::bind(&ControllerSwitcher::controller2_callback, this, _1));
        vel_pub = nh_ptr->advertise<geometry_msgs::Twist>("/cmd_vel", 1000);
    }

    void cmd_vel1_callback(const geometry_msgs::Twist::ConstPtr &msg1)
    {
        cmd_vel1.linear.x = msg1->linear.x;
        cmd_vel1.linear.y = msg1->linear.y;
        cmd_vel1.angular.z = msg1->angular.z;
        if (msg1->linear.x == 0 && msg1->angular.z == 0)
        {
            this->vel1_empty = true;
        }
        else
        {
            this->vel1_empty = false;
        }
    }
    void cmd_vel2_callback(const geometry_msgs::Twist::ConstPtr &msg2)
    {
        cmd_vel2.linear.x = msg2->linear.x;
        cmd_vel2.linear.y = msg2->linear.y;
        cmd_vel2.angular.z = msg2->angular.z;
        if (msg2->linear.x == 0 && msg2->angular.z == 0)
        {
            this->vel2_empty = true;
        }
        else
        {
            this->vel2_empty = false;
        }
    }
    void controller1_callback(const std_msgs::Bool::ConstPtr &msg3)
    {
        if (msg3->data == true)
        {
            controller_1_done = true;
            controller_num = 1;
        }
        else
        {
            controller_1_done = false;
        }
    }
    void controller2_callback(const std_msgs::Bool::ConstPtr &msg4)
    {
        if (msg4->data == true)
        {
            controller_2_done = true;
            controller_num = 2;
        }
        else
        {
            controller_2_done = false;
        }
    }
    void execute()
    {
        MoveBaseClient ac1("/controller_1/move_base", true);
        MoveBaseClient ac2("/controller_2/move_base", true);
        while (ros::ok())
        {
            ros::spinOnce();
            // check which velocity should be published
            if (current_vel == 1 && controller_num == 2 && vel2_empty == false)
            {
                // this means the second move_base has started spitting our commands so let's switch
                current_vel = 2;
                ROS_INFO("Switching vel cmds from controller 1 to 2");
                ROS_INFO("Canceling controller 1's current goal");
                //ac1.cancelAllGoals();

            } // else, stay with 1

            else if (current_vel == 2 && controller_num == 1 && vel1_empty == false)
            {
                // this means 2 was publishing but then 1 started publishing again so switch back to 1
                current_vel = 1;
                ROS_INFO("Switching vel cmds from controller 2 to 1");
                ROS_INFO("Canceling controller 2's current goal");
                //ac2.cancelAllGoals();

            } // else stay with 2

            // Publish correct velocity
            if (current_vel == 1)
            {
                vel_pub.publish(cmd_vel1);
            }

            else if (current_vel == 2)
            {
                vel_pub.publish(cmd_vel2);
            }
            //rate.sleep();
        }
    }

private:
    ros::NodeHandle *nh_ptr;

    ros::Subscriber cmd_vel1_sub;
    ros::Subscriber cmd_vel2_sub;
    ros::Subscriber controller1_sub;
    ros::Subscriber controller2_sub;
    ros::Publisher vel_pub;
    geometry_msgs::Twist cmd_vel1;
    geometry_msgs::Twist cmd_vel2;
    int controller_num;
    int current_vel;
    bool vel1_empty;
    bool vel2_empty;
    bool controller_1_done;
    bool controller_2_done;
};

int main(int argc, char **argv)
{

    // ros::init(argc, argv, "controller_switcher"); //initiate node called gps_waypoint
    // ros::NodeHandle n;
    ControllerSwitcher cs(argc, argv, "controller_switcher");
    cs.execute();
    ros::spin();
    return 0;
}
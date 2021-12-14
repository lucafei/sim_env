#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include <gazebo_msgs/ModelStates.h>
#include<iostream>
class Visualizer
{
private:
    ros::NodeHandle nh_;
    ros::Publisher marker_pub;
    ros::Subscriber model_states;
    int count;

public:
    Visualizer(ros::NodeHandle nh)
    {
        nh_ = nh;
        marker_pub = nh_.advertise<visualization_msgs::Marker>("/visualization_marker", 1);
        model_states = nh_.subscribe("/gazebo/model_states", 1, &Visualizer::ModelStatesCallback,this);
        count = 0;
    }
    void ModelStatesCallback(const gazebo_msgs::ModelStates &msg)
    {
        ros::Rate r(1);
        std::cout<<"enter callback function"<<std::endl;
        visualization_msgs::Marker marker;
        uint32_t shape = visualization_msgs::Marker::SPHERE;
        marker.header.frame_id = "/my_frame";
        marker.header.stamp = ros::Time::now();

        marker.ns = "sphere";
        marker.id = count;

        marker.type = shape;

        marker.action = visualization_msgs::Marker::ADD;

        marker.pose.position.x = msg.pose[1].position.x;
        marker.pose.position.y = msg.pose[1].position.y;
        marker.pose.position.z = msg.pose[1].position.z;
        marker.pose.orientation.x = msg.pose[1].orientation.x;
        marker.pose.orientation.y = msg.pose[1].orientation.y;
        marker.pose.orientation.z = msg.pose[1].orientation.z;
        marker.pose.orientation.w = msg.pose[1].orientation.w;

        marker.scale.x = 0.05;
        marker.scale.y = 0.05;
       marker.scale.z = 0.05;

        marker.color.r = 0.0f;
        marker.color.g = 1.0f;
        marker.color.b = 0.0f;
        marker.color.a = 1.0;
        std::cout<<"marker x: "<< marker.pose.position.x<<std::endl;
        std::cout<<"marker y: "<<marker.pose.position.y<<std::endl;
        std::cout<<"marker z: "<<marker.pose.position.z<<std::endl;
        marker.lifetime = ros::Duration(0);

        // while (marker_pub.getNumSubscribers() < 1)
        // {
        //     if (!ros::ok())
        //     {
        //         return;
        //     }
        //     ROS_WARN_ONCE("Please create a subscriber to the marker");
        // }
        marker_pub.publish(marker);
        count++;
        r.sleep();
    }
};
int main(int argc, char **argv)
{
    ros::init(argc, argv, "vis_path");
    ros::NodeHandle n("vis_path");
    Visualizer vs(n);
    ros::spin();
}


// #include <ros/ros.h>
// #include <visualization_msgs/Marker.h>

// int main( int argc, char** argv )
// {
//   ros::init(argc, argv, "basic_shapes");
//   ros::NodeHandle n;
//   ros::Rate r(1);
//   ros::Publisher marker_pub = n.advertise<visualization_msgs::Marker>("/visualization_marker", 1);

//   // Set our initial shape type to be a cube
//   uint32_t shape = visualization_msgs::Marker::CUBE;

//   while (ros::ok())
//   {
//     visualization_msgs::Marker marker;
//     // Set the frame ID and timestamp.  See the TF tutorials for information on these.
//     marker.header.frame_id = "/my_frame";
//     marker.header.stamp = ros::Time::now();

//     // Set the namespace and id for this marker.  This serves to create a unique ID
//     // Any marker sent with the same namespace and id will overwrite the old one
//     marker.ns = "basic_shapes";
//     marker.id = 0;

//     // Set the marker type.  Initially this is CUBE, and cycles between that and SPHERE, ARROW, and CYLINDER
//     marker.type = shape;

//     // Set the marker action.  Options are ADD, DELETE, and new in ROS Indigo: 3 (DELETEALL)
//     marker.action = visualization_msgs::Marker::ADD;

//     // Set the pose of the marker.  This is a full 6DOF pose relative to the frame/time specified in the header
//     marker.pose.position.x = 0;
//     marker.pose.position.y = 0;
//     marker.pose.position.z = 0;
//     marker.pose.orientation.x = 0.0;
//     marker.pose.orientation.y = 0.0;
//     marker.pose.orientation.z = 0.0;
//     marker.pose.orientation.w = 1.0;

//     // Set the scale of the marker -- 1x1x1 here means 1m on a side
//     marker.scale.x = 1.0;
//     marker.scale.y = 1.0;
//     marker.scale.z = 1.0;

//     // Set the color -- be sure to set alpha to something non-zero!
//     marker.color.r = 0.0f;
//     marker.color.g = 1.0f;
//     marker.color.b = 0.0f;
//     marker.color.a = 1.0;

//     marker.lifetime = ros::Duration();

//     // Publish the marker
//     // while (marker_pub.getNumSubscribers() < 1)
//     // {
//     //   if (!ros::ok())
//     //   {
//     //     return 0;
//     //   }
//     //   ROS_WARN_ONCE("Please create a subscriber to the marker");
//     //   sleep(1);
//     // }
//     marker_pub.publish(marker);

//     // Cycle between different shapes
//     switch (shape)
//     {
//     case visualization_msgs::Marker::CUBE:
//       shape = visualization_msgs::Marker::SPHERE;
//       break;
//     case visualization_msgs::Marker::SPHERE:
//       shape = visualization_msgs::Marker::ARROW;
//       break;
//     case visualization_msgs::Marker::ARROW:
//       shape = visualization_msgs::Marker::CYLINDER;
//       break;
//     case visualization_msgs::Marker::CYLINDER:
//       shape = visualization_msgs::Marker::CUBE;
//       break;
//     }

//     r.sleep();
//   }
// }
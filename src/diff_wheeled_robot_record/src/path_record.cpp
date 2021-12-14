#include <gazebo_msgs/ModelStates.h>
#include "json.h"
#include <fstream>
#include <iostream>
#include <vector>
#include "ros/ros.h"
#include <thread>
using namespace std;

using json = nlohmann::json;

class PathRecorder
{
public:
    PathRecorder(ros::NodeHandle nh)
    {
        nh_ = nh;
        state_sub = nh_.subscribe("/gazebo/model_states", 1, &PathRecorder::ModelStatesCallback,this);
       
        tf_json_.reset(new json());
    }
    void ModelStatesCallback(const gazebo_msgs::ModelStates &msg)
    {
        ros::Rate r(0.2);

        // int modelCount = msg.name.size();

        // for (int modelInd = 0; modelInd < modelCount; ++modelInd)
        // {
        //     if (msg.name[modelInd] == "diff_wheeled_robot")
        transform_vector.emplace_back(msg.pose[1].position.x);
        transform_vector.emplace_back(msg.pose[1].position.y);
        transform_vector.emplace_back(msg.pose[1].position.z);
        transform_vector.emplace_back(msg.pose[1].orientation.x);
        transform_vector.emplace_back(msg.pose[1].orientation.y);
        transform_vector.emplace_back(msg.pose[1].orientation.z);
        transform_vector.emplace_back(msg.pose[1].orientation.w);
        tf_json_->emplace_back(transform_vector);
        file.open("./test.json");
        file << tf_json_->dump(4) << std::endl;
        file.close();
        transform_vector.clear();
        ROS_INFO_STREAM("Write to " << "./test.json");
        //    break;
        // }
        r.sleep();
    }

private:
    vector<double> transform_vector;
    ofstream file;
    std::unique_ptr<json> tf_json_;
    ros::Subscriber state_sub;
    ros::NodeHandle nh_;
};

int main(int argc, char **argv)
{
    std::unique_ptr<std::thread> record_run_thread_ptr_;
    ros::init(argc, argv, "pathrecoder");
    ros::NodeHandle nh("path_recoder");
    PathRecorder pr(nh);
    // std::unique_ptr<std::thread> record_run_thread_ptr_ =
    // ros::Subscriber state_sub = nh.subscribe("/gazebo/model_states", 1, &ModelStatesCallback);
    // std::cout<<"size of transform vector"<<transform_vector.size()<<std::endl;

    ros::spin();
}
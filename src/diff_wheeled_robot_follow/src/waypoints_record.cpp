
#include <unistd.h>

#include "json.hpp"
#include <string>
#include <ros/ros.h>
#include <thread>
#include <actionlib/server/simple_action_server.h>
#include <tf/transform_listener.h>
#include <mutex>
#include <fstream>
#include <unistd.h>
#include <string>
using json = nlohmann::json;
class PathRecorderSimple
{
public:
    PathRecorderSimple(std::string json_path)
        : json_path_(json_path), nh_("~")
    {

        ROS_INFO("Start Listening tf and save base_link -> map");
        tf_json_.reset(new json());
        record_run_thread_ptr_.reset(new std::thread(&PathRecorderSimple::Run, this));
        record_run_thread_ptr_->join();
    }

    void Run()
    {
        ros::Rate r(0.2); // 5s 记录一次, TODO(mario): cartographer 开了的话这个没用
        while (ros::ok())
        {
            ROS_INFO("START");
            bool tf_ok_flag = true;

            // 读取transform
            tf::StampedTransform transform;
            try
            {
                listener_.lookupTransform("map", "base_link", ros::Time(0), transform);
            }
            catch (tf::TransformException ex)
            {
                ROS_WARN("%s", ex.what());
                tf_ok_flag = false;
            }

            if (tf_ok_flag)
            {
                ROS_INFO("Receive tf from base_link to laser_link");
                std::vector<float> transform_vector;
                transform_vector.emplace_back(transform.getOrigin().x());
                transform_vector.emplace_back(transform.getOrigin().y());
                transform_vector.emplace_back(transform.getOrigin().z());
                transform_vector.emplace_back(transform.getRotation().getX());
                transform_vector.emplace_back(transform.getRotation().getY());
                transform_vector.emplace_back(transform.getRotation().getZ());
                transform_vector.emplace_back(transform.getRotation().getW());

                tf_json_->emplace_back(transform_vector);
                // 写入文件,append形式
                std::ofstream file;
                file.open(json_path_);
                // file.open("/home/mario/tmp/path.json");
                /* file.open("/home/mario/tmp/path.json"); */
                file << tf_json_->dump(4) << std::endl;
                file.close();
                ROS_INFO_STREAM("Write to " << json_path_);
            }
            // sleep(1);
            r.sleep();
            // ros::Duration(1).sleep();
            // ros::spinOnce();
        }
    }

private:
    std::unique_ptr<std::thread> record_run_thread_ptr_;
    ros::NodeHandle nh_;
    tf::TransformListener listener_;
    std::unique_ptr<json> tf_json_; // 数据保存
    std::string json_path_;
};
int main(int argc, char **argv)
{

    ros::init(argc, argv, "thunder_simple_record");

    ros::NodeHandle n("thunder_record");
    // std::string json_path;
    // if (!n.getParam("json_file_path", json_path))
    //     ROS_ERROR("Cannot get json_file_path");
    // else
    //     ROS_INFO_STREAM("Write to " << json_path);

    PathRecorderSimple recorder_simple("./path.json");
    /* ros::spin(); */

    return 0;
}

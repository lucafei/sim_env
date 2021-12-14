#include <termios.h>
#include <signal.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/poll.h>
#include <boost/thread/thread.hpp>
#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include<std_msgs/Float32MultiArray.h>
#define KEYCODE_W 0x77
#define KEYCODE_A 0x61
#define KEYCODE_S 0x73
#define KEYCODE_D 0x64
#define KEYCODE_A_CAP 0x41
#define KEYCODE_D_CAP 0x44
#define KEYCODE_S_CAP 0x53
#define KEYCODE_W_CAP 0x57
class SmartCarKeyboardTeleopNode
{
private:
    
    geometry_msgs::Twist cmdvel_;
    ros::NodeHandle n_;
    ros::Publisher pub_;
public:
double steeringangle;
    SmartCarKeyboardTeleopNode()
    {
        pub_ = n_.advertise<std_msgs::Float32MultiArray>("/thunder_micro/steeringwheel", 1);
        ros::NodeHandle n_private("~");
    }

    ~SmartCarKeyboardTeleopNode() {}
    void keyboardLoop();
    // void stopRobot()
    // {
    //     cmdvel_.linear.x = 0.0;
    //     cmdvel_.angular.z = 0.0;
    //     pub_.publish(cmdvel_);
    // }
};

SmartCarKeyboardTeleopNode *tbk;
int kfd = 0;
struct termios cooked, raw;
bool done;
int main(int argc, char **argv)
{
    ros::init(argc, argv, "tbk", ros::init_options::AnonymousName | ros::init_options::NoSigintHandler);
    SmartCarKeyboardTeleopNode tbk;
    boost::thread t = boost::thread(boost::bind(&SmartCarKeyboardTeleopNode::keyboardLoop, &tbk));
    ros::spin();
    t.interrupt();
    t.join();
   // tbk.stopRobot();
    tcsetattr(kfd, TCSANOW, &cooked);
    return (0);
}

void SmartCarKeyboardTeleopNode::keyboardLoop()

{

    char c;
    bool dirty = false;
    // get the console in raw mode

    tcgetattr(kfd, &cooked);
    memcpy(&raw, &cooked, sizeof(struct termios));
    raw.c_lflag &= ~(ICANON | ECHO);
    raw.c_cc[VEOL] = 1;
    raw.c_cc[VEOF] = 2;
    tcsetattr(kfd, TCSANOW, &raw);
    puts("Reading from keyboard");
    puts("Use WS keys to control the robot");
    struct pollfd ufd;
    ufd.fd = kfd;
    ufd.events = POLLIN;
    for (;;)
    {
        boost::this_thread::interruption_point();
        // get the next event from the keyboard
        int num;
        if ((num = poll(&ufd, 1, 250)) < 0)
        {
            perror("poll():");
            return;
        }
        else if (num > 0)
        {
            if (read(kfd, &c, 1) < 0)
            {
                perror("read():");
                return;
            }
        }
        else
        {
            if (dirty == true)
            {
                //stopRobot();
                dirty = false;
            }
            continue;
        }
        switch (c)
        {
        case KEYCODE_W:
            steeringangle+=1;
            dirty = true;
            break;
        case KEYCODE_S:
            steeringangle -= 1;
            dirty = true;
            break;
        default:
            steeringangle=0;
            dirty = false;
        }
        std_msgs::Float32MultiArray msg; 
        msg.data.emplace_back(0); //模拟自动驾驶flag
        msg.data.emplace_back(steeringangle);
        std::cout<<"sending steeringangle "<<steeringangle<<std::endl;
        pub_.publish(msg);
    }
}
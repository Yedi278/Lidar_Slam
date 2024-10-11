#include "ros/ros.h"
#include "std_msgs/String.h"
#include "ros/console.h"

#include "tcp_receive.h"

#define ROBOT_IP "192.168.1.169"
#define ROBOT_PORT 1234

int main(int argc, char **argv)
{
    ros::init(argc, argv, "Bohr_receive");
    ros::NodeHandle nh;

    ros::Publisher chatter_pub = nh.advertise<std_msgs::String>("chatter", 1000);
    ros::Rate loop_rate(10);

    int sockfd = connect_tcp(ROBOT_IP, ROBOT_PORT);

    while (ros::ok())
    {
        std_msgs::String msg;
        msg.data = "Hello, world";
        chatter_pub.publish(msg);

        ros::spinOnce();
        loop_rate.sleep();
    }

    return 0;
}
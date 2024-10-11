#include "ros/ros.h"
#include "std_msgs/String.h"
#include "ros/console.h"

#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

#define ROBOT_IP "10.253.145.97"
#define ROBOT_PORT 1234

int connect_tcp(const char *ip, int port)
{
    int sockfd;
    struct sockaddr_in serv_addr;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        ROS_ERROR("ERROR opening socket");
        return -1;
    }
    ROS_INFO_STREAM("Socket created");

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(ROBOT_PORT);
    // serv_addr.sin_addr.s_addr = ;
    inet_aton(ROBOT_IP, &serv_addr.sin_addr);

    if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) > 0 )
    {
        ROS_ERROR("ERROR connecting");
        return -1;
    }
    ROS_INFO_STREAM("Connected to " << ROBOT_IP << ":"<< ROBOT_PORT);

    char buffer[20];
    while(1){
        int n = read(sockfd, buffer, sizeof(buffer));
        if (n < 0)
        {
            ROS_ERROR("ERROR reading from socket");
            return -1;
        }
        if(n > 0){
            ROS_INFO_STREAM(buffer);
        }
    }



    return sockfd;
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "tcp_receive_node");
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
#include "ros/ros.h"
#include "sensor_msgs/LaserScan.h"

int main(int argc, char** argv){

    ros::init(argc, argv, "lidar_pub_node");
    ros::NodeHandle nh;

    ros::Publisher lidar_pub = nh.advertise<sensor_msgs::LaserScan>("lidar_scan", 1000);
    ros::Rate loop_rate(10);

    while(ros::ok()){
        
        
    }    

    return 0;
}
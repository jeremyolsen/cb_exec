#include <ros/ros.h>
#include "cb_exec/cb_exec.h"

int main(int argc, char **argv)
{
    ROS_INFO("Starting cb_exec ROS node...");

    ros::init(argc, argv, "cb_exec");
    ros::NodeHandle nh("~");

    cb_exec::CBExec controller;
    if(!controller.init(nh))
    {
        ROS_ERROR("Could not initialize CBExec node!");
        return -1;
    }

    if(!controller.arm())
    {
        ROS_ERROR("Could not arm Navio/FCU!");
        return -1;
    }

    // Loop and process commands/state
    controller.spin();

    return 0;
}
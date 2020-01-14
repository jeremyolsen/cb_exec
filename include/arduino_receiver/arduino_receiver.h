#include "ros/ros.h"
#include <serial/serial.h>
#include <std_msgs/String.h>
#include <std_msgs/Empty.h>
#include <regex>
#include <vector>
#include <geometry_msgs/Vector3.h>
#include <tf/transform_broadcaster.h>
#include <nav_msgs/Odometry.h>

serial::Serial ser;

class ArduinoReceiver
{

        private:
                ros::NodeHandle nh_;  //Node handle
                // ros::Timer timer;

        public: 
                ArduinoReceiver(ros::NodeHandle *nodehandle);
                // void timerCallback(const ros::TimerEvent&);
                ~ArduinoReceiver();
                
};
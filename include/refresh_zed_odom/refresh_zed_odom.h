
#include "ros/ros.h"


class RefreshZedOdom
{

        private:
                ros::NodeHandle nh_;  //Node handle
                ros::Timer timer;

        public: 
                RefreshZedOdom(ros::NodeHandle *nodehandle);
                void timerCallback(const ros::TimerEvent&);
                ~RefreshZedOdom();
                
};
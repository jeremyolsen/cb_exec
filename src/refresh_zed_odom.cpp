#include "refresh_zed_odom/refresh_zed_odom.h"
#include "zed_wrapper/reset_odometry.h"

/**
 * Node that refreshes zed/zed_node/restart_odometry service every 60 seconds
 */

RefreshZedOdom::RefreshZedOdom(ros::NodeHandle *nodehandle):
      nh_(*nodehandle)
{
    timer = nh_.createTimer(ros::Duration(60.0), &RefreshZedOdom::timerCallback, this);
}    

void RefreshZedOdom::timerCallback(const ros::TimerEvent&)
{
   ROS_INFO("refreshZedOdomService triggered");
   ros::ServiceClient client = nh_.serviceClient<zed_wrapper::reset_odometry>("/zed/zed_node/reset_odometry");
   zed_wrapper::reset_odometry srv;
   if (client.call(srv))
   {
      ROS_INFO("Sum: %ld", (long int)srv.response.reset_done);
   }
   else {
      ROS_ERROR("Failed to call service reset_odometry");
   }
}

RefreshZedOdom::~RefreshZedOdom() {

};

int main(int argc, char **argv)
{
  ros::init(argc, argv, "refresh_zed_odom");
  
  ros::NodeHandle nh("~");
  RefreshZedOdom refesh_zed_odom(&nh);

  ros::spin();

  return 0;
}
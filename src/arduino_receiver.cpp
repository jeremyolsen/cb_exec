#include "arduino_receiver/arduino_receiver.h"

long _PreviousLeftEncoderCounts = 0;
long _PreviousRightEncoderCounts = 0;
double DistancePerCount = (3.14159265 * 0.20) / 24;
double lengthBetweenTwoWheels = 0.54;
double x;
double y;
double th;
double vx;
double vy;
double vth;
double deltaLeft, deltaRight;
double v_left, v_right;
bool first_run = true;

ArduinoReceiver::ArduinoReceiver(ros::NodeHandle *nodehandle): nh_(*nodehandle) {} 

ArduinoReceiver::~ArduinoReceiver() {};

int main(int argc, char **argv)
{
  ros::init(argc, argv, "arduino_receiver");
  
  ros::NodeHandle nh("~");
  ros::Publisher odom_pub = nh.advertise<nav_msgs::Odometry>("odom", 50);
  tf::TransformBroadcaster odom_broadcaster;

  ArduinoReceiver arduino_receiver(&nh);

  try
    {
        ser.setPort("/dev/ttyTHS2");
        ser.setBaudrate(9600);
        serial::Timeout to = serial::Timeout::simpleTimeout(100);
        ser.setTimeout(to);
        ser.open();
    }
    catch (serial::IOException& e)
    {
        ROS_ERROR_STREAM("Unable to open port ");
        return -1;
    }

    if(ser.isOpen()){
        ROS_INFO_STREAM("Serial Port initialized");
    }else{
        return -1;
    }

    ros::Time current_time, last_time;
    current_time = ros::Time::now();
    last_time = ros::Time::now();
    
    ros::Rate loop_rate(5);
    
    while(ros::ok()){

        ros::spinOnce();

        if(ser.available()){
            ROS_INFO_STREAM("Reading from serial port");
            std::vector<std::string> result;
            result = ser.readlines(ser.available());
            ROS_INFO_STREAM("Read: " << result[1]);
            // read_pub.publish(result);
            const std::regex txt_regex("^E ([-0-9]+) ([-0-9]+) ([-0-9]+)");
            std::string serline = result[1];
            std::smatch value_match;
            std::regex_search(serline, value_match, txt_regex);
            if (value_match.size() > 0) {
                ROS_INFO_STREAM("\nvalue_match[1]: " << value_match[1] << "\nvalue_match[2]: " << value_match[2] << "\nvalue_match[3]: " << value_match[3]);

                current_time = ros::Time::now();
                
                std::string::size_type sz;   // alias of size_t
                int match_x = std::stoi (value_match[3],&sz);
                int match_y = std::stoi (value_match[2],&sz);

                if(first_run) {
                    _PreviousLeftEncoderCounts = match_x;
                    _PreviousRightEncoderCounts = match_y;
                    first_run = false;
                }

                deltaLeft = match_x - _PreviousLeftEncoderCounts;
                deltaRight = match_y - _PreviousRightEncoderCounts;

                ROS_INFO_STREAM("deltaLeft: " << deltaLeft << " deltaRight: " << deltaRight);

                v_left = (deltaLeft * DistancePerCount) / (current_time - last_time).toSec();
                v_right = (deltaRight * DistancePerCount) / (current_time - last_time).toSec();

                vx = ((v_right + v_left) / 2);
                vy = 0;
                vth = ((v_right - v_left) / lengthBetweenTwoWheels);

                //compute odometry in a typical way given the velocities of the robot
                double dt = (current_time - last_time).toSec();
                double delta_x = (vx * cos(th) - vy * sin(th)) * dt;
                double delta_y = (vx * sin(th) + vy * cos(th)) * dt;
                double delta_th = vth * dt;

                x += delta_x;
                y += delta_y;
                th += delta_th;

                //since all odometry is 6DOF we'll need a quaternion created from yaw
                geometry_msgs::Quaternion odom_quat = tf::createQuaternionMsgFromYaw(th);

                //first, we'll publish the transform over tf
                geometry_msgs::TransformStamped odom_trans;
                odom_trans.header.stamp = current_time;
                odom_trans.header.frame_id = "base_link";
                odom_trans.child_frame_id = "wheel_odom";

                odom_trans.transform.translation.x = x;
                odom_trans.transform.translation.y = y;
                odom_trans.transform.translation.z = 0.0;
                odom_trans.transform.rotation = odom_quat;

                //send the transform
                odom_broadcaster.sendTransform(odom_trans);

                //next, we'll publish the odometry message over ROS
                nav_msgs::Odometry odom;
                odom.header.stamp = current_time;
                odom.header.frame_id = "base_link";

                //set the position
                odom.pose.pose.position.x = x;
                odom.pose.pose.position.y = y;
                odom.pose.pose.position.z = 0.0;
                odom.pose.pose.orientation = odom_quat;

                //set the velocity
                odom.child_frame_id = "wheel_odom";
                odom.twist.twist.linear.x = vx;
                odom.twist.twist.linear.y = vy;
                odom.twist.twist.angular.z = vth;

                //publish the message
                odom_pub.publish(odom);
                _PreviousLeftEncoderCounts = match_x;
                _PreviousRightEncoderCounts = match_y;

                last_time = current_time;
            }
        }
        loop_rate.sleep();

    }

  return 0;
}
# Captain Barnacle

**Captain Barnacle** the name of the rover project that is composed of autonomous visual navigation components of an ardupilot / PX4 based rover platform built on ros-kinetic.  Packages used as a part of this project include:

## Other Packages

* **rtabmap:** Open source slam solutions that is being used for mapping, visual odometry and localization and the output of costmaps which are used in obstacle avoidance processes.

* **robot_localization:** EKF/UKF sensor fusion package for gps, wheel_odometry, viual_odometry, and IMU

* **move_base:** The move_base package provides an implementation of an action that, given a goal in the world, will attempt to reach it with a mobile base. The move_base node links together a global and local planner to accomplish its global navigation task.

* **mavros:** This package provides communication driver for various autopilots with MAVLink communication protocol. Additional it provides UDP MAVLink bridge for ground control stations (e.g. QGroundControl).

* **zed-ros-wrapper:** This package lets you use the ZED stereo camera with ROS. It outputs the camera left and right images, depth map, point cloud, pose information and supports the use of multiple ZED cameras.

* **teb_local_planner:** The teb_local_planner package implements a plugin to the base_local_planner of the 2D navigation stack. The underlying method called Timed Elastic Band locally optimizes the robot's trajectory with respect to trajectory execution time, separation from obstacles and compliance with kinodynamic constraints at runtime.

* **wheel_encoder:** Custom rear wheel encoders that is using an arduino micro to send and encoder stream to the ros node, which in turn is converting it to odometry Twist messages to be used by UKF/EKF (robot_localization)

## Project Goals

The initial goal of the platform is to be used for a RoboMagellan competition, in which the robot searches and touched 3 traffic cones placed around an area, like a park or urban area that has multiple obstacles.  This will include a navigational executive node that will be listening to artificial intelligence in the form of a R-CNN which will identify traffic cones.  Executive node will then give navigation commands based upon the inference of the R-CNN.

More:  Captain Barnacle is a fictional character on a kids TV show, Octonauts, which can be found on Netflix.  Captain Barnacle is a polar bear and the leader of a crew of underwater animal explorers.   My son choose it after he had asked me if he could name the rover.


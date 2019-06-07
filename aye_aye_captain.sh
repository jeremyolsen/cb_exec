#!/bin/bash

source ~/catkin_ws/devel/setup.bash

clear

# Run jetson at max performance?
#
# This must be run with sudo privelidges 
read -r -p  "Enable maximum performance (Jetson)? [y/n] " key

if [ "$key" = 'y' ]; then

    xterm -e 'echo "nvidia" | sudo -S ./bash/max_perf.sh'
    sleep 1

else
    printf "\nskipping max performance...\n"
fi

#
# Start roscore?
#
printf "\n"
read -r -p "Start roscore? [y/n] " key

if [ "$key" = 'y' ]; then

    'roscore' &
    sleep 2

else
    printf "\nskipping roscore...\n"
fi

#
# Start MavROS?
#
printf "\n"
read -r -p "Start MavROS manually - press any key to continue " key

if [ "$key" = 'y' ]; then

    # xterm -e sshpass -p 'raspberry' ssh -t pi@176.0.0.42 "rosrun mavros mavros_node _fcu_url:=udp:\/\/:14650@ _gcs_url:=udp:\/\/:14551@176.0.0.41:14550" &
    sleep 2

else
    printf "\nskipping MavROS...\n"
fi

#
# Start robot_localization?
#
printf "\n"
read -r -p "Start robot_localiztion? [y/n] " key

if [ "$key" = 'y' ]; then

    xterm -e 'roslaunch cb_exec loco_withgps.launch' &
    sleep 2

else
    printf "\nskipping robot_localization...\n"
fi

#
# Start ZED / rtabmap ?
#
printf "\n"
read -r -p "Start ZED / rtabmap? [y/n] " key

if [ "$key" = 'y' ]; then

    xterm -e 'roslaunch cb_exec zed_rtabmap.launch' & 
    sleep 5

else
    printf "\nskipping zed / rtabmap...\n"
fi

#
# Start move_base ?
#
printf "\n"
read -r -p "Start Move_Base? [y/n] " key

if [ "$key" = 'y' ]; then

    xterm -e 'roslaunch cb_exec move_base.launch' &
    sleep 2

else
    printf "\nskipping Move_Base...\n"
fi

#
# Start cb_exec ?
#
printf "\n"
read -r -p "Start cb_exec? [y/n] " key

if [ "$key" = 'y' ]; then

    xterm -e 'roslaunch cb_exec cb_exec.launch' &
    sleep 2

else
    printf "\nskipping cb_exec...\n"
fi


printf "\nDone!\n"



#!/bin/bash

# uncomment to run rviz on the Nvidia Jetson TX1
# unset GTK_IM_MODULE


# Run jetson at max performance?
#
# This must be run with sudo privelidges
printf "This is the 3D/VO versions of robot_localization and rtabmap launch files\n\n" 
read -r -p  "Enable maximum performance (Jetson)? [y/n] " key

if [ "$key" = 'y' ]; then

    xterm -e sshpass -p 'nvidia' ssh -t nvidia@176.0.0.41 'echo "nvidia" | sudo -S nvpmodel -m 0; echo "nvidia" | sudo -S ./jetson_clocks.sh; $SHELL -i' &
    sleep 2
    xterm -e sshpass -p 'nvidia' ssh -t nvidia@176.0.0.41 'cd ~/swap; echo "nvidia" | sudo -S rm -rf swapfile^M; echo "nvidia" | sudo -S sh Jetson_Create_Swap_File.sh; $SHELL -i' &
    sleep 2

else
    printf "\nskipping max performance...\n"
fi

#
# Start roscore?
#
printf "\n"
read -r -p "Start roscore? [y/n] " key

if [ "$key" = 'y' ]; then

    xterm -e sshpass -p 'nvidia' ssh -t nvidia@176.0.0.41 'source ~/catkin_ws/devel/setup.bash; roscore; $SHELL -i' &
    sleep 2

else
    printf "\nskipping roscore...\n"
fi

#
# Start wheel encoder?
#
printf "\n"
read -r -p "Start wheel encoder? [y/n] " key

if [ "$key" = 'y' ]; then

    xterm -e sshpass -p 'nvidia' ssh -t nvidia@176.0.0.41 'source ~/catkin_ws/devel/setup.bash; roslaunch cb_exec wheel_encoder.launch; $SHELL -i' &
    sleep 2

else
    printf "\nskipping wheel encoder...\n"
fi

#
# Start MavROS?
#
printf "\n"
read -r -p "Start MavROS? [y/n] - hit up button/enter in xterm window to complete" key

if [ "$key" = 'y' ]; then

    xterm -e sshpass -p 'raspberry' ssh -t pi@176.0.0.42 &
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

    xterm -e sshpass -p 'nvidia' ssh -t nvidia@176.0.0.41 'source ~/catkin_ws/devel/setup.bash; roslaunch cb_exec loco_withgps_3D_vo.launch; $SHELL -i' &
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

    xterm -e sshpass -p 'nvidia' ssh -t nvidia@176.0.0.41 'source ~/catkin_ws/devel/setup.bash; roslaunch cb_exec zed_rtabmap.launch; $SHELL -i' & 
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

    xterm -e sshpass -p 'nvidia' ssh -t nvidia@176.0.0.41 'source ~/catkin_ws/devel/setup.bash; roslaunch cb_exec move_base.launch; $SHELL -i' &
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

    xterm -e sshpass -p 'nvidia' ssh -t nvidia@176.0.0.41 'source ~/catkin_ws/devel/setup.bash; roslaunch cb_exec cb_exec.launch; $SHELL -i' &
    sleep 2

else
    printf "\nskipping cb_exec...\n"
fi


printf "\nDone!\n"



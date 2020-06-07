#!/bin/sh

# Create a test_navigation.sh shell script that launches these files

# Define workspace variable
path_catkin_ws="/home/workspace/catkin_ws"

xterm -e "cd ${path_catkin_ws} && source devel/setup.bash && roslaunch turtlebot_gazebo turtlebot_world.launch" &
sleep 5

xterm -e "cd ${path_catkin_ws} && source devel/setup.bash && roslaunch turtlebot_gazebo amcl_demo.launch" &
sleep 5

xterm -e "cd ${path_catkin_ws} && source devel/setup.bash && roslaunch add_markers view_navigation.launch rviz_path:=${path_catkin_ws}/src/rvizConfig/rvizConfig.rviz" &
sleep 5

xterm -e "cd ${path_catkin_ws} && source devel/setup.bash && rosrun add_markers add_markers" &


xterm -e "cd ${path_catkin_ws} && source devel/setup.bash && rosrun pick_objects pick_objects"
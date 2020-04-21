# go_straight_and_turn  
A ROS package that you can let your robot move straight or rotate for a specified distance or radian.
## Launch files
* go_straight.launch  
Let the robot move staight for a specified distance with a specified linear velocity.
* go_turn.launch  
Let the robot rotate for a specified radian with a specified angular velocity.
## Arguments
1. odom_topic  
The topic published from odom sensor (nav_msgs/Odometry).
2. cmd_vel_topic  
The topic published to the robot mobile base (geometry_msgs/Twist).
3. distance  
Linear or angular distance that robot will move for (m or rad).
4. velocity  
Linear or angular velocity that robot will move with (m/s or rad/s).  
5. ctrl_freq  
The frequence of /cmd_vel topic is published(Hz).  
__All default arguments are appropriate with Turtlebot3.__  
## Examples
go_straight example: `roslaunch go_straight_and_turn go_straight.launch odom_topic:=/odom cmd_vel_topic:=/cmd_vel distance:=0.5 velocity:=0.15 ctrl_freq:=8.0`  
go_turn example: `roslaunch go_straight_and_turn go_turn.launch odom_topic:=/odom cmd_vel_topic:=/cmd_vel distance:=-1.57 velocity:=0.3 ctrl_freq:=8.0`  

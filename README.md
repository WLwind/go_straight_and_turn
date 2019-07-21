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
__All default arguments are appropriate with Turtlebot3.__

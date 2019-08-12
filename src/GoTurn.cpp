#include <go_straight_and_turn/GoTurn.h>

geometry_msgs::Twist GoTurn::getCmdVel(const nav_msgs::Odometry::ConstPtr& ptr)
{
    double roll,pitch,yaw;
    geometry_msgs::Twist turn_speed;//msg quaternion
    tf::Quaternion tfq;//tf quaternion
    tf::quaternionMsgToTF(ptr->pose.pose.orientation, tfq);//msg quaternion to tf quaternion
    tf::Matrix3x3(tfq).getRPY(roll, pitch, yaw);//tf quaternion to Euler angle
    if(getFirstTime())
    {
        start=yaw;
        destination=start+goal;
        destination=destination>=3.14159265?destination-6.2831853:destination;//range of yaw: [-π,π)
        destination=destination<-3.14159265?destination+6.2831853:destination;
        clearFirstTime();
        ROS_INFO("Start yaw is %frad",yaw);
    }
    distance=fabs(destination-yaw);//goal yaw - current yaw
    if(distance>=0.08)//tolerance
    {
        if(goal_sign)
            turn_speed.angular.z=speed!=0.0?speed:0.3;
        else
            turn_speed.angular.z=speed!=0.0?-speed:-0.3;
    }
    else
    {
        turn_speed.angular.z=0.0;
        setStop();
        ROS_INFO("Final yaw is %f",yaw);
    }
    return turn_speed;
}
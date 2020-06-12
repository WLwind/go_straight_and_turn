#include <cmath>
#include <tf2/utils.h>
#include <go_straight_and_turn/GoTurn.h>
GoTurn::GoTurn(double goal_init,double speed_init,bool shutdown):GoCMD(goal_init,speed_init,shutdown)
{
    laps=goal/2.0/M_PI;
    if(laps!=0)
    {
        ROS_INFO("The robot need to turn %d laps",laps);
    }
}

geometry_msgs::Twist GoTurn::getCmdVel(const nav_msgs::Odometry::ConstPtr& ptr)
{
    geometry_msgs::Twist turn_speed;//msg quaternion
    tf2::Quaternion tf2q;
    tf2::fromMsg(ptr->pose.pose.orientation,tf2q);//message to tf2
    double yaw=tf2::getYaw(tf2q);
    if(getFirstTime())
    {
        start=yaw;
        destination=start+goal-laps*2*M_PI;//(-2π,2π)
        destination=destination>=M_PI?destination-2*M_PI:destination;//range of yaw: [-π,π)
        destination=destination<-M_PI?destination+2*M_PI:destination;
        ROS_INFO("Start yaw is %f rad",yaw);
        if(std::fabs(destination-yaw)<TURN_THRESHOLD&&std::fabs(goal-laps*2*M_PI)>TURN_THRESHOLD)
        {
            near_loop=true;
        }
        clearFirstTime();
    }
    distance=std::fabs(destination-yaw);//goal yaw - current yaw
    if(distance>=TURN_THRESHOLD)//tolerance
    {
        near_loop=false;
        if(goal_sign)
            turn_speed.angular.z=speed!=0.0?speed:0.3;
        else
            turn_speed.angular.z=speed!=0.0?-speed:-0.3;
    }
    else
    {
        if(!near_loop)
        {
            near_loop=true;
            laps+=goal_sign?-1:1;
        }
        if(laps==(goal_sign?-1:1))//need to stop
        {
            turn_speed.angular.z=0.0;
            setStop();
            ROS_INFO("Final yaw is %f",yaw);
        }
        else
        {
            if(goal_sign)
                turn_speed.angular.z=speed!=0.0?speed:0.3;
            else
                turn_speed.angular.z=speed!=0.0?-speed:-0.3;
        }
    }
    return turn_speed;
}

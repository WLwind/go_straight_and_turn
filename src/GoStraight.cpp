#include <go_straight_and_turn/GoStraight.h>

GoStraight::GoStraight(double dis,double spd):GoStraight(dis)//C++11 delegate constructor
{
    setSpeed(spd);
}

geometry_msgs::Twist GoStraight::getCmdVel(const nav_msgs::Odometry::ConstPtr& ptr)
{
    double x=ptr->pose.pose.position.x;
    double y=ptr->pose.pose.position.y;
    geometry_msgs::Twist straight_speed;
    if(getFirstTime())
    {
        start[0]=x;
        start[1]=y;
        clearFirstTime();
        ROS_INFO("Start coordinate is (%.3f,%.3f)",x,y);
    }
    setDistance(fabs(getGoal())-sqrt(pow(x-start[0],2)+pow(y-start[1],2)));//goal distance - current distance
    if(getDistance()>=0.005)//tolerance
    {
        if(goal_sign)
            straight_speed.linear.x=getSpeed()!=0.0?getSpeed():0.03;
        else
            straight_speed.linear.x=getSpeed()!=0.0?-getSpeed():-0.03;
    }
    else
    {
        straight_speed.linear.x=0.0;
        setStop();
        ROS_INFO("Final coordinate is (%.3f,%.3f)",x,y);
    }
    return straight_speed;
}
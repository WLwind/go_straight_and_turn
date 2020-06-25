#include <complex>
#include <go_straight_and_turn/GoStraight.h>

geometry_msgs::msg::Twist GoStraight::getCmdVel(const nav_msgs::msg::Odometry::SharedPtr ptr)
{
    double x=ptr->pose.pose.position.x;
    double y=ptr->pose.pose.position.y;
    geometry_msgs::msg::Twist straight_speed;
    if(getFirstTime())
    {
        start[0]=x;
        start[1]=y;
        clearFirstTime();
        RCLCPP_INFO(get_logger(),"Start coordinate is (%.3f,%.3f)",x,y);
    }
    distance=std::abs(goal)-std::sqrt(std::pow(x-start[0],2)+std::pow(y-start[1],2));//goal distance - current distance
    if(distance>=m_tolerance)//tolerance
    {
        if(goal_sign)
            straight_speed.linear.x=speed!=0.0?speed:0.03;
        else
            straight_speed.linear.x=speed!=0.0?-speed:-0.03;
    }
    else
    {
        straight_speed.linear.x=0.0;
        setStop();
        RCLCPP_INFO(get_logger(),"Final coordinate is (%.3f,%.3f)",x,y);
    }
    return straight_speed;
}


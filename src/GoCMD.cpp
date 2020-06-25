#include <go_straight_and_turn/GoCMD.h>

GoCMD::GoCMD(double goal_init,double speed_init,bool shutdown,std::string node_name):Node(node_name),m_shutdown(shutdown),goal(goal_init),distance(goal_init),speed(speed_init)
{
    goal_sign=goal>=0;
    RCLCPP_INFO(get_logger(),"Set goal to %.3f",goal);
    if(!get_parameter("ctrl_freq",m_ctrl_freq))
        m_ctrl_freq=10.0;
    if(!get_parameter("tolerance",m_tolerance))
        m_ctrl_freq=10.0;
    m_cmd_timer=create_wall_timer(std::chrono::duration<int,std::milli>(int(1000/m_ctrl_freq)),std::bind(&GoCMD::timerCB,this));
}

void GoCMD::odomCB(const nav_msgs::msg::Odometry::SharedPtr ptr)
{
    geometry_msgs::msg::Twist vel=getCmdVel(ptr);
    m_cmd_vel_mx.lock();
    cmd_vel_msg=vel;
    m_cmd_vel_mx.unlock();
    return;
}

void GoCMD::setStop()
{
    m_need_stop_mx.lock();
    need_stop=true;
    m_need_stop_mx.unlock();
    return;
}

void GoCMD::clearFirstTime()
{
    first_time=false;
    return;
}

bool GoCMD::getFirstTime() const
{
    return first_time;
}

void GoCMD::timerCB()
{
    m_cmd_vel_mx.lock();
    vel_pub->publish(cmd_vel_msg);
    m_cmd_vel_mx.unlock();
    if(getStop())
    {
        geometry_msgs::msg::Twist zero;
        vel_pub->publish(zero);
        RCLCPP_INFO(get_logger(),"Done!");
        if(m_shutdown)
            rclcpp::shutdown();
    }
    return;
}


bool GoCMD::getStop()
{
    m_need_stop_mx.lock();
    auto stop=need_stop;
    m_need_stop_mx.unlock();
    return stop;
}


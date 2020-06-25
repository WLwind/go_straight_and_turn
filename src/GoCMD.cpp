#include <go_straight_and_turn/GoCMD.h>

GoCMD::GoCMD(double goal_init,double speed_init,bool shutdown):m_shutdown(shutdown),goal(goal_init),distance(goal_init),speed(speed_init)
{
    goal_sign=goal>=0;
    ROS_INFO("Set goal to %.3f",goal);
    ros::NodeHandle private_nh("~/");
    private_nh.param("ctrl_freq",m_ctrl_freq,10.0);
    private_nh.param("tolerance",m_tolerance,0.01);
    m_cmd_timer=private_nh.createTimer(ros::Duration(1.0/m_ctrl_freq),&GoCMD::timerCB,this);
}


void GoCMD::odomCB(const nav_msgs::Odometry::ConstPtr& ptr)
{
    geometry_msgs::Twist vel=getCmdVel(ptr);
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

void GoCMD::timerCB(const ros::TimerEvent& ev)
{
    m_cmd_vel_mx.lock();
    vel_pub.publish(cmd_vel_msg);
    m_cmd_vel_mx.unlock();
    if(getStop())
    {
        geometry_msgs::Twist zero;
        vel_pub.publish(zero);
        ROS_INFO("Done!");
        if(m_shutdown)
            ros::shutdown();
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

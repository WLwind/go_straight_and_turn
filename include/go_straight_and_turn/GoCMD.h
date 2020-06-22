#pragma once

#include <iostream>
#include <mutex>
#include <stdlib.h>
#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <nav_msgs/Odometry.h>

class GoCMD
{
public:
    /**
    * @brief Constructor with 2 default arguments
    * @param goal_init The goal distance
    * @param speed_init The speed that you want your robot to move
    */
    GoCMD(double goal_init=0.1,double speed_init=0.1,bool shutdown=true);
    /**
    * @brief Destructor
    */
    virtual ~GoCMD(){}
    /**
    * @brief Odom subscriber callback funtion
    */
    void odomCB(const nav_msgs::Odometry::ConstPtr&);
    /**
    * @brief Get velocity command from derived class
    * @param ptr Pointer of odom message
    * @return Velocity command for the robot
    */
    virtual geometry_msgs::Twist getCmdVel(const nav_msgs::Odometry::ConstPtr&)=0;
    /**
    * @brief Set stop sign to true
    */
    void setStop();
    /**
    * @brief Set fisrt first_time to false
    */
    void clearFirstTime();
    /**
    * @brief Get first time sign
    * @return first_time
    */
    bool getFirstTime() const;
    /**
    * @brief Get stop sign
    * @return need_stop
    */
    bool getStop();

    bool goal_sign{true};//positive or negative sign

private:
    void timerCB(const ros::TimerEvent& ev);
    ros::NodeHandle nh;
    ros::Subscriber odom_sub{nh.subscribe<nav_msgs::Odometry>("odom",1,boost::bind(&GoCMD::odomCB,this,_1))};//odom subscriber
    ros::Publisher vel_pub{nh.advertise<geometry_msgs::Twist>("cmd_vel",1)};//velocity publisher
    geometry_msgs::Twist cmd_vel_msg;//velocity mesage
    std::mutex m_cmd_vel_mx;
    bool need_stop{false},first_time{true};//stop signal，first time or not
    std::mutex m_need_stop_mx;
    double m_ctrl_freq{10.0};//frequency of publishing cmd_vel
    ros::Timer m_cmd_timer;//timer for publishing cmd_vel
    bool m_shutdown{true};//whether to shutdown the node after publishing zero speed

protected:
    double goal{0};//goal distance
    double distance{0.0};//distance to the goal
    double speed{0.0};//velocity m/s or rad/s
};


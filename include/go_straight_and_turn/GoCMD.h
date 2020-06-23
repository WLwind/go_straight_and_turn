#pragma once

#include <iostream>
#include <mutex>
#include <stdlib.h>
#include <chrono>
#include <functional>
#include <string>
#include <rclcpp/rclcpp.hpp>
#include <geometry_msgs/msg/twist.hpp>
#include <nav_msgs/msg/odometry.hpp>

class GoCMD:public rclcpp::Node
{
public:
    /**
    * @brief Constructor with 2 default arguments
    * @param goal_init The goal distance
    * @param speed_init The speed that you want your robot to move
    * @param node_name The name of the node
    */
    GoCMD(double goal_init=0.1,double speed_init=0.1,bool shutdown=true,std::string node_name="go_cmd");
    /**
    * @brief Destructor
    */
    virtual ~GoCMD(){}
    /**
    * @brief Odom subscriber callback funtion
    */
    void odomCB(const nav_msgs::msg::Odometry::SharedPtr);
    /**
    * @brief Get velocity command from derived class
    * @param ptr Pointer of odom message
    * @return Velocity command for the robot
    */
    virtual geometry_msgs::msg::Twist getCmdVel(const nav_msgs::msg::Odometry::SharedPtr)=0;
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
    void timerCB();
//    ros::NodeHandle nh;
    rclcpp::Subscription<nav_msgs::msg::Odometry>::SharedPtr odom_sub{create_subscription<nav_msgs::msg::Odometry>("odom",10,std::bind(&GoCMD::odomCB,this,std::placeholders::_1))};//odom subscriber
    rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr vel_pub{create_publisher<geometry_msgs::msg::Twist>("cmd_vel",10)};//velocity publisher
    geometry_msgs::msg::Twist cmd_vel_msg;//velocity mesage
    std::mutex m_cmd_vel_mx;
    bool need_stop{false},first_time{true};//stop signal，first time or not
    std::mutex m_need_stop_mx;
    double m_ctrl_freq{10.0};//frequency of publishing cmd_vel
    rclcpp::TimerBase::SharedPtr m_cmd_timer;//timer for publishing cmd_vel
    bool m_shutdown{true};//whether to shutdown the node after publishing zero speed

protected:
    double goal{0};//goal distance
    double distance{0.0};//distance to the goal
    double speed{0.0};//velocity m/s or rad/s
};

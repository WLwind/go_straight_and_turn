#pragma once//or _Pragma("once");
//#ifndef GO_CMD_H
//#define GO_CMD_H

#include <iostream>
#include <ros/ros.h>
#include <stdlib.h>
#include <tf/transform_listener.h>
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
    GoCMD(double goal_init=0.1,double speed_init=0.1);
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

    bool goal_sign{true};//plus or minus sign

private:
    ros::NodeHandle nh;
    ros::Subscriber odom_sub{nh.subscribe<nav_msgs::Odometry>("odom",1,boost::bind(&GoCMD::odomCB,this,_1))};//odom publisher
    ros::Publisher vel_pub{nh.advertise<geometry_msgs::Twist>("cmd_vel",1)};//velocity publisher
    geometry_msgs::Twist cmd_vel_msg;//velocity mesage
    bool need_stop{false},first_time{true};//stop signal，first time or not

protected:
    double goal{0};//goal distance
    double distance{0.0};//distance to the goal
    double speed{0.0};//velocity m/s or rad/s
};
//#endif
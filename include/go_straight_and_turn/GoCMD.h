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
    GoCMD(double=0.1,double=0.1);//constructor with 2 default value
    virtual ~GoCMD(){}
    void odomCB(const nav_msgs::Odometry::ConstPtr&);//odom callback funtion
    virtual geometry_msgs::Twist getCmdVel(const nav_msgs::Odometry::ConstPtr&)=0;//get velocity command from derived class
    void setStop();//set stop sign
    void clearFirstTime();//clear fisrt time sign
    bool getFirstTime() const;//read first time sign
    bool goal_sign{true};//plus or minus sign

private:
    ros::NodeHandle nh;
    ros::Subscriber odom_sub{nh.subscribe<nav_msgs::Odometry>("odom",1,boost::bind(&GoCMD::odomCB,this,_1))};//odom publisher
    ros::Publisher vel_pub{nh.advertise<geometry_msgs::Twist>("cmd_vel",1)};//velocity publisher
    geometry_msgs::Twist cmd_vel_msg;//velocity mesage
    bool need_stop{false},first_time{true};//stop signal，first time or not

protected:
    double goal{0};//goal distance
    double distance{0.0};//discance to the goal
    double speed{0.0};//velocity m/s or rad/s
};
//#endif
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
    GoCMD(double=0.1);
    void odomCB(const nav_msgs::Odometry::ConstPtr&);
    virtual geometry_msgs::Twist getCmdVel(const nav_msgs::Odometry::ConstPtr&)=0;
    virtual ~GoCMD(){}
    void setStop();
    void clearFirstTime();
    bool getFirstTime() const;
    void setDistance(double);
    double getDistance() const;
    double getGoal() const;
    void setSpeed(double);
    double getSpeed() const;
    bool goal_sign{true};//is goal distance plus or minus

private:
    ros::NodeHandle nh;
    ros::Subscriber odom_sub{nh.subscribe<nav_msgs::Odometry>("odom",1,boost::bind(&GoCMD::odomCB,this,_1))};//odom publisher
    ros::Publisher vel_pub{nh.advertise<geometry_msgs::Twist>("cmd_vel",1)};//velocity publisher
    geometry_msgs::Twist cmd_vel_msg;//velocity mesage
    bool need_stop{false},first_time{true};//stop signal，first time or not
    double goal{0};//goal distance
    double distance{0.0};//discance to the goal
    double speed{0.0};//velocity m/s or rad/s
};
//#endif
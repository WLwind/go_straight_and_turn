#pragma once
//#ifndef GO_S_H
//#define GO_S_H

#include <go_straight_and_turn/GoCMD.h>

class GoStraight:public GoCMD
{
public:
    using GoCMD::GoCMD;//C++11 inherit constructor
    geometry_msgs::Twist getCmdVel(const nav_msgs::Odometry::ConstPtr&) override;//obtain linear velocity
    virtual ~GoStraight(){}

private:
    double start[2]{0.0,0.0};//initial coordinate
};
//#endif
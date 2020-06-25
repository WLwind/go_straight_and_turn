#pragma once

#include <go_straight_and_turn/GoCMD.h>

class GoStraight:public GoCMD
{
public:
    using GoCMD::GoCMD;
    /**
    * @brief Get linear velocity command
    * @param ptr Pointer of odom message
    * @return Velocity command for the robot
    */
    geometry_msgs::msg::Twist getCmdVel(const nav_msgs::msg::Odometry::SharedPtr) override;
    /**
    * @brief Destructor
    */
    ~GoStraight() override{}

private:
    double start[2]{0.0,0.0};//initial coordinate
};


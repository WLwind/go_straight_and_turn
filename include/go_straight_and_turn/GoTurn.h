#pragma once

#include <go_straight_and_turn/GoCMD.h>

class GoTurn:public GoCMD
{
public:
    GoTurn(double goal_init=0.1,double speed_init=0.1,bool shutdown=true,std::string node_name="go_turn");
    /**
    * @brief Get angular velocity command
    * @param ptr Pointer of odom message
    * @return Velocity command for the robot
    */
    geometry_msgs::msg::Twist getCmdVel(const nav_msgs::msg::Odometry::SharedPtr) override;
    /**
    * @brief Destructor
    */
    ~GoTurn() override{}

private:
    double start{0.0},destination{0.0};//initial yaw， goal yaw
    int laps{0};//numbers of laps the robot should turn
    bool near_loop{false};//whether current orientation is near the start orientation
};


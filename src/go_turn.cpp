#include <stdlib.h>
#include <cmath>
#include <go_straight_and_turn/GoTurn.h>

int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);
    std::shared_ptr<GoTurn> go_turn_object_ptr;
    if(argc<3)
    {
        go_turn_object_ptr=std::make_shared<GoTurn>(argc==2?atof(argv[1]):M_PI_2);//radian
    }
    else
    {
        go_turn_object_ptr=std::make_shared<GoTurn>(atof(argv[1]),atof(argv[2]));//radian, angular velocity
    }
    rclcpp::executors::MultiThreadedExecutor executor(rclcpp::executor::ExecutorArgs(),2);
    executor.add_node(go_turn_object_ptr);
    executor.spin();
    return 0;
}


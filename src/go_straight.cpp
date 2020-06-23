#include <stdlib.h>
#include <memory>
#include <go_straight_and_turn/GoStraight.h>

int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);
    std::shared_ptr<GoStraight> go_straight_object_ptr;
    if(argc<3)
    {
        go_straight_object_ptr=std::make_shared<GoStraight>(argc==2?atof(argv[1]):0.1,0.1,true,"go_straight_node");//distance
    }
    else if(argc==3)
    {
        go_straight_object_ptr=std::make_shared<GoStraight>(atof(argv[1]),atof(argv[2]),true,"go_straight_node");//distance、linear velocity
    }
    rclcpp::executors::MultiThreadedExecutor executor(rclcpp::executor::ExecutorArgs(),2);
    executor.add_node(go_straight_object_ptr);
    executor.spin();
    return 0;
}

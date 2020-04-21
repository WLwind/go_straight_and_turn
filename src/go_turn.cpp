#include <stdlib.h>//transform argv to int
#include <go_straight_and_turn/GoTurn.h>

int main(int argc, char *argv[])
{
    ros::init(argc, argv, "go_turn_node");
    std::unique_ptr<GoTurn> go_turn_object_ptr;
    if(argc<3)
    {
        go_turn_object_ptr.reset(new GoTurn(argc==2?atof(argv[1]):1.570796327));//radian
    }
    else if(argc==3)
    {
        go_turn_object_ptr.reset(new GoTurn(atof(argv[1]),atof(argv[2])));//radian, angular velocity
    }
    ros::MultiThreadedSpinner spinner(2);
    spinner.spin();
    return 0;
}

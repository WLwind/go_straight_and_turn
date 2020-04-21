#include <stdlib.h>//transform argv to int
#include <go_straight_and_turn/GoStraight.h>

int main(int argc, char *argv[])
{
    ros::init(argc, argv, "go_straight_node");
    std::unique_ptr<GoStraight> go_straight_object_ptr;
    if(argc<3)
    {
        go_straight_object_ptr.reset(new GoStraight(argc==2?atof(argv[1]):0.1));//distance
    }
    else if(argc==3)
    {
        go_straight_object_ptr.reset(new GoStraight(atof(argv[1]),atof(argv[2])));//distance、linear velocity
    }
    ros::MultiThreadedSpinner spinner(2);
    spinner.spin();
    return 0;
}

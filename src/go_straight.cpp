#include <stdlib.h>//transform argv to int
//#include <cassert>
#include <go_straight_and_turn/GoStraight.h>

int main(int argc, char *argv[])
{
    ros::init(argc, argv, "go_straight_node");
    GoStraight* go_straight_object=0;
    if(argc<3)
    {
        go_straight_object=new GoStraight(argc==2?atof(argv[1]):0.1);//distance
    }
    else if(argc==3)
    {
        go_straight_object=new GoStraight(atof(argv[1]),atof(argv[2]));//distance、linear velocity
    }
    ros::spin();
    delete go_straight_object;
    return 0;
}
#include <stdlib.h>//transform argv to int
#include <go_straight_and_turn/GoTurn.h>

int main(int argc, char *argv[])
{
    ros::init(argc, argv, "go_turn_node");
    GoTurn* go_turn_object=0;
    if(argc<3)
        go_turn_object=new GoTurn(argc==2?atof(argv[1]):1.570796327);//radian
    else if(argc==3)
        go_turn_object=new GoTurn(atof(argv[1]),atof(argv[2]));//radian, angular velocity
    ros::spin();
    delete go_turn_object;
    return 0;
}
#include "ros/ros.h"
#include <ap0_com/messages.h>
#include <iostream>

bool provide_next(ap0_com::apollo_message  &req,
         ap0_com::apollo_message &res)
{
  std::cin >> res.next ;
  // std::cin >> res.int64 ;

  // ROS_INFO("request: x=%ld, y=%ld", (long int)req.a, (long int)req.b);
  // ROS_INFO("sending back response: [%ld]", (long int)res.sum);
  return true;
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "provide_next_service");
  ros::NodeHandle n;

  ros::ServiceServer service = n.advertiseService("move_to_next", provide_next);
  ROS_INFO("Ready to move base.");
  ros::spin();

  return 0;
}

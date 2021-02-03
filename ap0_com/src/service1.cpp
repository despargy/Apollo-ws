#include "ros/ros.h"
#include <iostream>
#include <ap_msgs/GetPermission.h>
#include <string>

// bool provide_next(std_msgs* req,
//          std_msgs &res)
// {
//   std::cin >> res.int64 ;
//
//   return true;
// }

struct Landmark {
  std::string name;
  double x;
  double y;
};

class LandmarkMonitor {
  public:
    LandmarkMonitor(){}
    bool GetPermission(ap_msgs::GetPermissionRequest &request,ap_msgs::GetPermissionResponse &response)
    {
          ROS_INFO("GetPermission called");
          std::cin >> response.next ;
           // response.next = 5 ;

          return true;
    }
};

int main(int argc, char **argv)
{
  ros::init(argc, argv, "service1");
  ros::NodeHandle nh;

  LandmarkMonitor monitor;

  ros::ServiceServer service = nh.advertiseService("move_to_next", &LandmarkMonitor::GetPermission, &monitor);
  ROS_INFO("Ready to move base.");
  ros::spin();

  return 0;
}

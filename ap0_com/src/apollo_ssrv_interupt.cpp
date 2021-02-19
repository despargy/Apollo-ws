#include "ros/ros.h"
#include <iostream>
#include <ap_msgs/GetPermission.h>
#include <string>
#include "useTcpipClient.cpp"

struct Landmark {
  std::string name;
  double x;
  double y;
};

class LandmarkMonitor {
  public:
    LandmarkMonitor(){}
    bool GetPermission(ap_msgs::GetPermissionRequest &request, ap_msgs::GetPermissionResponse &response)
    {
          ROS_INFO("GetPermission called");
          // //send OK
          // if (request.success)
          //   ROS_INFO("request.success == TRUE");
            informGoalReached();
            ROS_INFO("before useTcpClient");
            int id ;
            useTcpClient(&id);
            request.success = false;

            std::cout<<id<<std::endl;
            response.next = id ;
            if (response.next == 8)
            {
              std::cin.clear();
              // cin.ignore(numeric_limits<streamsize>::max, '\n');
              std::cout<<"cin.clear"<<std::endl; // TODO maybe not demanded
            }
          // }
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

#include "ros/ros.h"
#include <iostream>
#include <ap_msgs/GetPermission.h>
#include <string>
#include "useTcpipClient.cpp"
#include <boost/thread.hpp>

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
          if (request.success)
          {
            ROS_INFO("request.success == TRUE");
            informGoalReached();

            ROS_INFO("before useTcpClient");
            int id ;
            useTcpClient(&id);

            request.success = false;
            response.next = id ;

            if (response.next == 8)
            {
              std::cin.clear();
              // cin.ignore(numeric_limits<streamsize>::max, '\n');
              std::cout<<"cin.clear"<<std::endl; // TODO maybe not demanded
            }
          }
          else
          {
            response.next = request.current ; //id
            ROS_INFO("Send same id as it, failed in aproach");
          }
          return true;
    }

    bool GetInterupt(ap_msgs::GetPermissionRequest &request, ap_msgs::GetPermissionResponse &response)
    {
          ROS_INFO("GetInterupt called");
          int idInterupt;
          handleInteruptClient(&idInterupt);
          if (idInterupt == 8)
          {
            ROS_INFO("got 8 ");
            return false;
          }
          return true;
    }
};

int main(int argc, char **argv)
{
  ros::init(argc, argv, "service1");
  ros::NodeHandle nh;

  LandmarkMonitor monitor, monitorInterupt;

  ros::AsyncSpinner spinner(3);
  spinner.start();

  ros::ServiceServer service = nh.advertiseService("move_to_next", &LandmarkMonitor::GetPermission, &monitor);
  ROS_INFO("Ready to move base.");
  //handle handle interupts
  ros::ServiceServer serviceInterupt = nh.advertiseService("handle_interupt", &LandmarkMonitor::GetInterupt, &monitorInterupt);
  ROS_INFO("After handle interupt.");

  // while(true)
  // {
  //   if (idInterupt == 8)
  //     ROS_INFO("BREAK");
  // }

  // ros::spin();
  ros::waitForShutdown();

  return 0;
}

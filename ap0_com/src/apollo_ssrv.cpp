#include "ros/ros.h"
#include <iostream>
#include <ap_msgs/GetPermission.h>
#include <string>
#include "useTcpipClient.cpp"
#include <boost/thread.hpp>
#include "std_msgs/Int8.h"

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

    // bool GetInterupt(ap_msgs::GetPermissionRequest &request, ap_msgs::GetPermissionResponse &response)
    // {
    //       ROS_INFO("GetInterupt called");
    //       int idInterupt;
    //       handleInteruptClient(&idInterupt);
    //       if (idInterupt == 8)
    //       {
    //         ROS_INFO("got 8 ");
    //         return false;
    //       }
    //       return true;
    // }
};

int main(int argc, char **argv)
{
  ros::init(argc, argv, "service1");
  ros::NodeHandle nh, n;

  LandmarkMonitor monitor, monitorInterupt;

  // int idInterupt;
  // handleInteruptClient(&idInterupt);

  ros::AsyncSpinner spinner(2);
  spinner.start();
  //handle handle interupts
  ros::Publisher inter_pub = n.advertise<std_msgs::Int8>("interupt_chatter", 1000);
  // ros::ServiceServer serviceInterupt = nh.advertiseService("handle_interupt", &LandmarkMonitor::GetInterupt, &monitorInterupt);
  // ROS_INFO("After handle interupt.");

  ros::ServiceServer service = nh.advertiseService("move_to_next", &LandmarkMonitor::GetPermission, &monitor);
  ROS_INFO("Ready to move base.");

  ros::Rate loop_rate(2);
  while(ros::ok())
  {
      int idInterupt;
      handleInteruptClient(&idInterupt);

      std_msgs::Int8 msg;
      msg.data = idInterupt;
      ROS_INFO("%d", msg.data);
      inter_pub.publish(msg);
  }
  ros::waitForShutdown();

  return 0;
}

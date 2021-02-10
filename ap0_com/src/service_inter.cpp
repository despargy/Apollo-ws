#include "ros/ros.h"
#include <iostream>
#include <ap_msgs/Interupt.h>
#include <string>

// bool provide_next(std_msgs* req,
//          std_msgs &res)
// {
//   std::cin >> res.int64 ;
//
//   return true;
// }

struct InteruptStruct {
  std::string name;
  double id;
};

class InteruptHandler {
  public:
    InteruptHandler(){}
    bool SendInterupt(ap_msgs::InteruptRequest &request, ap_msgs::InteruptResponse &response)
    {
          ROS_INFO("Handler for Interupts called");
          std::cin >> response.inter_id ;
           // response.next = 5 ;

          return true;
    }
};

int main(int argc, char **argv)
{
  ros::init(argc, argv, "service_inter");
  ros::NodeHandle nh;

  InteruptHandler ih;

  ros::ServiceServer service = nh.advertiseService("interupt", &InteruptHandler::SendInterupt, &ih);
  ROS_INFO("Ready to handle interupts.");
  ros::spin();

  return 0;
}

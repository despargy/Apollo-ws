#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <iostream>
#include <fstream>
#include <strings.h>
#include <string>
#include <sstream>
#include <ros/ros.h>

#include <move_base_msgs/MoveBaseGoal.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <move_base_msgs/MoveBaseResult.h>
#include <actionlib/client/terminal_state.h>
#include <actionlib/client/simple_action_client.h>

#include "setGoalParams.cpp"
#include <ap_msgs/GetPermission.h>

const int BUF_LEN=256;
const int PORT  = 1300;

using namespace std;



int main(int argc,char** argv)
{
  ros::init(argc, argv, "d_com");
  ros::NodeHandle n;

  // ac=new actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction>("move_base", true);
  // ac->waitForServer();
  // ros::ServiceClient client = n.serviceClient<std_msgs>("move_to_next");
  //
  // std_msgs srv;
  //
  // if (client.call(srv))
  // {
  //   cout<<"Permission was given !"<<endl;
  //   bool achieved = actionTo(&srv);
  // }
  // else
  // {
  //   cout<<"Permission denied !"<<endl;
  // }

  ros::spin();

  return 0;
}

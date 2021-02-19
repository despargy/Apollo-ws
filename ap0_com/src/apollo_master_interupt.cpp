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
#include <message_filters/subscriber.h>
#include <move_base_msgs/MoveBaseGoal.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <move_base_msgs/MoveBaseResult.h>
#include <actionlib/client/terminal_state.h>
#include <actionlib/client/simple_action_client.h>
#include "setGoalParams.cpp"
#include <ap_msgs/GetPermission.h>
#include "tf2_ros/message_filter.h"
#include "useTcpipClient.cpp"


const int BUF_LEN=256;
const int PORT  = 1300;

using namespace std;

actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> *ac;
ap_msgs::GetPermissionRequest req;
ap_msgs::GetPermissionResponse res;

///////////////////

// Called once when a tour becomes active
void activeCb()
{
  ROS_INFO("Tour received");
}

void doneCb(const actionlib::SimpleClientGoalState& state,
            const move_base_msgs::MoveBaseResultConstPtr& result)
{
    /*
     * Publish Robot msg only on success and error
     * Do not publish on no final state (e.g. PENDING) and on PREEMPTED
     */
    if(state.state_==actionlib::SimpleClientGoalState::SUCCEEDED)
    {
        ROS_INFO("SUCCEEDED");
        req.success = true;
        req.current = res.next; // renew current state
    }
    else if(state.state_==actionlib::SimpleClientGoalState::ABORTED ||
        state.state_==actionlib::SimpleClientGoalState::REJECTED
    )
    {
        ROS_INFO("NOT SUCCEEDED");
        req.success = false;
    }
}


// Called every time feedback is received for the goal
void feedbackCb(const move_base_msgs::MoveBaseFeedbackConstPtr& feedback)
{
    ROS_INFO("In Feedback - sending goal");
}

//////////////

// Action function
void actionTo(ap_msgs::GetPermissionRequest req, ap_msgs::GetPermissionResponse res)
// bool actionTo( std_msgs req, std_msgs res)
{
    cout<<"Received an action"<<endl;
    int stop_id = res.next ;

    if (stop_id == 0)
    {
      // ac-> cancelGoal();
      ROS_INFO("Action wait - cancel / stop id = 0 ");
    }
    else if (stop_id == 8)
    {
      ac-> cancelGoal();
      ROS_INFO("Action wait - cancel / stop id = 8 ");
      // Checking for valid stop_id
    }
    else if(stop_id >= 1 and stop_id <=5)
    {
      move_base_msgs::MoveBaseGoal goal;
      goal = setStaticGoal(stop_id);

      ROS_INFO("Sending goal");
      ac->sendGoal(goal, &doneCb, &activeCb, &feedbackCb);
      ac->waitForResult();
    }
    else
    {
      ROS_INFO("Warning: Invalid stop_id");
    }
}

int main(int argc,char** argv)
{
  ros::init(argc, argv, "d_com");
  ros::NodeHandle n;

  // action client
  ac=new actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction>("move_base", true);
  ac->waitForServer();

  // service Client to receive ids from server
  ros::ServiceClient client = n.serviceClient<ap_msgs::GetPermission>("move_to_next");
  // client.waitForServer();
  // client.waitForExistence();
  req.success = true;


  ros::Rate loop_rate(2);
  while(ros::ok())
  {

    if(client.call(req, res))
    {
      ROS_INFO("After .call");
      ROS_INFO("%d",res.next);
      // call action to send goal - handle response
      actionTo(req, res);
    }
    else
    {
      ROS_INFO("Waiting for server to connect.");
    }

    loop_rate.sleep();
    ros::spinOnce();

  }

  return 0;
}
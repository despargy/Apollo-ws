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
const int BUF_LEN=256;
const int PORT  = 1300;

using namespace std;

actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> *ac;


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
    }
    else if(state.state_==actionlib::SimpleClientGoalState::ABORTED ||
        state.state_==actionlib::SimpleClientGoalState::REJECTED
    )
    {
      ROS_INFO("NOT SUCCEEDED");
    }
}


// Called every time feedback is received for the goal
// void feedbackCb(const move_base_msgs::MoveBaseActionFeedbackConstPtr& feedback)
void feedbackCb(const move_base_msgs::MoveBaseFeedbackConstPtr& feedback)
{
    ROS_INFO("Got Feedback");
}

//////////////

// Action function
bool actionTo(ap_msgs::GetPermissionResponse res, bool *valid)
// bool actionTo( std_msgs req, std_msgs res)
{
    cout<<"Received an action"<<endl;
    int stop_id = res.next ;

    // Checking for valid stop_id
    if(stop_id >= 0 and stop_id <=5)
    {
      *valid = true;
      move_base_msgs::MoveBaseGoal goal;

      goal = setStaticGoal(stop_id);

      ROS_INFO("Sending goal");

      ac->sendGoal(goal, &doneCb, &activeCb, &feedbackCb);
      // if (stop_id == 1)
      //   ac-> cancelGoal();
      ac->waitForResult();

      if(ac->getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
      {
        ROS_INFO("The base moved with success");
        return  true;
      }
      else
      {
        ROS_INFO("The base failed to move with success");
        ROS_INFO("FAILED");
        return  false;
      }
    }
    else
    {
      *valid = false;
      ROS_INFO("Warning: Invalid stop_id");
      return  false;
    }
}

int main(int argc,char** argv)
{
  ros::init(argc, argv, "d_com");
  ros::NodeHandle n;

  ac=new actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction>("move_base", true);
  ac->waitForServer();

  ros::ServiceClient client = n.serviceClient<ap_msgs::GetPermission>("move_to_next");
  // client.waitForServer();
  // client.waitForExistence();

  ap_msgs::GetPermissionRequest req;
  ap_msgs::GetPermissionResponse res;

  bool valid;
  // tf2_ros::MessageFilter<std_msgs::int> mf;

  ros::Rate loop_rate(2);
  while(ros::ok())
  {

    if(client.call(req, res))
    {

      bool achieved;
      do
      {
        ROS_INFO("Server gave me a goal");
        ROS_INFO("%d",res.next);
        achieved = actionTo(res, &valid); // call action to send goal
      }while( valid and !achieved); // try again if valid and not reached

      if (achieved)
      {
        req.current = res.next; // renew current state
        ROS_INFO("Now speek");  //TODO inform (as server) to speek
      }
      else if (!valid)
      {
       ROS_INFO("Invalid goal send");
      }

    }else
    {
      ROS_INFO("Waiting for server to connect.");
    }

    loop_rate.sleep();
    ros::spinOnce();
  }

  return 0;
}

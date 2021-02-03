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
#include <ap0_com/messages.h>

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
bool actionTo( ap0_com::apollo_message* res)
// bool actionTo( std_msgs req, std_msgs res)
{

    cout<<"Received an action"<<endl;
    int stop_id = (*res).next ;

    // Checking for valid stop_id
    if(stop_id >= 0 and stop_id <=5)
    {
      move_base_msgs::MoveBaseGoal goal;

      goal = setStaticGoal(stop_id);

      ROS_INFO("Sending goal");

      ac->sendGoal(goal, &doneCb, &activeCb, &feedbackCb);

      ac->waitForResult();

      if(ac->getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
      {
        cout<<"SUCCEEDED"<<endl;
        ROS_INFO("The base went back at the charging spot");
        // setTCPIPConnection();
        (*res).msg = "Success";
        return true;
      }
      else
      {
        ROS_INFO("The base failed to move back at the charging spot");
        cout<<"FAILED"<<endl;
      }
    }
    else
    {
      cout<<"Warning: Invalid stop_id"<<endl;
      (*res).msg = "Failure";
      return false;
    }



}

int main(int argc,char** argv)
{
  ros::init(argc, argv, "d_com");
  ros::NodeHandle n;

  ac=new actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction>("move_base", true);
  ac->waitForServer();
  ros::ServiceClient client = n.serviceClient<ap0_com::apollo_message>("move_to_next");
  // ros::ServiceClient client = n.advertiseClient<std_msgs>("move_to_next");

  ap0_com::apollo_message srv;

  if (client.call(srv))
  {
    cout<<"Permission was given !"<<endl;
    bool achieved = actionTo(&srv);
  }
  else
  {
    cout<<"Permission denied !"<<endl;
  }
  // srv. = 2;

  // daisy_pub = new ros::Publisher(n.advertise<timestorm_msg::Robot>("/daisy/from_nao_chatter", 1000) );
  // cout<<"starting"<<endl;
  // for(int i = 0 ; i < 6 ; i++)
  // {
  //   last_id[i] = i;
  //   cout<<last_id[i]<<endl;
  //   // actionTo(last_id[i]);
  //
  // }

  ros::spin();

  return 0;
}
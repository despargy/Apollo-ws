#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<unistd.h>
#include <iostream>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <ros/ros.h>
#include <message_filters/subscriber.h>
#include <move_base_msgs/MoveBaseGoal.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <move_base_msgs/MoveBaseResult.h>
#include <actionlib/client/terminal_state.h>
#include <actionlib/client/simple_action_client.h>
#include "setGoalParams.cpp"
#include <ap_msgs/GetPermission.h>
#include "SocketClient.cpp"
#include "ActionsNSockets.h"

HandleActionSocket::HandleActionSocket()
{
  // action client
  // actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> *ac;
  ac=new actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction>("move_base", true);
  ac->waitForServer();
  // create CONNECTION
  mysocket.informGoalReached();
  ROS_INFO("Constructor HandleActionSocket");

}

// Called once when a tour becomes active
void HandleActionSocket::activeCb()
{
  ROS_INFO("Tour received");
}

void HandleActionSocket::doneCb(const actionlib::SimpleClientGoalState& state,
            const move_base_msgs::MoveBaseResultConstPtr& result)
{
    /*
     * Publish Robot msg only on success and error
     * Do not publish on no final state (e.g. PENDING) and on PREEMPTED
     */
    if(state.state_==actionlib::SimpleClientGoalState::SUCCEEDED)
    {
        ROS_INFO("SUCCEEDED");
        mysocket.informGoalReached(); //TODO
    }
    else if(state.state_==actionlib::SimpleClientGoalState::ABORTED ||
        state.state_==actionlib::SimpleClientGoalState::REJECTED
    )
    {
        ROS_INFO("NOT SUCCEEDED");
    }
}


// Called every time feedback is received for the goal
void HandleActionSocket::feedbackCb(const move_base_msgs::MoveBaseFeedbackConstPtr& feedback)
{
    ROS_INFO("In Feedback - sending goal"); //TODO
}

//////////////



// Action function
bool HandleActionSocket::actionTo( int stop_id)
{
    ROS_INFO("Received an action");

    if (stop_id >= 1 and stop_id <=5)
    {
      move_base_msgs::MoveBaseGoal goal;
      goal = setStaticGoal(stop_id);
      ROS_INFO("Sending goal");
      // ac->sendGoal(goal, boost::bind(&HandleActionSocket::doneCb, this, &HandleActionSocket::activeCb, &HandleActionSocket::feedbackCb));

      ac->sendGoal(goal, boost::bind(&HandleActionSocket::doneCb, this, _1, _2),
                boost::bind(&HandleActionSocket::activeCb, this),
                boost::bind(&HandleActionSocket::feedbackCb, this, _1));
    }
    else if (stop_id == 8) //TODO
    {
      ac-> cancelGoal();
      ROS_INFO("Action wait - cancel / interupt id = 8 ");
    }
    else if (stop_id  == 0) //TODO
    {
      ac-> cancelGoal();
      ROS_INFO("Action wait - cancel / interupt id = 0 ");
    }
    else
    {
      ROS_INFO("Warning: Invalid stop_id");
    }

}

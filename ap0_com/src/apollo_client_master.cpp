#include <ros/ros.h>
#include <actionlib/client/simple_action_client.h>
#include <actionlib/client/terminal_state.h>
#include <ap_msgs/apMoveAction.h>
#include "setActionGoalParams.cpp"

actionlib::SimpleActionClient<ap_msgs::apMoveAction> *ac;


// Action function
bool actionTo(ap_msgs::apMoveResult result_, bool *valid)
// bool actionTo( std_msgs req, std_msgs res)
{
    cout<<"Received an action"<<endl;
    int stop_id = result_.id ;

    // Checking for valid stop_id
    if(stop_id >= 0 and stop_id <=5)
    {
      *valid = true;
      //TODO IT AP ACTION NOT MOVE BASE
      ap_msgs::apMoveGoal goal = setActionStaticGoal(stop_id);

      ROS_INFO("Sending goal");

      ac->sendGoal(goal);
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


int main (int argc, char **argv)
{
  ros::init(argc, argv, "test_apMove");

  // create the action client
  // true causes the client to spin its own thread
  ac = new actionlib::SimpleActionClient<ap_msgs::apMoveAction>("ap", true);

  ROS_INFO("Waiting for action server to start.");
  // wait for the action server to start
  ac->waitForServer(); //will wait for infinite time

  ROS_INFO("Action server started.");


  //wait for the action to return
  bool finished_before_timeout = ac->waitForResult(ros::Duration(30.0));

  if (finished_before_timeout)
  {
    actionlib::SimpleClientGoalState state = ac->getState();
    ROS_INFO("Action finished: %s",state.toString().c_str());
  }
  else
    ROS_INFO("Action did not finish before the time out.");

  //exit
  return 0;
}

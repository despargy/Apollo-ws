#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <stdio.h>

#include <sstream>
#include <ros/ros.h>
#include <move_base_msgs/MoveBaseGoal.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <move_base_msgs/MoveBaseResult.h>
#include <tf/transform_datatypes.h>

using namespace std;

move_base_msgs::MoveBaseGoal setStaticGoal(int stop_id )
{
  move_base_msgs::MoveBaseGoal goal;
  if (stop_id == 0)
  {
    cout<<"Go back to the charging spot"<<endl;

    //we'll send the robot back to the charging spot
    goal.target_pose.header.frame_id = "base_link"; //TODO
    goal.target_pose.header.stamp = ros::Time::now();

    goal.target_pose.pose.position.x = 1.0; //TODO
    goal.target_pose.pose.position.y=0.80;
    goal.target_pose.pose.position.z = 0.0;
    tf::Quaternion quat;
    quat.setRPY(0,0,3.14);
    quat.normalize();
    goal.target_pose.pose.orientation.x = quat[0];
    goal.target_pose.pose.orientation.y = quat[1];
    goal.target_pose.pose.orientation.z = quat[2];
    goal.target_pose.pose.orientation.w = quat[3];

  }
  else if (stop_id == 1)
  {
    cout<<"Go to "<<stop_id<<endl;
    move_base_msgs::MoveBaseGoal goal;

    //we'll send the robot to picked stop
    goal.target_pose.header.frame_id = "base_link"; //TODO
    goal.target_pose.header.stamp = ros::Time::now();

    goal.target_pose.pose.position.x = 0.0; //TODO
    goal.target_pose.pose.position.y=0.80;
    goal.target_pose.pose.position.z = 0.0;
    tf::Quaternion quat;
    quat.setRPY(0,0,3.14);
    quat.normalize();
    goal.target_pose.pose.orientation.x = quat[0];
    goal.target_pose.pose.orientation.y = quat[1];
    goal.target_pose.pose.orientation.z = quat[2];
    goal.target_pose.pose.orientation.w = 0; //quat[3];
  }
  else if (stop_id == 2)
  {
    cout<<"Go to "<<stop_id<<endl;
    move_base_msgs::MoveBaseGoal goal;

    //we'll send the robot to picked stop
    goal.target_pose.header.frame_id = "base_link"; //TODO
    goal.target_pose.header.stamp = ros::Time::now();

    goal.target_pose.pose.position.x = 1.0; //TODO
    goal.target_pose.pose.position.y=0.80;
    goal.target_pose.pose.position.z = 0.0;
    tf::Quaternion quat;
    quat.setRPY(0,0,3.14);
    quat.normalize();
    goal.target_pose.pose.orientation.x = quat[0];
    goal.target_pose.pose.orientation.y = quat[1];
    goal.target_pose.pose.orientation.z = quat[2];
    goal.target_pose.pose.orientation.w = quat[3];
    std::cout<<quat[0]<<endl;
    std::cout<<quat[1]<<endl;
    std::cout<<quat[2]<<endl;
    std::cout<<quat[3]<<endl;


  }
  else if (stop_id == 3)
  {
    cout<<"Go to "<<stop_id<<endl;
    move_base_msgs::MoveBaseGoal goal;

    //we'll send the robot to picked stop
    goal.target_pose.header.frame_id = "base_link"; //TODO
    goal.target_pose.header.stamp = ros::Time::now();

    goal.target_pose.pose.position.x = 1.60; //TODO
    goal.target_pose.pose.position.y=1.0;
    goal.target_pose.pose.position.z = 0.0;
    tf::Quaternion quat;
    quat.setRPY(0,0,3.14);
    quat.normalize();
    goal.target_pose.pose.orientation.x = quat[0];
    goal.target_pose.pose.orientation.y = quat[1];
    goal.target_pose.pose.orientation.z = quat[2];
    goal.target_pose.pose.orientation.w = quat[3];
  }
  else if (stop_id == 4)
  {
    cout<<"Go to "<<stop_id<<endl;
    move_base_msgs::MoveBaseGoal goal;

    //we'll send the robot to picked stop
    goal.target_pose.header.frame_id = "base_link"; //TODO
    goal.target_pose.header.stamp = ros::Time::now();

    goal.target_pose.pose.position.x = 2.0; //TODO
    goal.target_pose.pose.position.y=0.80;
    goal.target_pose.pose.position.z = 0.0;
    tf::Quaternion quat;
    quat.setRPY(0,0,3.14);
    quat.normalize();
    goal.target_pose.pose.orientation.x = quat[0];
    goal.target_pose.pose.orientation.y = quat[1];
    goal.target_pose.pose.orientation.z = quat[2];
    goal.target_pose.pose.orientation.w = quat[3];
  }
  // else print a Warning
  else if (stop_id == 5)
  {
    cout<<"Go to "<<stop_id<<endl;
    move_base_msgs::MoveBaseGoal goal;

    //we'll send the robot to picked stop
    goal.target_pose.header.frame_id = "base_link"; //TODO
    goal.target_pose.header.stamp = ros::Time::now();

    goal.target_pose.pose.position.x = 1.0; //TODO
    goal.target_pose.pose.position.y=0.80;
    goal.target_pose.pose.position.z = 0.0;
    tf::Quaternion quat;
    quat.setRPY(0,0,3.14);
    quat.normalize();
    goal.target_pose.pose.orientation.x = quat[0];
    goal.target_pose.pose.orientation.y = quat[1];
    goal.target_pose.pose.orientation.z = quat[2];
    goal.target_pose.pose.orientation.w = quat[3];
  }

  return goal;
}

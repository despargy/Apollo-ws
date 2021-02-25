#ifndef ACTIONSNSOCKETS_H
#define ACTIONSNSOCKETS_H
#include "SocketClient.h"

class HandleActionSocket
{
  public:
    SocketClient mysocket;
    actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> *ac;
    HandleActionSocket();
    void activeCb();
    void doneCb(const actionlib::SimpleClientGoalState& state,
                const move_base_msgs::MoveBaseResultConstPtr& result);
    void feedbackCb(const move_base_msgs::MoveBaseFeedbackConstPtr& feedback);
    bool actionTo( int stop_id );

};
#endif

/*
 * TODO check that all the headers bellow are usefull
 */
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
#include <actionlib/client/simple_action_client.h>
#include <move_base_msgs/MoveBaseGoal.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <move_base_msgs/MoveBaseResult.h>
#include <actionlib/client/terminal_state.h>
#include <tf/transform_datatypes.h>

using namespace std;

const char hostM[]="139.91.185.77";  //Mixalis
int portM=1200;
int listenM;
struct sockaddr_in svrAddM;
struct hostent *serverM;


int setTCPIPConnection_0(const char* hostname, int portNo, int *listenFd, struct sockaddr_in *svrAdd, struct hostent **server){
    bool loop = false;

    if((portNo > 65535) || (portNo < 1000))
    {
        cerr<<"Please enter port number between 1000 - 65535"<<endl;
        return 0;
    }

    //create client skt
    *listenFd = socket(AF_INET, SOCK_STREAM, 0);

    if(*listenFd < 0)
    {
        cerr << "Cannot open socket" << endl;
        return 0;
    }

    *server = gethostbyname(hostname);

    if(*server == NULL)
    {
        cerr << "Host does not exist" << endl;
        return 0;
    }

    bzero((char *) svrAdd, sizeof(*svrAdd));
    svrAdd->sin_family = AF_INET;

    bcopy((char *) (*server)->h_addr, (char *) &(svrAdd->sin_addr.s_addr), (*server)->h_length);

    svrAdd->sin_port = htons(portNo);

    int checker = connect(*listenFd,(struct sockaddr *) svrAdd, sizeof(*svrAdd));

    if (checker < 0)
    {
        cerr << "Cannot connect!" << endl;
        return 0;
    }


        char bb[]="-NtoP-Done";
        cout <<"just sent...."<<endl;
        write(*listenFd, bb, strlen(bb));
    close(*listenFd);
}

int setTCPIPConnection() {
    return  setTCPIPConnection_0((const char*)hostM, portM, &listenM, &svrAddM, &serverM);
}

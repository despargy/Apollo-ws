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

#include <timestorm_msg/Time.h>
#include <timestorm_msg/Daisy.h>
const int BUF_LEN=256;
const int PORT  = 1300;
using namespace std;


int main(int argc, char** argv) {
  ros::init(argc, argv, "ap0_com");
  ros::NodeHandle n("~");
  ros::Publisher time_pub = n.advertise<timestorm_msg::Time>("/ap0_com/time", 1000);
    int opt = true;
    int master_socket , addrlen , new_socket , client_socket[30] ,
    max_clients = 30 , activity, i , valread , sd;
    int max_sd;
    struct sockaddr_in address;

    char buffer[BUF_LEN+1];

    //set of socket descriptors
    fd_set readfds;

    //a message
    const char  *message = "ConnectedOK";

    //initialise all client_socket[] to 0 so not checked
    for (i = 0; i < max_clients; i++)
    {
        client_socket[i] = 0;
    }

    //create a master socket
    if( (master_socket = socket(AF_INET , SOCK_STREAM , 0)) == 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    //set master socket to allow multiple connections ,
    //this is just a good habit, it will work without this
    if( setsockopt(master_socket, SOL_SOCKET, SO_REUSEADDR, (char *)&opt,
          sizeof(opt)) < 0 )
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    //type of socket created
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( PORT );

    //bind the socket to localhost port 8888
    if (bind(master_socket, (struct sockaddr *)&address, sizeof(address))<0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    printf("Listener on port %d \n", PORT);

    //try to specify maximum of 3 pending connections for the master socket
    if (listen(master_socket, 3) < 0)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    //accept the incoming connection
    addrlen = sizeof(address);
    puts("Waiting for connections ...");

  ROS_INFO("Connecting to the TCP/IP Timestorm Planner Server");

 ros::Rate rate(100);
 while(ros::ok())
 {
        //clear the socket set
        FD_ZERO(&readfds);

        //add master socket to set
        FD_SET(master_socket, &readfds);
        max_sd = master_socket;

        //add child sockets to set
        for ( i = 0 ; i < max_clients ; i++)
        {
            //socket descriptor
            sd = client_socket[i];

            //if valid socket descriptor then add to read list
            if(sd > 0)
                FD_SET( sd , &readfds);

            //highest file descriptor number, need it for the select function
            if(sd > max_sd)
                max_sd = sd;
        }

        //wait for an activity on one of the sockets , timeout is NULL ,
        //so wait indefinitely
        activity = select( max_sd + 1 , &readfds , NULL , NULL , NULL);


        if ((activity < 0) && (errno!=EINTR))
        {
            printf("select error");
        }

//        cout <<".";

        //If something happened on the master socket ,
        //then its an incoming connection
        if (FD_ISSET(master_socket, &readfds))
        {
            if ((new_socket = accept(master_socket,
                    (struct sockaddr *)&address, (socklen_t*)&addrlen))<0)
            {
                perror("accept");
                exit(EXIT_FAILURE);
            }

            //inform user of socket number - used in send and receive commands
            printf("New connection , socket fd is %d , ip is : %s , port : %d \n" , new_socket , inet_ntoa(address.sin_addr) , ntohs
                  (address.sin_port));

        cout<<"send bak to markos :"<<message<<endl;
            //send new connection greeting message
            if( send(new_socket, message, strlen(message), 0) != strlen(message) )
            {
                perror("send");
            }

            puts("Welcome message sent successfully");

            //add new socket to array of sockets
            for (i = 0; i < max_clients; i++)
            {
                //if position is empty
                if( client_socket[i] == 0 )
                {
                    client_socket[i] = new_socket;
                    printf("Adding to list of sockets as %d\n" , i);

                    break;
                }
            }
        }

        //else its some IO operation on some other socket
        for (i = 0; i < max_clients; i++)
        {
            sd = client_socket[i];
        memset(buffer, 0, (BUF_LEN+1)*sizeof(char));

            if (FD_ISSET( sd , &readfds)) {
                    //Check if it was for closing , and also read the incoming message
                    if ((valread = read( sd , buffer, BUF_LEN)) == 0) {
                        //Somebody disconnected , get his details and print
                        getpeername(sd , (struct sockaddr*)&address, (socklen_t*)&addrlen);
                        printf("Host disconnected , ip %s , port %d \n", inet_ntoa(address.sin_addr) , ntohs(address.sin_port));

                        //Close the socket and mark as 0 in list for reuse
                        close( sd );
                        client_socket[i] = 0;
                    }
                    //process the message that came in
                    else {
                        getpeername(sd , (struct sockaddr*)&address, (socklen_t*)&addrlen);
                        printf("Host info: ip %s , port %d \n", inet_ntoa(address.sin_addr) , ntohs(address.sin_port));

                //cout <"something" << buffer << "\n";
                printf("%s, valread:%d\n",buffer,valread);
                int dd, pp,aa,tt;
                if (valread>0){
                    std::string bs(buffer); //create "string" using the char-array
                    if (bs == "-PtoN-MoveToJaco")
                    {
                        ros::ServiceClient client = n.serviceClient<ap0_com::goToJaco>("/timeStorm/goToJaco");
                        ap0_com::goToJaco srv;
                        client.call(srv);
                    }
                    else if (bs == "-PtoN-MoveToHuman")
                    {
                        ros::ServiceClient client = n.serviceClient<ap0_com::goToHuman>("/timeStorm/goToHuman");
                        ap0_com::goToHuman srv;
                        client.call(srv);
                    }
                    else if (bs == "-PtoN-WaitFilling")
                     {
                        ros::ServiceClient client = n.serviceClient<ap0_com::waitFilling>("/timeStorm/waitFilling");
                        ap0_com::waitFilling srv;
                        client.call(srv);

                     }
                    else if (bs == "-PtoN-GoHome")
                    {
                        ros::ServiceClient client = n.serviceClient<ap0_com::waitFilling>("/timeStorm/waitFilling");
                        ap0_com::waitFilling srv;
                        client.call(srv);
                    }
                    else if (bs == "-PtoN-SayMessage"){
                        ros::ServiceClient client = n.serviceClient<ap0_com::waitFilling>("/timeStorm/waitFilling");
                        ap0_com::waitFilling srv;
                        client.call(srv);
                    }
               	    else if (bs.find("-NT-")!= string::npos){

			     std::size_t ef_start = bs.find("-EF-");
			      int nt =  atoi ((bs.substr(4,ef_start)).c_str());
				std::cout<<nt<<std::endl;
			    double ef =  atof ((bs.substr(ef_start+4,bs.length())).c_str());
				std::cout<<ef<<std::endl;
			    timestorm_msg::Time time_msg;

			    time_msg.header.stamp = ros::Time::now();
			    time_msg.duration = nt;
			    time_msg.efficiency = ef;
			    time_pub.publish(time_msg);
                    }
  	    		else if (bs.find("-STO-")!= string::npos){
			    timestorm_msg::Time time_msg;
			    time_msg.header.stamp = ros::Time::now();
			    time_msg.duration = -1;
			    time_msg.efficiency = -1;
			    time_pub.publish(time_msg);
                    }
                    else
                        ROS_INFO("Error In com");
                }
                        //set the string terminating NULL byte on the end of the data read
                        buffer[valread] = '\0';
                //Echo back the message that came in
                        //send(sd , buffer , strlen(buffer) , 0 );
                    }
                }


        }

  rate.sleep();
  ros::spinOnce();
 }
  return 0;
}

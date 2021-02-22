#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
//Create a Socket for server communication
//
// class TCPipClient()
// {
//
// }

short SocketCreate(void)
{
    short hSocket;
    printf("Create the socket\n");
    hSocket = socket(AF_INET, SOCK_STREAM, 0);
    return hSocket;
}
//try to connect with server
int SocketConnect(int hSocket, int port_)
{
    int iRetval=-1;
    int ServerPort = port_;
    struct sockaddr_in remote= {0};
    remote.sin_addr.s_addr = inet_addr("127.0.0.1"); //Local Host 192.168.1.4 127.0.0.1
    remote.sin_family = AF_INET;
    remote.sin_port = htons(ServerPort);
    iRetval = connect(hSocket,(struct sockaddr *)&remote,sizeof(struct sockaddr_in));
    return iRetval;
}


// Send the data to the server and set the timeout of 20 seconds
int SocketSend(int hSocket,char* Rqst,short lenRqst)
{
    int shortRetval = -1;
    struct timeval tv;
    tv.tv_sec = 1200;  /* 20 Secs Timeout */
    tv.tv_usec = 0;
    if(setsockopt(hSocket,SOL_SOCKET,SO_SNDTIMEO,(char *)&tv,sizeof(tv)) < 0)
    {
        printf("Time Out\n");
        return -1;
    }
    shortRetval = send(hSocket, Rqst, lenRqst, 0);
    return shortRetval;
}
//receive the data from the server
int SocketReceive(int hSocket,char* Rsp,short RvcSize)
{
    int shortRetval = -1;
    struct timeval tv;
    tv.tv_sec = 1200;  /* 20 Secs Timeout */
    tv.tv_usec = 0;
    if(setsockopt(hSocket, SOL_SOCKET, SO_RCVTIMEO,(char *)&tv,sizeof(tv)) < 0)
    {
        printf("Time Out\n");
        return -1;
    }
    shortRetval = recv(hSocket, Rsp, RvcSize, 0);
    printf("Response %s\n",Rsp);
    return shortRetval;
}
//main driver program
// int cl_main(int *id_)
int useTcpClient(int *id)
{
    int hSocket,  read_size;
    struct sockaddr_in server;
    char SendToServer[100] = {0};
    char server_reply[200] = {0};
  // while(true)
  // {
    //Create socket
    hSocket = SocketCreate();

    if(hSocket == -1) // if nt while
    {
        printf("Could not create socket\n");
        // hSocket = SocketCreate(); //commend

        return 1;
    }
    printf("Socket is created\n");
    //Connect to remote server
    if (SocketConnect(hSocket, 90190) < 0)
    {
        perror("connect failed.\n");
        return 1;
    }
    printf("Sucessfully conected with server\n");

    //......................
    // printf("Enter the Message: ");
    // // gets(SendToServer);
    // std::cin>>SendToServer;
    // //Send data to the server
    // SocketSend(hSocket, SendToServer, strlen(SendToServer));
    //Received the data from the server
    //.......................
  //   //
  //   // //SEND OK - GOAL REACHED
  //   if (!first)
  //   {
  //   SendToServer[0] = 'O' ;
  //   SendToServer[1] = 'K';
  //   //Send data to the server
  //   SocketSend(hSocket, SendToServer, strlen(SendToServer));
  //   printf("comment - like send\n");
  // }

    read_size = SocketReceive(hSocket, server_reply, 200);
    *id = atoi( server_reply );
    std::cout<<*id<<std::endl;
    // std::cout<<int(server_reply[0])<<std::endl;
    // std::cout<<(*id)<<std::endl;

    close(hSocket);
    shutdown(hSocket,0);
    shutdown(hSocket,1);
    shutdown(hSocket,2);
  // };

    return 0;
}

int informGoalReached()
{
    int hSocket, read_size;
    struct sockaddr_in server;
    char SendToServer[100] = {0};


    //Create socket
    hSocket = SocketCreate();

    if(hSocket == -1) // if nt while
    {
        printf("Could not create socket\n");
        // hSocket = SocketCreate(); //commend

        return 1;
    }
    printf("Socket is created\n");
    //Connect to remote server
    if (SocketConnect(hSocket, 90190) < 0)
    {
        perror("connect failed.\n");
        return 1;
    }
    printf("Sucessfully conected with server\n");

    SendToServer[0] = 'O' ;
    SendToServer[1] = 'K';
    //Send data to the server
    SocketSend(hSocket, SendToServer, strlen(SendToServer));

    close(hSocket);
    shutdown(hSocket,0);
    shutdown(hSocket,1);
    shutdown(hSocket,2);

    return 0;
}

int handleInteruptClient(int *id)
{
    int hSocket, read_size;
    struct sockaddr_in server;
    char SendToServer[100] = {0};
    char server_reply[200] = {0};
  // while(true)
  // {
    //Create socket
    hSocket = SocketCreate();

    if(hSocket == -1) // if nt while
    {
        printf("Could not create socket\n");
        // hSocket = SocketCreate(); //commend

        return 1;
    }
    printf("Socket handleInteruptClient is created\n");
    //Connect to remote server
    if (SocketConnect(hSocket, 90191) < 0)
    {
        perror("connect failed.\n");
        return 1;
    }
    printf("Sucessfully handleInteruptClient conected with server\n");

    //......................
    // printf("Enter the Message: ");
    // // gets(SendToServer);
    // std::cin>>SendToServer;
    // //Send data to the server
    // SocketSend(hSocket, SendToServer, strlen(SendToServer));
    //Received the data from the server
    //.......................
  //   //
  //   // //SEND OK - GOAL REACHED
  //   if (!first)
  //   {
  //   SendToServer[0] = 'O' ;
  //   SendToServer[1] = 'K';
  //   //Send data to the server
  //   SocketSend(hSocket, SendToServer, strlen(SendToServer));
  //   printf("comment - like send\n");
  // }
    printf("Before Recieve. Am I gonna wait? interupt\n");

    read_size = SocketReceive(hSocket, server_reply, 200);
    *id = atoi( server_reply );
    std::cout<<*id<<std::endl;
    // std::cout<<int(server_reply[0])<<std::endl;
    // std::cout<<(*id)<<std::endl;

    close(hSocket);
    shutdown(hSocket,0);
    shutdown(hSocket,1);
    shutdown(hSocket,2);
  // };

    return 0;
}

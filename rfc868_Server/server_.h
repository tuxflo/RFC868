#ifndef SERVER__H
#define SERVER__H
#include <iostream>
#include <string.h>
#include <sys/socket.h>
#include <netdb.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>

class Server_
{
public:
    Server_();
    ~Server_();
    virtual bool listen_accept() =0;

protected:
    virtual void send_time() =0;
    void setflags(bool oflag, int port);
    void error(const char *msg);

    int socketfd;
    int newsockfd;
    struct sockaddr_in server_addr;
    struct sockaddr_in client_addr;
    socklen_t client_length;
    bool running;
    bool oflag; //For showing Output messages
    int port; //If different port is selected
};

#endif // SERVER__H

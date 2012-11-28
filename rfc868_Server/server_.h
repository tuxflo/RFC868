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
    virtual ~Server_() =0;
    virtual void send_time() =0;

protected:
    void setflags(bool oflag, int port);
    void error(const char *msg);
    int ret;
    unsigned int rfc_time;
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

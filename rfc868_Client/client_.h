#ifndef CLIENT__H
#define CLIENT__H
#include <iostream>
#include <unistd.h>
#include <string>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

class client_
{
public:
    client_();
    virtual ~client_() =0;
    struct hostent* findserver(struct hostent *server, int attempt);
    void error(const char* msg);
    unsigned int get_rfc_time();
    virtual void recieve_time() =0;

protected:
    void setflags(bool oflag, int port);
    int socketfd, ret;
    struct sockaddr_in server_addr;
    struct hostent *server;
    unsigned int rfc_time, length;
    bool oflag; //For showing Output messages
    int port; //If different port is selected
};

#endif // CLIENT__H

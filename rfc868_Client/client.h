#ifndef Client_H
#define Client_H
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
#include <signal.h>

class Client
{
public:
    Client();
    virtual ~Client() =0;
    struct hostent* findserver(struct hostent *server, int attempt);
    void error(const char* msg);
    unsigned int get_rfc_time();
    virtual int recieve_time() =0;

protected:
    void setflags(bool oflag, int port);
    int socketfd, ret;
    struct sockaddr_in server_addr;
    struct hostent *server;
    unsigned int rfc_time, length;
    bool oflag; //For showing Output messages
    int port; //If different port is selected

    struct sigaction end_process;
    static void get_signal(int sig);
    static bool quit;
};

#endif // Client_H

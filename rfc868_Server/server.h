#ifndef Server_H
#define Server_H
#include <iostream>
#include <string.h>
#include <sys/socket.h>
#include <netdb.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <signal.h>

class Server
{
public:
    Server();
    virtual ~Server() =0;
    virtual void send_time() =0;

protected:
    void setflags(bool oflag, int port);
    void error(const char *msg);

    static void get_signal(int sig);
    static bool quit;
    int ret;
    unsigned int rfc_time;
    int socketfd;
    int newsockfd;
    struct sockaddr_in server_addr;
    struct sockaddr_in client_addr;
    socklen_t client_length;
    bool oflag; //For showing Output messages
    int port; //If different port is selected
    bool running;
    struct sigaction end_process;
};

#endif // Server_H

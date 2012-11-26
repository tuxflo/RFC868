#include <iostream>
#include <sys/socket.h>
#include <cstring>
#include <string>
#include <netdb.h>
#include <ctime>
#include <unistd.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <errno.h>

#include "server_.h"
#include "tcp_socket.h"
#include "udp_socket.h"

using namespace std;

void show_help()
{
    cout << "Usage:" << endl <<
            "-h prints this help" << endl <<
            "-i swich between ipv4 and ipv6 (default is ipv4)" << endl <<
            "-u use udp as protocol (default is tcp)" << endl <<
            "-p [port] use different working port (default is 37)" << endl <<
            "-d enable debugging output (default is off)" << endl;
    exit(0);
}

int main(int argc, char* argv[])
{
    int c;
    bool oflag = true;
    bool ipflag =false;
    bool udpflag = true;
    int portflag = 37;
    sa_family_t ip;

    Server_ *server;
    optarg = NULL;
    while((c = getopt(argc, argv, "diup:h")) != -1)
        switch(c)
        {
        case 'd':
            oflag = true;
            break;
        case 'i':
            ipflag = true;
            break;
        case 'u':
            udpflag = true;
            break;
        case 'p':
            portflag = atoi(optarg);
            break;
        case 'h':
            show_help();
            break;
        default:
            show_help();
        }

    if(ipflag)
        ip = AF_INET6;
    else
        ip = AF_INET;
    if(udpflag)
    {
        server= new UDP_Socket(ip, oflag, portflag);
    }
    else
    {
        server = new TCP_Socket(ip, oflag, portflag);
    }
    delete server;
    return 0;
}

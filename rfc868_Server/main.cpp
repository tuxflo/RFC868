#include <iostream>
#include <unistd.h>
#include <errno.h>

#include "server.h"
#include "tcp_socket.h"
#include "udp_socket.h"

using namespace std;


void show_help()
{
    cout << "Usage:" << endl <<
            "if executed without arguments it will use the default setting" << endl <<
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
    //Set up the default settings
    bool oflag = true;
    bool ipflag =false;
    bool udpflag = false;
    int portflag = 1025;

    sa_family_t ip;
    Server *server;
    optarg = 0;

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

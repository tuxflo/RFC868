#include <iostream>



#include "client.h"
#include "tcp_client.h"
#include "udp_client.h"

//Client part

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

int main(int argc, char *argv[])
{
    int c;

    //Set default options
    bool oflag = true;
    bool ipflag =false;
    bool udpflag = true;
    int portflag = 1025;
    sa_family_t ip;

    Client *client;
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

    if(oflag)
        cout << "RFC868 Client started!" << endl;

    if(ipflag)
        ip = AF_INET6;
    else
        ip = AF_INET;
    if(udpflag)
    {
        client= new udp_client(ip, oflag, portflag);
    }
    else
    {
        client = new tcp_client(ip, oflag, portflag);
    }
    if(client->recieve_time() == 0)
    {
        cout << "Time recieved: " << client->get_rfc_time() << "(Seconds since 1.1.1900)" << endl;
        cout << "Time difference between server and client: " << time(0) + 2208988800U - client->get_rfc_time() << " seconds!" << endl;
    }
    delete client;

    return 0;
}


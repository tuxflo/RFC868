#include "udp_socket.h"

using namespace std;
UDP_Socket::UDP_Socket(sa_family_t IP, bool oflag, int port)
{


    setflags(oflag, port);
    if(oflag)
        cout << "starting rfc868 server..." << endl <<
                "using protocol: UPD" << endl <<
                "using port: " << port << endl;

    socketfd = socket(IP, SOCK_DGRAM, 0);
    if(socketfd < 0)
    {
        error("ERROR while opening socket!");
        exit(-1);
    }
    server_addr.sin_family = IP;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = INADDR_ANY;
    if(bind(socketfd, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0)
        error("ERROR while binding!");
    if(oflag)
        cout << "waiting on port " << port << " ..." << endl;
    send_time();
}

UDP_Socket::~UDP_Socket()
{
    close(socketfd);
}

void UDP_Socket::send_time()
{
    client_length = sizeof(struct sockaddr_in);

    while(running)
    {
        //Recieve 0 Byte data to get the destination adress structure
        int n = recvfrom(socketfd, 0, 0, 0, (struct sockaddr *) &client_addr, &client_length);

        //Check if SIGINT was send
        if(quit)
            break;

        if(n < 0)
            error("Error while recieving!");
        if(oflag)
            cout << "client connected: " << inet_ntoa(client_addr.sin_addr) << endl;
        rfc_time = time(0) + 2208988800U;
        ret = sendto(socketfd, &rfc_time, sizeof(rfc_time), 0, (struct sockaddr *)&client_addr, client_length);
        if(ret < 0)
            error("ERROR while sending time!");
        if(oflag)
            cout << "time sent (" << rfc_time << ") seconds since 1.1.1900" << endl;
    }
}



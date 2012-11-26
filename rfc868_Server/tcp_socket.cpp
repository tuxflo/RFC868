#include "tcp_socket.h"

using namespace std;
TCP_Socket::TCP_Socket(sa_family_t IP, bool oflag, int port)
{
    setflags(oflag, port);
    if(oflag)
        cout << "starting rfc868 server..." << endl;
    socketfd = socket(IP, SOCK_STREAM, 0);
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
        cout << "listening on port: " << port << endl;
    listen(socketfd, 5);
}

bool TCP_Socket::listen_accept()
{
    running = true;
    while(running)
    {
        client_length = sizeof(client_addr);
        newsockfd = accept(socketfd, (struct sockaddr*) &client_addr, &client_length);
        if(newsockfd < 0)
        {
            error("ERROR while accepting!");
            return false;
        }
        if(oflag)
            cout << "client connected: " << inet_ntoa(client_addr.sin_addr) << endl;
        send_time();
    }
    return true;
}

void TCP_Socket::send_time()
{
    int ret;
    unsigned int rfc_time = time(0) + 2208988800U;
    ret = write(newsockfd, &rfc_time, sizeof(rfc_time));
    if(ret < 0)
        error("ERROR while writing to socket!");
    if(oflag)
        cout << "time sent(" << rfc_time << ") seconds since 1.1.1900" << endl;
    close(newsockfd);
}

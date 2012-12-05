#include "tcp_client.h"

using namespace std;
tcp_client::tcp_client(sa_family_t IP, bool oflag, int port)
{
    socketfd = socket(IP, SOCK_STREAM, 0);
    if(socketfd < 0)
        error("ERROR while opening socket!");

    server = findserver(server, 5);
    server_addr.sin_family = IP;
    server_addr.sin_port = htons(port);
    memcpy((char *) &server_addr.sin_addr.s_addr, (char *)server->h_addr, server->h_length);
    if(connect(socketfd,(struct sockaddr *) &server_addr, sizeof(server_addr)) < 0)
        error("ERROR while connecting to server!");

}

tcp_client::~tcp_client()
{
    close(socketfd);
    cout << "Destructor!" << endl;
}

int tcp_client::recieve_time()
{
    ret = read(socketfd, &rfc_time, sizeof(rfc_time));
    if(ret < 0)
        error("ERROR while reading from socket!");
    return 0;
}

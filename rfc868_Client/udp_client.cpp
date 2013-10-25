#include "udp_client.h"

using namespace std;
udp_client::udp_client(sa_family_t IP, bool oflag, int port)
{
    socketfd = socket(IP, SOCK_DGRAM, 0);
    if(socketfd < 0)
        error("ERROR while opening socket!");

    server = findserver(server, 5);
    server_addr.sin_family = IP;
    server_addr.sin_port = htons(port);
    //memcpy((char *) &server_addr.sin_addr.s_addr, (char *)server->h_addr, server->h_length);
}

udp_client::~udp_client()
{
    //do cleamup here...
}

void udp_client::recieve_time()
{
    //In UDP I send a dummy message containing 'a' to get the adressdata of the server
    length = sizeof(struct sockaddr_in);
    char buf[] = {'a'};
    int n = sendto(socketfd, buf, 1, 0, (const struct sockaddr *) &server_addr, length);
    if(n < 0)
        error("ERROR while sending!");
    ret = recvfrom(socketfd, &rfc_time, sizeof(rfc_time), 0, (struct sockaddr *) &other, &length);
    if(ret < 0)
        error("ERROR while reading from socket!");
}

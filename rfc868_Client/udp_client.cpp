#include "udp_client.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

using namespace std;
udp_client::udp_client(sa_family_t IP, bool oflag, int port)
{
    socketfd = socket(IP, SOCK_DGRAM, 0);
    if(socketfd < 0)
        error("ERROR while opening socket!");

    server = findserver(server, 5);
    server_addr.sin_family = IP;
    server_addr.sin_port = htons(port);

}

udp_client::~udp_client()
{
    close(socketfd);
    cout << "Destructor!" << endl;

}

int udp_client::recieve_time()
{
    //In UDP I send a 0 Byte package get the adressdata of the server
       length = sizeof(struct sockaddr_in);

       int n = sendto(socketfd, 0, 0, 0, (const struct sockaddr *) &server_addr, length);
       if(n < 0)
           error("ERROR while sending!");
       ret = recvfrom(socketfd, &rfc_time, sizeof(rfc_time), 0, (struct sockaddr *) &other, &length);
       if(quit)
           return -1;
       if(ret < 0)
           error("ERROR while reading from socket!");
       return 0;
}

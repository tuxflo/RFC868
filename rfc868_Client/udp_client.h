#ifndef UDP_CLIENT_H
#define UDP_CLIENT_H
#include "client.h"
class udp_client : public Client
{
public:
    udp_client(sa_family_t IP, bool oflag, int port);
    ~udp_client();
    int recieve_time();
private:
    struct sockaddr_in other;
};

#endif // UDP_CLIENT_H

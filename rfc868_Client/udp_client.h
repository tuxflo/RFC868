#ifndef UDP_CLIENT_H
#define UDP_CLIENT_H
#include "client_.h"
class udp_client : public client_
{
public:
    udp_client(sa_family_t IP, bool oflag, int port);
    ~udp_client();
    void recieve_time();
private:
    struct sockaddr_in other;
};

#endif // UDP_CLIENT_H

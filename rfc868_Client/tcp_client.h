#ifndef TCP_CLIENT_H
#define TCP_CLIENT_H
#include "client_.h"

class tcp_client : public client_
{
public:
    tcp_client(sa_family_t IP, bool oflag, int port);
    ~tcp_client();
    void recieve_time();
};

#endif // TCP_CLIENT_H

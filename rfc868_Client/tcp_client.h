#ifndef TCP_ClientH
#define TCP_ClientH
#include "client.h"

class tcp_client : public Client
{
public:
    tcp_client(sa_family_t IP, bool oflag, int port);
    ~tcp_client();
    int recieve_time();
};

#endif // TCP_ClientH

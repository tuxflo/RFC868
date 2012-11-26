#ifndef RFC_SOCKET_H
#define RFC_SOCKET_H

#include "server_.h"

class TCP_Socket : public Server_
{
public:
    TCP_Socket(sa_family_t ip, bool oflag, int port);
    ~TCP_Socket();
    void send_time();
    bool listen_accept();
    void open_socket(sa_family_t IP);

};

#endif // RFC_SOCKET_H

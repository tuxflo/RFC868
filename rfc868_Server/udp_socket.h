#ifndef UDP_SOCKET_H
#define UDP_SOCKET_H
#include "server_.h"

class UDP_Socket : public Server_
{
public:
    UDP_Socket(sa_family_t IP, bool oflag, int port);
    bool listen_accept();
    void open_socket(sa_family_t IP);
    void send_time();
private:
    socklen_t fromlen;
};

#endif // UDP_SOCKET_H

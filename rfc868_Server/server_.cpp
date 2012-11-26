#include "server_.h"

using namespace std;
Server_::Server_()
{
}

Server_::~Server_()
{
    close(socketfd);
    close(newsockfd);
}

void Server_::setflags(bool oflag, int port)
{
    this->oflag = oflag;
    this->port = port;
}

void Server_::error(const char *msg)
{
    cerr << msg << "(" << strerror(errno) << ")" << endl;
    exit(-1);
}

#include "server.h"

using namespace std;
bool Server::quit = false;

Server::Server()
{
    running = true;

    end_process.sa_handler = get_signal;
    sigemptyset(&end_process.sa_mask);
    end_process.sa_flags = SA_SIGINFO;

    sigaction(SIGINT, &end_process, 0);
}

Server::~Server()
{
    close(socketfd);
    close(newsockfd);
}

void Server::setflags(bool oflag, int port)
{
    this->oflag = oflag;
    this->port = port;
}

void Server::error(const char *msg)
{
    cerr << msg << "(" << strerror(errno) << ")" << endl;
    exit(-1);
}

void Server::get_signal(int sig)
{
    quit = true;
}

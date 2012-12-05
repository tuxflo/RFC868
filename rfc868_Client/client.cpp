#include "client.h"

using namespace std;
bool Client::quit = false;

Client::Client()
{
    //Set up signalhandler for caching SIGINT
    end_process.sa_handler = get_signal;
    sigemptyset(&end_process.sa_mask);
    end_process.sa_flags = SA_SIGINFO;

    sigaction(SIGINT, &end_process, 0);
}

Client::~Client()
{

}

struct hostent* Client::findserver(struct hostent* server, int attempt)
{
    if(attempt == 0)
    {
        cout << "Still no server found, exiting now..." << endl;
        exit(1);
    }
    string hostname;
    cout << "Please enter the Hostname or IP Adress of the Server: " << endl;
    cin >> hostname;
    if(quit)
    {
        close(socketfd);
        exit(-1);
    }
    server = gethostbyname(hostname.c_str());
    if(server == 0)
    {
        cout << "Could not find server Please try again!" << endl;
        return findserver(server, attempt -1);
    }
    else
        return server;
}

void Client::error(const char *msg)
{
    cerr << msg << " (" << strerror(errno) << ")" << endl;
    exit(1);
}

unsigned int Client::get_rfc_time()
{
    return rfc_time;
}

void Client::setflags(bool oflag, int port)
{
    this->oflag = oflag;
    this->port = port;
}

void Client::get_signal(int sig)
{
    quit = true;
}

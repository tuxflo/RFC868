#include "client_.h"

using namespace std;

client_::client_()
{
}

client_::~client_()
{

}

struct hostent* client_::findserver(struct hostent* server, int attempt)
{
    if(attempt == 0)
    {
        cout << "Still no server found, exiting now..." << endl;
        exit(1);
    }
    string hostname;
    cout << "Please enter the Hostname or IP Adress of the Server: " << endl;
    cin >> hostname;
    server = gethostbyname(hostname.c_str());
    if(server == 0)
    {
        cout << "Could not find server Please try again!" << endl;
        return findserver(server, attempt -1);
    }
    else
        return server;
}

void client_::error(const char *msg)
{
    cerr << msg << strerror(errno) << endl;
    exit(1);
}

unsigned int client_::get_rfc_time()
{
    return rfc_time;
}

void client_::setflags(bool oflag, int port)
{
    this->oflag = oflag;
    this->port = port;
}

#include <iostream>
#include <unistd.h>
#include <string>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

//Client part

using namespace std;

void error(const char * msg)
{
    cerr << msg << strerror(errno) << endl;
    exit(1);
}

struct hostent* findserver(struct hostent* server, int attempt)
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

int main()
{
    int socketfd, ret;
    struct sockaddr_in server_addr;
    struct hostent *server;
    unsigned int rfc_time;

    cout << "RFC868 Client started!" << endl;
        socketfd = socket(AF_INET, SOCK_STREAM, 0);
        if(socketfd < 0)
            error("ERROR while opening socket!");
        server = findserver(server, 5);
        if(server == 0)
            error("ERROR no server found!");
        server_addr.sin_family = AF_INET;
        server_addr.sin_port = htons(37);
        memcpy((char *) &server_addr.sin_addr.s_addr, (char *)server->h_addr, server->h_length);
        if(connect(socketfd,(struct sockaddr *) &server_addr, sizeof(server_addr)) < 0)
            error("ERROR while connecting to server!");
        ret = read(socketfd, &rfc_time, sizeof(rfc_time));
        if(ret < 0)
            error("ERROR while reading from socket!");
        close(socketfd);

        cout << "time recieved from server: " << rfc_time << endl;
    return 0;
}


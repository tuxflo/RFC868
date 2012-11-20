#include <iostream>
#include <sys/socket.h>
#include <cstring>
#include <string>
#include <netdb.h>
#include <ctime>
#include <unistd.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <errno.h>
#include <pthread.h>

using namespace std;
void error(const char* msg)
{
    cerr << msg << " " << "(" << strerror(errno) << ")" << endl;
    exit(1);
}

void *send_time(void *socketfd)
{
    unsigned int rfc_time = time(0) + 2208988800U;
    int ret = write((int)socketfd, &rfc_time, sizeof(rfc_time));
    if(ret < 0)
        error("ERROR while writing to socket!");
    cout << "time sent(" << rfc_time << ") seconds since 1.1.1900" << endl;
    close((int)socketfd);
    pthread_exit(0);
}

int main()
{

    int socketfd, newsockfd, ret;
    pthread_t thread;
    socklen_t clientlen;
    struct sockaddr_in server_addr, client_addr;
    cout << "Starting rfc868 server!" << endl << "Time is: " << time(0) + 2208988800U << endl;
        socketfd = socket(AF_INET, SOCK_STREAM, 0);
        if(socketfd < 0)
            error("ERROR while opening socket!");
        server_addr.sin_family = AF_INET;
        server_addr.sin_port = htons(37); //37 is the default port for rfc868
        server_addr.sin_addr.s_addr = INADDR_ANY; //Address of the machine where the server is running
        if(bind(socketfd, (struct sockaddr *) &server_addr, sizeof(server_addr)) <  0)
                error("ERROR while binding!");
        listen(socketfd, 5);

        while(1)    //loop because server is running infinitely
        {
            clientlen = sizeof(client_addr);
            newsockfd = accept(socketfd, (struct sockaddr *) &client_addr, &clientlen);
            if(newsockfd < 0)
                error("ERROR while accepting!");
            cout << "client connected: " << inet_ntoa(client_addr.sin_addr) << endl;
            ret = pthread_create(&thread, NULL, send_time, (void *)newsockfd);
            pthread_join(thread, 0);
        }
    return 0;
}

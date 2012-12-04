#include "tcp_socket.h"

using namespace std;
TCP_Socket::TCP_Socket(sa_family_t IP, bool oflag, int port)
{
    //Set up the signal and signal handler



    setflags(oflag, port);
    if(oflag)
        cout << "starting rfc868 server..." << endl <<
                "using protocol: TCP" << endl <<
                "using port: " << port << endl;

    socketfd = socket(IP, SOCK_STREAM, 0);
    if(socketfd < 0)
    {
        error("ERROR while opening socket!");
        exit(-1);
    }
    server_addr.sin_family = IP;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = INADDR_ANY;
    if(bind(socketfd, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0)
        error("ERROR while binding!");
    if(oflag)
        cout << "listening on port " << port << " ..." << endl;
    listen(socketfd, 5);
    send_time();
}

TCP_Socket::~TCP_Socket()
{
    close(newsockfd);
    close(socketfd);
}

void TCP_Socket::send_time()
{
    while(running)
    {
        client_length = sizeof(client_addr);
        newsockfd = accept(socketfd, (struct sockaddr*) &client_addr, &client_length);

        //Check if SIGINT was send...
        if(quit)
            break;

        if(newsockfd < 0)
        {
            error("ERROR while accepting!");
        }

        if(oflag)
            cout << "client connected: " << inet_ntoa(client_addr.sin_addr) << endl;        
        rfc_time = time(0) + 2208988800U;
        ret = write(newsockfd, &rfc_time, sizeof(rfc_time));
        if(ret < 0)
            error("ERROR while writing to socket!");
        if(oflag)
            cout << "time sent (" << rfc_time << ") seconds since 1.1.1900" << endl;
        close(newsockfd);
    }
}

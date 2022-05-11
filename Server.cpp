#include "Server.h"
#include "Common.h"

#include "cstring"

Server::Server(unsigned int port)
{
    m_port = port;

    init();
}

Server::~Server()
{
    
}

void Server::init()
{
    struct sockaddr_in address;
    bzero(&address, sizeof(address));
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = htonl(INADDR_ANY);
    address.sin_port = htons(m_port);

    int listenfd = socket(AF_INET, SOCK_STREAM, 0);
    Bind(listenfd, (SA *)&address, sizeof(address));

    Listen(listenfd, BACKLOG);

    for (; ;)
    {
        int connfd = Accept(listenfd, (SA *) NULL, NULL);

        char buf[MAXLINE];
        time_t tricks;
        snprintf(buf, sizeof(buf), "%.24s\r\n", ctime(&tricks));
        
        Write(connfd, buf, sizeof(buf));
        Close(connfd);
    }
}
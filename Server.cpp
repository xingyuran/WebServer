#include "Server.h"
#include "Common.h"
#include "Define.h"

#include <fcntl.h>
#include <sys/epoll.h>

Server::Server(unsigned int port)
{
    m_port = port;
}

Server::~Server()
{
    
}

void Server::run()
{
    
}

void Server::setnonBlocking(int sock)
{
    int opt;
    opt = fcntl(sock, F_GETFL);
    if (opt < 0)
    {
        LOG("[fcntl]F_GETFL error");
        exit(1);
    }
    opt = opt | O_NONBLOCK;
    if (fcntl(sock, F_SETFL, sock))
    {
        LOG("[fcntl]F_SETFL error");
        exit(1);
    }
}

void Server::addfd(int epollfd, int fd)
{
    struct epoll_event ev;

    ev.events = EPOLLIN;
    ev.data.fd = listenfd;
    ev.events = EPOLLIN | EPOLLET;

    epoll_ctl(epollfd, EPOLL_CTL_ADD, fd, &ev);
    setnonBlocking(fd);
}

void Server::epoll_Event()
{
    struct sockaddr_in address;
    bzero(&address, sizeof(address));
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = htonl(INADDR_ANY);
    address.sin_port = htons(m_port);

    int listenfd = socket(AF_INET, SOCK_STREAM, 0);

    Bind(listenfd, (SA *)&address, sizeof(address));
    Listen(listenfd, BACKLOG);

    struct epoll_event events[EPOLLEVENTNUM];

    int epollfd = epoll_create(EPOLLNUM);
    if (epollfd == -1)
    {
        LOG("[epoll]epoll_create error");
        exit(1);
    }

    addfd(epollfd, listenfd);

    for (; ;)
    {
        int nfds = epoll_wait(epollfd, events, EPOLLNUM, 500);

        for (size_t i = 0; i < nfds; i++)
        {
            //new conn
            if (events[i].data.fd == listenfd)
            {
                int connfd = Accept(listenfd, (SA *) NULL, NULL);
                Sock connSock(connfd);
                m_socks.AddTask(connSock);
            }
            //conn data
            else
            {

            }
        }
    }
}
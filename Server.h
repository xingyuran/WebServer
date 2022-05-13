#ifndef _SERVER_H_
#define _SERVER_H_

#include "Sock.h"
#include "ThreadPool.h"

class Server
{
public:
    explicit Server(unsigned int port = 80);
    ~Server();

    void run();
    void setnonBlocking(int sock);
    void epoll_Event();
    void addfd(int epollfd, int fd);

private:
    unsigned int m_port;



    ThreadPool<Sock> m_socks;
};

#endif
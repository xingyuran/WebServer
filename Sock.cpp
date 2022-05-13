#include "Sock.h"
#include "Common.h"
#include "Define.h"

Sock::Sock(int sockfd)
    : m_sockfd(sockfd)
{

}

Sock::~Sock()
{

}

void Sock::Start()
{
    char buf[MAXLINE];
    time_t tricks;
    snprintf(buf, sizeof(buf), "%.24s\r\n", ctime(&tricks));
    
    Write(m_sockfd, buf, sizeof(buf));
    Close(m_sockfd);
}
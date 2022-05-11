#ifndef _COMMON_H_
#define _COMMON_H_

#include "netinet/in.h"

#include "Log.h"
#include "Define.h"

static void Bind(int sockfd, SA * address, socklen_t n)
{
    int ret = bind(sockfd, address, n);
    if (ret == -1)
    {
        LOG("[bind error]%s\r\n", strerror(errno));
        assert(0);
    }
    return;
}

static void Listen(int sockfd, int n)
{
    int ret = listen(sockfd, n);
    if (ret == -1)
    {
        LOG("[listen error]%s\r\n", strerror(errno));
        assert(0);
    }
    return;
}

static int Accept(int sockfd, SA * address, socklen_t * n)
{
    int connfd = accept(sockfd, address, n);
    if (connfd == -1)
    {
        LOG("[accept error]%s\r\n", strerror(errno));
        assert(0);
    }
    return connfd;
}

static void Write(int sockfd, const void * buf, size_t len)
{
    int ret = write(sockfd, buf, len);
    if (ret == -1)
    {
        LOG("[write error]%s\r\n", strerror(errno));
        assert(0);
    }
    return;
}

static void Close(int sockfd)
{
    int ret = close(sockfd);
    if (ret == -1)
    {
        LOG("[close error]%s\r\n", strerror(errno));
        assert(0);
    }
    return;
}

#endif
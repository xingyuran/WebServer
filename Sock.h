#ifndef _SOCK_H_
#define _SOCK_H_

class Sock
{
public:
    explicit Sock(int sockfd);
    ~Sock();

private:
    void Start();

private:
    int m_sockfd;

};

#endif
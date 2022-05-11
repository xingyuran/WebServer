#ifndef _SERVER_H_
#define _SERVER_H_

class Server
{
public:
    explicit Server(unsigned int port = 80);
    ~Server();

private:
    void init();

private:
    unsigned int m_port;
};

#endif
#include "Server.h"

#include "netinet/in.h"
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
}
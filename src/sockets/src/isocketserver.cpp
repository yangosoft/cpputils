

#include <arpa/inet.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <netinet/in.h>
#include <sys/types.h>
#include <unistd.h>

#include <iostream>
#include "sockets/socket.h"
#include "sockets/isocketserver.h"

using namespace CppUtils;

ISocketServer::ISocketServer(uint32_t port, OnNewClientCallback onNewClientCallback): m_port(port), m_fdSocket(-1), fCallback(std::move(onNewClientCallback))
{
    
}

ISocketServer::ISocketServer(const ISocketServer &other)
{
    m_fdSocket = other.m_fdSocket;
    m_port = other.m_port;
    fCallback = other.fCallback;    
}
    
ISocketServer& ISocketServer::operator=(const ISocketServer &other)
{
    m_fdSocket = other.m_fdSocket;
    m_port = other.m_port;
    fCallback = other.fCallback;
    
    return *this;
}

int ISocketServer::serverListen()
{
    int32_t status = listen(m_fdSocket, 1024);
    if ( 0 != status )
    {
        std::cerr << "Something went wrong in listen" << std::endl;  
    }
    
    return status;
}


void ISocketServer::disconnect()
{
    close(m_fdSocket);
}

void ISocketServer::doAccept()
{
    int32_t fdClient = accept(m_fdSocket, nullptr, nullptr);
    auto s = std::make_unique<Socket>(fdClient);
    fCallback(std::move(s));
}

int ISocketServer::getFdSocket() const
{
    return m_fdSocket;
}

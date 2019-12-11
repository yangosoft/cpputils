
#include "sockets/isocket.h"


#include <cstdio>
#include <iostream>

#include <sys/socket.h>
#include <sys/types.h>



using namespace CppUtils;

ISocket::ISocket(int32_t fdSocket): m_fdSocket(fdSocket){

}

ISocket::ISocket(const ISocket &other)
{
    m_fdSocket = other.m_fdSocket;
}
    
ISocket& ISocket::operator=(const ISocket &other)
{
    m_fdSocket = other.m_fdSocket;
    return *this;
}



bool ISocket::writeString(const std::string& data) const
{
    std::cerr << __PRETTY_FUNCTION__ << std::endl;
    ssize_t n = writeData(data.c_str(),data.size());
    return (n == static_cast<ssize_t>(data.size()));
}


bool ISocket::readString(std::string &data) const
{
    std::cerr << __PRETTY_FUNCTION__ << std::endl;
    char buffer[256]{};
    size_t n = readData(buffer,sizeof(buffer));
    if(( n > 0 ) && ( n < sizeof(buffer)))
    {
        buffer[n] = '\0';
        data = std::string(buffer);
    }
    
    return (n == static_cast<size_t>(data.size()));   
}

ssize_t ISocket::writeData(const char *data, size_t size) const
{
    if ( -1 == m_fdSocket )
    {
        std::cerr << "Wrong socket FD -1" << std::endl;
    }
    std::cerr << __PRETTY_FUNCTION__ << std::endl;
    ssize_t n = send(m_fdSocket, data, size,MSG_NOSIGNAL);
    return n;
}

ssize_t ISocket::readData(char* buffer, ssize_t size) const
{
    if ( -1 == m_fdSocket )
    {
        std::cerr << "Wrong socket FD -1" << std::endl;
    }
    std::cerr << __PRETTY_FUNCTION__ << std::endl;


    ssize_t len = recv(m_fdSocket, buffer, size,MSG_NOSIGNAL);
    if (len <= 0)
    {
        //Client disconnected
        std::cerr << "Client " << m_fdSocket << " disconnected" << std::endl;
        close(m_fdSocket);
    }

    return len;
}

void ISocket::disconnect()
{
    if(m_fdSocket > 0)
    {
        close(m_fdSocket);
    }
}

int32_t ISocket::getFdSocket() const
{
    return m_fdSocket;
}



#include <cstdio>
#include <iostream>

#include "sockets/isocket.h"

using namespace CppUtils;

ISocket::ISocket(int32_t fdSocket): m_fdSocket(fdSocket){

}


ssize_t ISocket::writeData(const char *data, size_t size) const
{
    ssize_t n = write(m_fdSocket, data, size);
    return n;
}

ssize_t ISocket::readData(char* buffer, ssize_t size) const
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;


    ssize_t len = read(m_fdSocket, buffer, size);
    if (len <= 0)
    {
        //Client disconnected
        std::cout << "Client " << m_fdSocket << " disconnected" << std::endl;
        close(m_fdSocket);
    }

    return len;
}

bool ISocket::writeData(const std::string& data) const
{
    ssize_t n = writeData(data.c_str(),data.size());
    return (n == static_cast<ssize_t>(data.size()));
}


ssize_t ISocket::readData(std::string &data) const
{
    char buffer[256]{};
    ssize_t n = readData(buffer,sizeof(buffer));
    if ( n > 0 )
    {
        buffer[n] = '\0';
        data = std::string(buffer);
    }
    
    return n;
    
}

void ISocket::disconnect()
{
    close(m_fdSocket);
}

int32_t ISocket::getFdSocket() const
{
    return m_fdSocket;
}


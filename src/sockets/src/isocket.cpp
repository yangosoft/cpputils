
#include <cstdio>
#include <iostream>

#include "sockets/isocket.h"

using namespace CppUtils;

ISocket::ISocket(int32_t fdSocket): m_fdSocket(fdSocket){

}




bool ISocket::writeString(const std::string& data) const
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    ssize_t n = writeData(data.c_str(),data.size());
    return (n == static_cast<ssize_t>(data.size()));
}


bool ISocket::readString(std::string &data) const
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    char buffer[256]{};
    size_t n = readData(buffer,sizeof(buffer));
    if(( n > 0 ) && ( n < sizeof(buffer)))
    {
        buffer[n] = '\0';
        data = std::string(buffer);
    }
    
    return (n == static_cast<size_t>(data.size()));
    
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


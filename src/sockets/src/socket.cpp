

#include <iostream>

#include "sockets/socket.h"


using namespace CppUtils;

Socket::Socket(int32_t fdSocket) : ISocket(fdSocket)
{
}



ssize_t Socket::writeData(const char *data, size_t size) const
{
    if ( -1 == m_fdSocket )
    {
        std::cout << "Wrong socket FD -1" << std::endl;
    }
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    ssize_t n = write(m_fdSocket, data, size);
    return n;
}

ssize_t Socket::readData(char* buffer, ssize_t size) const
{
    if ( -1 == m_fdSocket )
    {
        std::cout << "Wrong socket FD -1" << std::endl;
    }
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


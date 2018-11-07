
#include <cstdio>
#include <iostream>

#include "sockets/securesocket.h"

using namespace CppUtils;

SecureSocket::SecureSocket(int32_t fdSocket, gnutls_session_t& session) : ISocket(fdSocket),
m_session(session)
{

}

ssize_t SecureSocket::writeData(const char *data, size_t size) const
{
    ssize_t n = gnutls_record_send(m_session, data, size);
    return n;
}

ssize_t SecureSocket::readData(char* buffer, ssize_t size) const
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    ssize_t len = gnutls_record_recv(m_session, buffer, size);

    
//    if (ret < 0
//                                   && gnutls_error_is_fatal(ret) == 0) {
//                                fprintf(stderr, "*** Warning: %s\n",
//                                        gnutls_strerror(ret));
//                        } else if (ret < 0) {
//                                fprintf(stderr, "\n*** Received corrupted "
//                                        "data(%d). Closing the connection.\n\n",
//                                        ret);
    
    if (len == 0)
    {
        //Client disconnected
        std::cout << "Client " << m_fdSocket << " disconnected" << std::endl;
    }

    return len;
}


void SecureSocket::disconnect()
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;
//    gnutls_bye(m_session, GNUTLS_SHUT_WR);
    close(m_fdSocket);
}




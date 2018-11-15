
#ifndef SECURESOCKET_H
#define	SECURESOCKET_H

#include <sys/types.h>
#include <unistd.h>

#include <cstdint>
#include <string>

#include <gnutls/gnutls.h>
#include "isocket.h"

namespace CppUtils
{


class SecureSocket : public ISocket  {
public:
    SecureSocket(int32_t fdSocket, gnutls_session_t& session);
    void disconnect() override;
    ssize_t writeData(const char *data, size_t size) const override;    
    ssize_t readData(char *buffer, ssize_t size) const override;
//    bool writeData(const std::string &data) const override{ return ISocket::writeData(data); };    
//    ssize_t readData(std::string &data) const override { return ISocket::readData(data); };
    
    virtual ~SecureSocket() = default;

protected:
    int32_t m_fdSocket;
    gnutls_session_t& m_session;
   

};
};
#endif	/* SECURESOCKET_H */

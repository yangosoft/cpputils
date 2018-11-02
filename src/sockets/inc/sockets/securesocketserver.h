#ifndef SECURESOCKETSERVER_H
#define	SECURESOCKETSERVER_H


#include <gnutls/gnutls.h>
#include <gnutls/x509.h>

#include <cstdint>
#include <functional>

#include "isocket.h"

namespace CppUtils
{

using OnNewClientCallback =  std::function< void(ISocket fdClient) >;


class SecureSocketServer  {
  
public:
    SecureSocketServer(uint32_t port, OnNewClientCallback onNewClientCallback);
    
    int serverListen();
    void doAccept();
    
    
    virtual void disconnect();
    
    virtual ~SecureSocketServer() = default;
    
    
private:
    uint32_t m_port;
    uint32_t m_fdSocket;
    OnNewClientCallback fCallback;
    
    gnutls_datum_t out;    
    
    
    gnutls_certificate_credentials_t x509_cred;
    gnutls_priority_t priority_cache;
    
    gnutls_session_t session;
    
};
}

#endif

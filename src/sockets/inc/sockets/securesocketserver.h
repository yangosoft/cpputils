#ifndef SECURESOCKETSERVER_H
#define	SECURESOCKETSERVER_H


#include <gnutls/gnutls.h>
#include <gnutls/x509.h>

#include <cstdint>
#include <functional>

#include "isocket.h"
#include "sockets/isocketserver.h"

namespace CppUtils
{




class SecureSocketServer : public ISocketServer  {
  
public:
    SecureSocketServer(uint32_t port, std::string certificate, std::string key, OnNewClientCallback onNewClientCallback);
    
    
    void doAccept() override;
    
    
    void disconnect() override;
    
    virtual ~SecureSocketServer() = default;
    
    
protected:
    
    std::string m_certificate;
    std::string m_key;
   
    gnutls_datum_t out;        
    gnutls_certificate_credentials_t x509_cred;
    gnutls_priority_t priority_cache; 
    gnutls_session_t session;
};
}

#endif

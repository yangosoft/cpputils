#ifndef CPPUTILS_SECURESOCKETCLIENT_H
#define CPPUTILS_SECURESOCKETCLIENT_H

#include <string>

#include "isocketclient.h"
#include "securesocket.h"

namespace CppUtils {

/**
 * @todo write docs
 */
class SecureSocketClient : public ISocketClient, public SecureSocket
{
public:
    /**
     * Default constructor
     */
    SecureSocketClient(std::string ip, uint16_t port, std::string certificatePath, std::string keyPath, std::string serverName);

    int32_t tryConnect() override;
    void disconnect() override;
    
    
    /**
     * Destructor
     */
    virtual ~SecureSocketClient();
    
private:
    gnutls_session_t session;
    gnutls_datum_t out;
    gnutls_certificate_credentials_t xcred;
    std::string m_certificate;
    std::string m_key;
    std::string m_serverName;
    

};

}

#endif // CPPUTILS_SECURESOCKETCLIENT_H

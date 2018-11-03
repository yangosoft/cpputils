#ifndef CPPUTILS_SECURESOCKETCLIENT_H
#define CPPUTILS_SECURESOCKETCLIENT_H

#include <string>

#include "socketclient.h"

namespace CppUtils {

/**
 * @todo write docs
 */
class SecureSocketClient : public SocketClient
{
public:
    /**
     * Default constructor
     */
    SecureSocketClient(std::string ip, uint16_t port, std::string certificatePath, std::string keyPath);

    bool tryConnect() override;
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

};

}

#endif // CPPUTILS_SECURESOCKETCLIENT_H

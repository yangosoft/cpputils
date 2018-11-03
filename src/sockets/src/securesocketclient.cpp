
#include <gnutls/gnutls.h>
#include <gnutls/x509.h>

#include <iostream>

#include "sockets/securesocketclient.h"

using namespace CppUtils;

SecureSocketClient::SecureSocketClient(std::string ip, uint16_t port,std::string certificate, std::string key):
    SocketClient(std::move(ip),port),
    m_certificate(certificate),
    m_key(key)
{

}

SecureSocketClient::~SecureSocketClient()
{
    if(m_fdSocket != -1)
    {
        disconnect();
    }
}

bool SecureSocketClient::tryConnect()
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    bool retConnect = SocketClient::tryConnect();

    /* for backwards compatibility with gnutls < 3.3.0 */
    gnutls_global_init();

    /* X509 stuff */
    gnutls_certificate_allocate_credentials(&xcred);

    /* sets the system trusted CAs for Internet PKI */
    gnutls_certificate_set_x509_system_trust(xcred);

    /* If client holds a certificate it can be set using the following:
     */
    gnutls_certificate_set_x509_key_file2 (xcred, m_certificate.c_str(), m_key.c_str(),                              GNUTLS_X509_FMT_PEM,"cpputils",0);


    /* Initialize TLS session */
    gnutls_init(&session, GNUTLS_CLIENT);

//     gnutls_server_name_set(session, GNUTLS_NAME_DNS, "my_host_name", strlen("my_host_name"));

    /* It is recommended to use the default priorities */
    gnutls_set_default_priority(session);

    /* put the x509 credentials to the current session
     */
    gnutls_credentials_set(session, GNUTLS_CRD_CERTIFICATE, xcred);
//     gnutls_session_set_verify_cert(session, "my_host_name", 0);

    gnutls_transport_set_int(session, m_fdSocket);
    gnutls_handshake_set_timeout(session,  GNUTLS_DEFAULT_HANDSHAKE_TIMEOUT);
    int32_t ret;
     gnutls_certificate_type_t type;
    uint32_t status;
    /* Perform the TLS handshake
     */
    do {
        ret = gnutls_handshake(session);
    }
    while (ret < 0 && gnutls_error_is_fatal(ret) == 0);
   
    if (ret < 0) {
        if (ret == GNUTLS_E_CERTIFICATE_VERIFICATION_ERROR) {
            /* check certificate verification status */
            type = gnutls_certificate_type_get(session);
            status = gnutls_session_get_verify_cert_status(session);
             gnutls_certificate_verification_status_print(status,type, &out, 0);
             printf("cert verify output: %s\n", out.data);
             gnutls_free(out.data);
        }
        std::string err{gnutls_strerror(ret)};
        err = "Handshake failed " + err;
        std::cout << err << std::endl;
        throw std::logic_error(err);
    }



    return retConnect;
}

void SecureSocketClient::disconnect()
{

    close(m_fdSocket);
    m_fdSocket = -1;
    gnutls_deinit(session);

    gnutls_certificate_free_credentials(xcred);

    gnutls_global_deinit();
}


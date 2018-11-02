


#include <arpa/inet.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <netinet/in.h>
#include <sys/types.h>
#include <unistd.h>

#include <iostream>

#include "sockets/securesocket.h"
#include "sockets/securesocketserver.h"



using namespace CppUtils;


#define KEYFILE "key.pem"
#define CERTFILE "cert.pem"
#define CAFILE "/etc/ssl/certs/ca-certificates.crt"
#define CRLFILE "crl.pem"
/* The OCSP status file contains up to date information about revocation
 * of the server's certificate. That can be periodically be updated
 * using:
 * $ ocsptool --ask --load-cert your_cert.pem --load-issuer your_issuer.pem
 *            --load-signer your_issuer.pem --outfile ocsp-status.der
 */
#define OCSP_STATUS_FILE "ocsp-status.der"

SecureSocketServer::SecureSocketServer(uint32_t port, OnNewClientCallback onNewClientCallback) : m_port(port), m_fdSocket(-1), fCallback(std::move(onNewClientCallback))
{

    int ret = gnutls_global_init();
    if (ret < 0)
    {
        std::string msg("Error initializing gnutls " + std::to_string(ret));
        std::cout << msg << std::endl;
        throw std::logic_error(msg);
    }



    gnutls_certificate_allocate_credentials(&x509_cred);

    gnutls_certificate_set_x509_trust_file(x509_cred, CAFILE, GNUTLS_X509_FMT_PEM);

    gnutls_certificate_set_x509_crl_file(x509_cred, CRLFILE,
            GNUTLS_X509_FMT_PEM);

    /* The following code sets the certificate key pair as well as, 
     * an OCSP response which corresponds to it. It is possible
     * to set multiple key-pairs and multiple OCSP status responses
     * (the latter since 3.5.6). See the manual pages of the individual
     * functions for more information.
     */
    gnutls_certificate_set_x509_key_file(x509_cred, CERTFILE,
            KEYFILE,
            GNUTLS_X509_FMT_PEM);

    gnutls_certificate_set_ocsp_status_request_file(x509_cred, OCSP_STATUS_FILE, 0);

    gnutls_priority_init(&priority_cache, NULL, NULL);

    gnutls_certificate_set_known_dh_params(x509_cred, GNUTLS_SEC_PARAM_MEDIUM);

    int fdSck = 0;

    struct sockaddr_in servAddr
    {
    };
    fdSck = socket(AF_INET, SOCK_STREAM, 0);


    servAddr.sin_family = AF_INET;
    servAddr.sin_addr.s_addr = htonl(INADDR_ANY); //Importantísimo usar la familia  de funciones hton (hardware to network)
    servAddr.sin_port = htons(m_port);


    int status = bind(fdSck, reinterpret_cast<struct sockaddr*> (&servAddr), sizeof (servAddr));
    if (0 != status)
    {

        std::string msg("Something went wrong in bind " + std::to_string(status));
        std::cout << msg << std::endl;
        throw std::logic_error(msg);
        return;
    }
    m_fdSocket = fdSck;
}

int SecureSocketServer::serverListen()
{
    int32_t status = listen(m_fdSocket, 10);
    if (0 != status)
    {
        std::cout << "Something went wrong in listen" << std::endl;
    }

    gnutls_init(&session, GNUTLS_SERVER);
    gnutls_priority_set(session, priority_cache);
    gnutls_credentials_set(session, GNUTLS_CRD_CERTIFICATE, x509_cred);

    /* We don't request any certificate from the client.
     * If we did we would need to verify it. One way of
     * doing that is shown in the "Verifying a certificate"
     * example.
     */
    gnutls_certificate_server_set_request(session,
            GNUTLS_CERT_IGNORE);
    gnutls_handshake_set_timeout(session,
            GNUTLS_DEFAULT_HANDSHAKE_TIMEOUT);

    return status;
}

void SecureSocketServer::disconnect()
{
    close(m_fdSocket);
    gnutls_deinit(session);
    gnutls_certificate_free_credentials(x509_cred);
    gnutls_priority_deinit(priority_cache);
    gnutls_global_deinit();
}

void SecureSocketServer::doAccept()
{
    int32_t fdClient = accept(m_fdSocket, nullptr, nullptr);
    gnutls_transport_set_int(session, fdClient);
    int32_t ret = 0;
    do
    {
        ret = gnutls_handshake(session);
    }
    while (ret < 0 && gnutls_error_is_fatal(ret) == 0);


    if (ret < 0)
    {
        close(fdClient);
        gnutls_deinit(session);
        std::string err(gnutls_strerror(ret));

        err = "*** Handshake has failed " + err;

        std::cout << err << std::endl;
        throw std::logic_error(err);
    }

    SecureSocket s(fdClient,session);
    fCallback(std::move(s));
}

#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <unistd.h>

#include <iostream>
#include "sockets/isocketclient.h"


using namespace CppUtils;


ISocketClient::ISocketClient(std::string ip, uint16_t port):
m_host(std::move(ip)),
m_port(port)
{
}


ISocketClient::ISocketClient(const ISocketClient &other)
{
    m_host = other.m_host;
    m_port = other.m_port;
}
    
ISocketClient& ISocketClient::operator=(const ISocketClient &other)
{
    m_host = other.m_host;
    m_port = other.m_port;
    
    return *this;
}

int32_t ISocketClient::tryConnect()
{
    std::cerr << __PRETTY_FUNCTION__ << std::endl;
    int sockfd = 0;

    struct sockaddr_in servAddr{};
    

    //Puntero a esctructura hostent que nos permitirá
    //resolver un nombre de host a IP
    struct hostent *he;

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        std::cerr << "Error : Could not create socket \n" << std::endl;
        return false;
    }



    servAddr.sin_family = AF_INET;
    servAddr.sin_port = htons(m_port);

    // Debemos resolver el nombre del host a una IP
    he = gethostbyname(m_host.c_str());
    if (he == nullptr)
    {
        std::cerr << "Error gethostbyname()" << std::endl;
        return false;
    }


    servAddr.sin_addr = *(reinterpret_cast<struct in_addr *> (he->h_addr));

    if (connect(sockfd, reinterpret_cast<struct sockaddr *> (&servAddr), sizeof (servAddr)) < 0)
    {
        std::cerr << "Error connecting socket" << std::endl;
        return false;
    }

    return sockfd;
}

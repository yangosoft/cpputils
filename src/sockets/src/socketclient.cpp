

#include <netinet/in.h>
#include <arpa/inet.h>


#include <unistd.h>

#include <sys/types.h>

#include <pthread.h>
#include <cstring>
#include <iostream>


#include <arpa/inet.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>

#include <cstdlib>
#include <unistd.h>
#include <arpa/inet.h>


#include <cerrno>
#include <chrono>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <iostream>
#include <thread>



#include "sockets/socketclient.h"



using namespace CppUtils;

TSocketClient::TSocketClient(const std::string& IP, uint16_t port) :
m_host(IP),
m_port(port)
{
}

bool TSocketClient::tryConnect()
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    int sockfd = 0;

    struct sockaddr_in serv_addr
    {
    };

    //Puntero a esctructura hostent que nos permitirá
    //resolver un nombre de host a IP
    struct hostent *he;

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        std::cout << "Error : Could not create socket \n" << std::endl;
        return false;
    }



    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(m_port);

    // Debemos resolver el nombre del host a una IP
    he = gethostbyname(m_host.c_str());
    if (he == nullptr)
    {
        std::cout << "Error gethostbyname()" << std::endl;
        return false;
    }


    serv_addr.sin_addr = *(reinterpret_cast<struct in_addr *> (he->h_addr));

    if (connect(sockfd, reinterpret_cast<struct sockaddr *> (&serv_addr), sizeof (serv_addr)) < 0)
    {
        std::cout << "Error connecting socket" << std::endl;
        return false;
    }

    m_fdSocket = sockfd;
 

    return true;
}

ssize_t TSocketClient::writeData(const char *data, uint32_t size) const
{
    ssize_t n = write(m_fdSocket, data, size);
    return n;
}

ssize_t TSocketClient::readData(char* buffer, ssize_t size) const
{
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

bool TSocketClient::writeData(const std::string& data) const
{
    ssize_t n = writeData(data.c_str(),data.size());
    return (n == data.size());
}

void TSocketClient::disconnect()
{
    close(m_fdSocket);
}


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

SocketClient::SocketClient(std::string ip, uint16_t port) :
ISocket(-1),
m_host(std::move(ip)),
m_port(port) 
{
}

bool SocketClient::tryConnect()
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    int sockfd = 0;

    struct sockaddr_in servAddr{};
    

    //Puntero a esctructura hostent que nos permitirá
    //resolver un nombre de host a IP
    struct hostent *he;

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        std::cout << "Error : Could not create socket \n" << std::endl;
        return false;
    }



    servAddr.sin_family = AF_INET;
    servAddr.sin_port = htons(m_port);

    // Debemos resolver el nombre del host a una IP
    he = gethostbyname(m_host.c_str());
    if (he == nullptr)
    {
        std::cout << "Error gethostbyname()" << std::endl;
        return false;
    }


    servAddr.sin_addr = *(reinterpret_cast<struct in_addr *> (he->h_addr));

    if (connect(sockfd, reinterpret_cast<struct sockaddr *> (&servAddr), sizeof (servAddr)) < 0)
    {
        std::cout << "Error connecting socket" << std::endl;
        return false;
    }

    m_fdSocket = sockfd;
 

    return true;
}


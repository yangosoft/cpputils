
#include <arpa/inet.h>

#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <cerrno>
#include <sys/types.h>
#include <ctime>
#include <pthread.h>
#include <cstring>
#include <iostream>


#include <iostream>

#include "sockets/socketserver.h"



using namespace CppUtils;



SocketServer::SocketServer(uint32_t port, OnNewClientCallback onNewClientCallback): m_port(port), m_fdSocket(-1), fCallback(onNewClientCallback)
{
    int fdSck 	 	= 0;
    struct sockaddr_in serv_addr{};

    

    fdSck = socket(AF_INET, SOCK_STREAM, 0);
    
//        fd_sck = socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK , 0);

    serv_addr.sin_family 	= AF_INET;
    serv_addr.sin_addr.s_addr 	= htonl(INADDR_ANY); //Importantísimo usar la familia  de funciones hton (hardware to network)
    serv_addr.sin_port 		= htons( m_port );

   
    int status = bind(fdSck, reinterpret_cast<struct sockaddr*>(&serv_addr), sizeof(serv_addr));
    if ( 0 != status )
    {
        std::cout << "Something went wrong in bind" << std::endl;
       
        return;
    }
    m_fdSocket = fdSck;
}

int SocketServer::serverListen()
{
    int32_t status = listen(m_fdSocket, 10);
    if ( 0 != status )
    {
        std::cout << "Something went wrong in listen" << std::endl;  
    }
    
    return status;
}


void SocketServer::disconnect()
{
    close(m_fdSocket);
}

void SocketServer::doAccept()
{
    int32_t fdClient = accept(m_fdSocket, nullptr, nullptr);
    fCallback(fdClient);
}
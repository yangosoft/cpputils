
#include <arpa/inet.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <netinet/in.h>
#include <sys/types.h>
#include <unistd.h>

#include <iostream>

#include "sockets/socketserver.h"



using namespace CppUtils;



SocketServer::SocketServer(uint32_t port, OnNewClientCallback onNewClientCallback): m_port(port), m_fdSocket(-1), fCallback(std::move(onNewClientCallback))
{
    int fdSck 	 	= 0;
    struct sockaddr_in servAddr{};

    

    fdSck = socket(AF_INET, SOCK_STREAM, 0);
    
//        fd_sck = socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK , 0);

    servAddr.sin_family 	= AF_INET;
    servAddr.sin_addr.s_addr 	= htonl(INADDR_ANY); //Importantísimo usar la familia  de funciones hton (hardware to network)
    servAddr.sin_port 		= htons( m_port );

   
    int status = bind(fdSck, reinterpret_cast<struct sockaddr*>(&servAddr), sizeof(servAddr));
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
    ISocket s(fdClient);
    fCallback(s);
}

int SocketServer::getFdSocket() const
{
    return m_fdSocket;
}
        

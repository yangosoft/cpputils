

#include <arpa/inet.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <netinet/in.h>
#include <sys/types.h>
#include <unistd.h>

#include <iostream>

#include "sockets/socket.h"
#include "sockets/socketserver.h"



using namespace CppUtils;



SocketServer::SocketServer(uint32_t port, OnNewClientCallback onNewClientCallback): 
ISocketServer(port, onNewClientCallback)
{
    int fdSck 	 	= 0;
    struct sockaddr_in servAddr{};

    

    fdSck = socket(AF_INET, SOCK_STREAM, 0);
    
    servAddr.sin_family 	= AF_INET;
    servAddr.sin_addr.s_addr 	= htonl(INADDR_ANY); //Importantísimo usar la familia  de funciones hton (hardware to network)
    servAddr.sin_port 		= htons( m_port );

   
    int status = bind(fdSck, reinterpret_cast<struct sockaddr*>(&servAddr), sizeof(servAddr));
    if ( 0 != status )
    {
        std::cerr << "Something went wrong in bind" << std::endl;
       
        return;
    }
    m_fdSocket = fdSck;
}       

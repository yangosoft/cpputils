
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


SocketServer::SocketServer(uint32_t port): m_port(port), fdSocket(-1)
{
    int fd_sck 	 	= 0;


    //Estructura sockaddr_in
    //contiene el tipo de socket que queremos abrir SOCK_STREAM (TCP)
    //el puerto
    //la IP (INADDR_ANY) escuchamos en cualquier interfaz de red
    struct sockaddr_in serv_addr{};

    

        fd_sck = socket(AF_INET, SOCK_STREAM, 0);
    
//        fd_sck = socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK , 0);

       
    serv_addr.sin_family 	= AF_INET;
    serv_addr.sin_addr.s_addr 	= htonl(INADDR_ANY); //Importantísimo usar la familia  de funciones hton (hardware to network)
    serv_addr.sin_port 		= htons( m_port );

   
    int status = bind(fd_sck, reinterpret_cast<struct sockaddr*>(&serv_addr), sizeof(serv_addr));
    if ( 0 != status )
    {
        std::cout << "Something went wrong in bind" << std::endl;
       
        return;
    }
    fdSocket = fd_sck;
}

void SocketServer::serverListen()
{
    int32_t status = listen(fdSocket, 10);
    if ( 0 != status )
    {
        std::cout << "Something went wrong in listen" << std::endl;
        return;
    }
}


//To an interface
void SocketServer::onNewClient(int32_t fdClient)
{
    
}

void SocketServer::disconnect()
{
    close(fdSocket);
}

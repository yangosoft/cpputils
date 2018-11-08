#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <unistd.h>

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
ISocketClient(ip,port),
Socket(-1)
{
}

int32_t SocketClient::tryConnect()
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    m_fdSocket = ISocketClient::tryConnect();
    return m_fdSocket;
}

#ifndef SOCKETSERVER_H
#define	SOCKETSERVER_H

#include <cstdint>
#include <functional>



namespace CppUtils
{

using OnNewClientCallback =  std::function< void(int32_t fdClient) >;


class SocketServer  {
  
public:
    SocketServer(uint32_t port, OnNewClientCallback onNewClientCallback);
    
    int serverListen();
    void doAccept();
    
    
    virtual void disconnect();
    
    virtual ~SocketServer() = default;
    
    
private:
    uint32_t m_port;
    uint32_t m_fdSocket;
    OnNewClientCallback fCallback;
    
};
}

#endif

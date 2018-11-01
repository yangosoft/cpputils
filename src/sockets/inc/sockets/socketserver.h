#ifndef SOCKETSERVER_H
#define	SOCKETSERVER_H

#include <cstdint>




namespace CppUtils
{


class SocketServer  {
  
public:
    SocketServer(uint32_t port);
    void serverListen();
    
    
    //To an interface
    virtual void onNewClient(int32_t fdClient);
    virtual void disconnect();
    
    virtual ~SocketServer() = default;
    
    
private:
    uint32_t m_port;
    uint32_t fdSocket;
    
};
}

#endif

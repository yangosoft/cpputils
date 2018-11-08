#ifndef ISOCKETSERVER_H
#define ISOCKETSERVER_H



#include <cstdint>
#include <functional>

#include "isocket.h"

namespace CppUtils
{
    
    
class ISocketServer
{
  
  public:
    using OnNewClientCallback =  std::function< void(ISocket& fdClient) >;
    ISocketServer(uint32_t port, OnNewClientCallback onNewClientCallback);
    
    virtual int serverListen();
    virtual void doAccept();
    
    
    virtual int getFdSocket() const;
    
    virtual void disconnect();
    
    virtual ~ISocketServer() = default;
    
    
protected:
    uint32_t m_port;
    uint32_t m_fdSocket;
    OnNewClientCallback fCallback;  
};
};

#endif /* ISOCKETSERVER_H */


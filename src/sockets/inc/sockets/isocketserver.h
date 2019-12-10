#ifndef __CPPUTILS_ISOCKETSERVER_H
#define __CPPUTILS_ISOCKETSERVER_H



#include <cstdint>
#include <functional>
#include <memory>

#include "isocket.h"

namespace CppUtils
{
    
    
class ISocketServer
{
  
  public:
    using OnNewClientCallback =  std::function< void(std::unique_ptr<ISocket> fdClient) >;
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

#endif /* __CPPUTILS_ISOCKETSERVER_H */


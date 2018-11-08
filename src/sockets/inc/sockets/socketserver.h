#ifndef SOCKETSERVER_H
#define	SOCKETSERVER_H



#include "isocket.h"
#include "isocketserver.h"


namespace CppUtils
{

class SocketServer : public ISocketServer  {
  
public:
    SocketServer(uint32_t port, OnNewClientCallback onNewClientCallback);
    
      
};
}

#endif

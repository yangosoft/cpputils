#ifndef __CPPUTILS_SOCKETSERVER_H
#define	__CPPUTILS_SOCKETSERVER_H



#include "isocket.h"
#include "isocketserver.h"


namespace CppUtils
{

class SocketServer : public ISocketServer  {
  
public:
    SocketServer(uint32_t port, OnNewClientCallback onNewClientCallback);
    
      
};
}

#endif //__CPPUTILS_

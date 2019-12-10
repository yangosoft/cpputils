#ifndef __CPPUTILS_SOCKET_H
#define __CPPUTILS_SOCKET_H

#include "isocket.h"

namespace CppUtils
{


class Socket : public ISocket {
public:
    Socket(int32_t fdSocket);
    
    
private:

};
};
#endif /* __CPPUTILS_SOCKET_H */


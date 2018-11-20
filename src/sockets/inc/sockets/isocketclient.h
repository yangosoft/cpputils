#ifndef __CPPUTILS_ISOCKETCLIENT_H
#define __CPPUTILS_ISOCKETCLIENT_H


#include <cstdint>
#include <string>

namespace CppUtils
{

class ISocketClient {
public:
    
    ISocketClient(std::string ip, uint16_t port);
    virtual int32_t tryConnect();
    virtual ~ISocketClient() = default;

protected:

    std::string m_host;
    uint16_t m_port;
    
};
};

#endif /* __CPPUTILS_ISOCKETCLIENT_H */


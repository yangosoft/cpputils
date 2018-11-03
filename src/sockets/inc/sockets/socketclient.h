
#ifndef SOCKETCLIENT_H
#define	SOCKETCLIENT_H

#include <cstdint>
#include <list>
#include <mutex>
#include <string>
#include <thread>

#include "isocket.h"


namespace CppUtils
{


class SocketClient : public ISocket  {
public:
    SocketClient(std::string ip, uint16_t port);
    virtual bool tryConnect();
    virtual ~SocketClient() = default;

protected:

    std::string m_host;
    uint16_t m_port;
        
};
};
#endif	/* TSOCKETCLIENT_H */



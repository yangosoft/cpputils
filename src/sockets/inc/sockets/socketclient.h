#ifndef SOCKETCLIENT_H
#define	SOCKETCLIENT_H

#include <cstdint>
#include <list>
#include <mutex>
#include <string>
#include <thread>

#include "socket.h"
#include "isocketclient.h"


namespace CppUtils
{


class SocketClient : public ISocketClient, public Socket  {
public:
    SocketClient(std::string ip, uint16_t port);
    int32_t tryConnect() override;
    virtual ~SocketClient() = default;


        
};
};
#endif	/* TSOCKETCLIENT_H */



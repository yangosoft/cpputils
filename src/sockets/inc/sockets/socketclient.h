
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
    bool tryConnect();
    void disconnect();
    ssize_t writeData(const char *data, uint32_t size) const override;    
    bool writeData(const std::string &data) const override ;    
    ssize_t readData(char *buffer, ssize_t size) const override;
    virtual ~SocketClient() = default;

private:

    std::string m_host;
    uint16_t m_port;
    
    
//    void *run( );
//    static void *run_helper(void *context)
//    {
//        TSocketClient *n = static_cast<TSocketClient *>(context);
//        return n->run();
//    }

};
};
#endif	/* TSOCKETCLIENT_H */



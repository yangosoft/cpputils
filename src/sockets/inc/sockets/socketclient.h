
#ifndef SOCKETCLIENT_H
#define	SOCKETCLIENT_H

#include <cstdint>
#include <list>
#include <mutex>
#include <string>
#include <thread>


namespace CppUtils
{


class TSocketClient  {
public:
    TSocketClient(const std::string& IP, uint16_t port);
    bool tryConnect();
    void disconnect();
    ssize_t writeData(const char *data, uint32_t size) const;    
    bool writeData(const std::string &data) const ;    
    ssize_t readData(char *buffer, ssize_t size) const;
    virtual ~TSocketClient() = default;

private:

    std::string m_host;
    uint16_t m_port;
    int32_t m_fdSocket;
    
//    void *run( );
//    static void *run_helper(void *context)
//    {
//        TSocketClient *n = static_cast<TSocketClient *>(context);
//        return n->run();
//    }

};
};
#endif	/* TSOCKETCLIENT_H */



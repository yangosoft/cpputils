#include <limits.h>

#include <cpputils/sockets/isocket.h>
#include <cpputils/sockets/socketclient.h>
#include <cpputils/sockets/socketserver.h>
#include <gtest/gtest.h>
namespace
{

std::string strSent("Hello world!");
TEST(SocketTests, TestAsync)
{
    
    
    
    CppUtils::SocketClient s("localhost",11010);
    
    bool connected = s.tryConnect();
    
    CppUtils::SocketServer server(11010, []( CppUtils::ISocket& client ){ 
        char buffer[128];
        auto n = client.readData(buffer,sizeof(buffer));
        EXPECT_GT(n,0);
        if(n > 0)
        {
            buffer[n] = '\0';
        }
        EXPECT_EQ(strSent,std::string(buffer));
    });
    
    
    auto fd = server.serverListen();
    
    EXPECT_NE(fd,-1);
    
    if( false == connected)
    {
        connected = s.tryConnect();
        EXPECT_TRUE(connected);
        if( false == connected)
        {
            server.disconnect();
            s.disconnect();
            return;
        }
    }
    server.doAccept();
    bool ok = s.writeString(strSent);
    
    server.disconnect();
    s.disconnect();
    
    EXPECT_TRUE(ok);
}

};

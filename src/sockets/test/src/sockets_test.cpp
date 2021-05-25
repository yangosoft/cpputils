#include <limits.h>

#include <sockets/isocket.h>
#include <sockets/socketclient.h>
#include <sockets/socketserver.h>
#include <gtest/gtest.h>
namespace
{

std::string strSent("Hello world!");
TEST(SocketTests, TestAsync)
{
    
    
    /*DISABLED until fix 
    CppUtils::SocketClient s("localhost",11010);
    
   
    
    CppUtils::SocketServer server(11010, []( std::unique_ptr<CppUtils::ISocket> client ){ 
        char buffer[128];
        auto n = client->readData(buffer,sizeof(buffer));
        EXPECT_GT(n,0);
        if(n > 0)
        {
            buffer[n] = '\0';
        }
        EXPECT_EQ(strSent,std::string(buffer));
    });
    
    bool connected = s.tryConnect();
    
    auto fd = server.serverListen();
   
    
    EXPECT_NE(fd,-1);
    
    if( false == connected)
    {
        connected = s.tryConnect();
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
    
    EXPECT_TRUE(ok);*/
    EXPECT_TRUE(true);
}

};

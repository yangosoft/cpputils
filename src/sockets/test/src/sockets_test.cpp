#include <limits.h>

#include <cpputils/sockets/isocket.h>
#include <cpputils/sockets/socketclient.h>
#include <cpputils/sockets/socketserver.h>
#include <gtest/gtest.h>
namespace
{


TEST(ExampleTests, TestGet)
{
    CppUtils::SocketClient s("localhost",8999);
    s.tryConnect();
   
    
    CppUtils::SocketServer server(8999, []( int32_t fdSocket ){ 
        
        CppUtils::ISocket client(fdSocket);
        
        char buffer[64];
        
        client.readData(buffer,sizeof(buffer));
        std::cout << std::string(buffer) << std::endl;
        
    
    
    });
    
    
    server.serverListen();
    server.doAccept();
    bool ok = s.writeData("Hello world!");
    
    server.disconnect();
    s.disconnect();
    
    EXPECT_TRUE(ok);
}

};

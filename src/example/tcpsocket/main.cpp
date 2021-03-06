

#include <iostream>
#include <string>
#include <thread>

#include <cpputils/sockets/isocket.h>
#include <cpputils/sockets/socketclient.h>
#include <cpputils/sockets/socketserver.h>




void runServer()
{
    CppUtils::SocketServer server(8999, []( CppUtils::ISocket& client ){ 
        
        std::cout << "* New client: " << client.getFdSocket() << std::endl;
        
        std::string data;
        int n = client.readString(data);
        
        std::cout << "* Readed " << n << " bytes: '" << data << "'" << std::endl;
    });
    
    
    if(0 != server.serverListen())
    {
        std::cout << "Cannot listen" << std::endl;
        return ;
    }
    
    server.doAccept();
}

int main(int /*argc*/, char** /*argv*/)
{
    std::thread t(&runServer);

    CppUtils::SocketClient s("localhost",8999);
    if ( -1 == s.tryConnect())
    {
        std::cout << "Error connecting!" << std::endl;
        return -1;
    }
   
    std::string hello("Hello World!");
    std::cout << "Sending '" << hello << "'" << std::endl;
    
    bool ok = s.writeString(hello);
    if(false == ok)
    {
        std::cout << "Cannot send all the data" << std::endl;
    }
    
    s.disconnect(); 
    t.join();

  return 0;
}



#include <iostream>
#include <string>
#include <thread>

#include <cpputils/sockets/isocket.h>
#include <cpputils/sockets/socketclient.h>
#include <cpputils/sockets/socketserver.h>




void runServer()
{
    CppUtils::SocketServer server(8999, []( int32_t fdSocket ){ 
        
        std::cout << "* New client: " << fdSocket << std::endl;
        CppUtils::ISocket client(fdSocket);
        std::string data;
        int n = client.readData(data);
        
        std::cout << "* Readed " << n << " bytes: '" << std::string(data) << "'" << std::endl;
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
    s.tryConnect();
   
    std::string hello("Hello World!");
    std::cout << "Sending '" << hello << "'" << std::endl;
    
    bool ok = s.writeData(hello);
    if(false == ok)
    {
        std::cout << "Cannot send all the data" << std::endl;
    }
    
    s.disconnect(); 
    t.join();

  return 0;
}

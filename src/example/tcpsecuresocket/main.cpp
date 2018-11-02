

#include <iostream>
#include <string>
#include <thread>


#include <cpputils/sockets/securesocket.h>
#include <cpputils/sockets/socketclient.h>
#include <cpputils/sockets/securesocketserver.h>




void runServer()
{
    CppUtils::SecureSocketServer server(8999, []( CppUtils::ISocket client ){ 
        
        std::cout << "* New client: " << client.getFdSocket() << std::endl;
        
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

    t.join();

  return 0;
}



#include <iostream>
#include <string>
#include <thread>


#include <cpputils/sockets/securesocket.h>
#include <cpputils/sockets/socketclient.h>
#include <cpputils/sockets/securesocketserver.h>



bool run = true;

void runServer(CppUtils::SecureSocketServer& server)
{
   
    while(run)
    {
        server.doAccept();
    }
}

int main(int /*argc*/, char** /*argv*/)
{
    
    CppUtils::SecureSocketServer server(8999, []( CppUtils::ISocket& client ){ 
        
        std::cout << "* New client: " << client.getFdSocket() << std::endl;
        
        std::string data;
        while(run){
        int n = client.readData(data);
        if (n < 0)
        {
            break;
        }
        std::cout << "* Readed " << n << " bytes: '" << std::string(data) << "'" << std::endl;
        
        }
    });
    
    
    if(0 != server.serverListen())
    {
        std::cout << "Cannot listen" << std::endl;
        return -1;
    }
    
    
    std::thread t(&runServer,std::ref(server));

    t.join();

  return 0;
}

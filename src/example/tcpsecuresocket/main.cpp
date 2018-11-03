

#include <iostream>
#include <string>
#include <thread>


#include <cpputils/sockets/securesocket.h>
#include <cpputils/sockets/socketclient.h>
#include <cpputils/sockets/securesocketclient.h>
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
        std::cout << "* Readed " << n << " bytes: '" << std::string(data) << "'" << std::endl;
        if (n < 0)
        {
            break;
        }
        
        
        }
    });
    
    
    if(0 != server.serverListen())
    {
        std::cout << "Cannot listen" << std::endl;
        return -1;
    }
    
    
    std::thread t(&runServer,std::ref(server));

    CppUtils::SecureSocketClient client{"localhost",8999,"cert.pem","key.pem"};
    client.tryConnect();
    client.writeData("HELLO from CLIENT");
    client.disconnect();
    
    
    
    
    t.join();

  return 0;
}

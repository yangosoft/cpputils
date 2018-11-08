
#include <chrono>
#include <iostream>
#include <string>
#include <thread>


#include <cpputils/sockets/securesocket.h>
#include <cpputils/sockets/socketclient.h>
#include <cpputils/sockets/securesocketclient.h>
#include <cpputils/sockets/securesocketserver.h>

using namespace std::chrono_literals;

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
    
    CppUtils::SecureSocketServer server(8999, "../cert/cert.pem", "../cert/key.pem", []( CppUtils::ISocket& client )
    { 
        
        std::cout << "[Server] New client: " << client.getFdSocket() << std::endl;
        
        std::string data{};
        while(run){
            int n = client.readData(data);
            std::cout << "[Server] Readed " << n << " bytes: '" << std::string(data) << "'" << std::endl;
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

    CppUtils::SecureSocketClient client{"localhost",8999,"../cert/clientcert.pem","../cert/clientkey.pem","cpputils" };
    client.tryConnect();
    while(run)
    {
        client.writeData("HELLO from CLIENT");
        std::this_thread::sleep_for(1s);
    }
    client.disconnect();
    
    
    
    
    t.join();

  return 0;
}

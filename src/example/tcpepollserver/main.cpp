

#include <iostream>
#include <string>
#include <thread>


#include <fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <wait.h>
#include <signal.h>
#include <errno.h>
#include <sys/select.h>
#include <sys/time.h>
#include <unistd.h>
#include <poll.h>
#include <sys/epoll.h>


#include <cpputils/sockets/isocket.h>
#include <cpputils/sockets/socketclient.h>
#include <cpputils/sockets/socketserver.h>




static constexpr int MAX_EVENTS = 256;
int epollfd;

struct epoll_event ev, events[MAX_EVENTS];

void addFdToEpoll(CppUtils::ISocket& client)
{

    if (fcntl(client.getFdSocket(), F_SETFL, fcntl(client.getFdSocket(), F_GETFL, 0) | O_NONBLOCK) == -1)
    {
        std::cout << "Error setting non block" << std::endl;
    }

    ev.events = EPOLLIN | EPOLLET;
    ev.data.fd = client.getFdSocket();

    if (epoll_ctl(epollfd, EPOLL_CTL_ADD, ev.data.fd, &ev) == -1)
    {
        std::cout << "Error adding fd to epoll" << std::endl;
    }

}

void runServer()
{

    CppUtils::SocketServer server(8999, addFdToEpoll);


    if (0 != server.serverListen())
    {
        std::cout << "Cannot listen" << std::endl;
        return;
    }

    //We are adding the listening socket to epoll
    auto listeningSocket = CppUtils::Socket{server.getFdSocket()};
    addFdToEpoll(listeningSocket);


    while(true)
    {
        int nfds = epoll_wait(epollfd, events, MAX_EVENTS, -1);
        if (nfds == -1)
        {
            std::cout << "epoll_wait error " << nfds << std::endl;
            exit(EXIT_FAILURE);
        }

        for (auto n = 0; n < nfds; ++n)
        {
            if (events[n].data.fd == listeningSocket.getFdSocket())
            {
                //Here we accept the socket and callback addFdToEpoll will be called
                server.doAccept();
            }
            else
            {
                auto c = CppUtils::Socket{ events[n].data.fd };
                std::string data;
                c.readString(data);
                std::cout << "Client " << c.getFdSocket() << " readed " << data << std::endl;
                c.writeString(data);
            }
        }
    }

}

int main(int /*argc*/, char** /*argv*/)
{
    epollfd = epoll_create1(0);
    if (epollfd == -1)
    {
        std::cout << "epoll_create1" << std::endl;
        exit(EXIT_FAILURE);
    }



    std::thread t(&runServer);

    CppUtils::SocketClient s("localhost", 8999);
    s.tryConnect();

    std::string hello("Hello World!");
    std::cout << "Sending '" << hello << "'" << std::endl;

    bool ok = s.writeString(hello);
    if (false == ok)
    {
        std::cout << "Cannot send all the data" << std::endl;
    }

    s.disconnect();
    t.join();

    return 0;
}

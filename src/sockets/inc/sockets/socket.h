#ifndef SOCKET_H
#define SOCKET_H

#include "isocket.h"

namespace CppUtils
{


class Socket : public ISocket {
public:
    Socket(int32_t fdSocket);
    ssize_t writeData(const char *data, size_t size) const override;
    ssize_t readData(char *buffer, ssize_t size) const override;
    
private:

};
};
#endif /* SOCKET_H */


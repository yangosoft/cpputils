
#ifndef ISOCKET_H
#define	ISOCKET_H

#include <sys/types.h>
#include <unistd.h>

#include <cstdint>
#include <string>



namespace CppUtils
{


class ISocket  {
public:
    ISocket(int32_t fdSocket);
    virtual void disconnect();
    virtual ssize_t writeData(const char *data, size_t size) const = 0;    
    virtual bool writeString(const std::string &data) const;    
    virtual ssize_t readData(char *buffer, ssize_t size) const = 0;
    virtual bool readString(std::string &data) const;
    
    
    int32_t getFdSocket() const;
    
    virtual ~ISocket() = default;

protected:
    int32_t m_fdSocket;
   

};
};
#endif	/* ISOCKET_H */

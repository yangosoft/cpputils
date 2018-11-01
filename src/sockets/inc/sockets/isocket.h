
#ifndef ISOCKET_H
#define	ISOCKET_H

#include <cstdint>
#include <string>



namespace CppUtils
{


class ISocket  {
public:
    ISocket(int32_t fdSocket);
    virtual void disconnect();
    virtual ssize_t writeData(const char *data, uint32_t size) const;    
    virtual bool writeData(const std::string &data) const;    
    virtual ssize_t readData(char *buffer, ssize_t size) const;
    virtual ~ISocket() = default;

protected:
    int32_t m_fdSocket;
   

};
};
#endif	/* ISOCKET_H */

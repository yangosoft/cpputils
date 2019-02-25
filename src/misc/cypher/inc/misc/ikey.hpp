#ifndef __CCPUTILS_IKEY_h__
#define __CCPUTILS_IKEY_h__


#include <openssl/rsa.h>
#include <string>

namespace CppUtils
{
    namespace Misc
    {
        
        class IKey
        {
        public:
            //IKey(const std::string& path) = 0;
            
            virtual bool load(const std::string &password)  = 0;
            virtual RSA* getAsRSA() = 0;
            virtual ~IKey() = default;
        };
    }
}


#endif
#ifndef __CCPUTILS_CIPHER2_h__
#define __CCPUTILS_CIPHER2_h__

#include <openssl/pem.h>
#include <openssl/rsa.h>
#include <openssl/conf.h>

#include <string>

namespace CppUtils
{
    namespace Misc
    {
        
        class Cipher2
        {
        public:
            RSA* loadPUBLICKeyFromString( const char* publicKeyStr );
            bool encryptFile(const std::string& pemCertificatePath);
            bool decryptFile(const std::string& pemCertificatePath, unsigned char* msg);
        };

    }
}

#endif //__CCPUTILS_CIPHER2_h__

#ifndef __CCPUTILS_ISYMMETRICCIPHER_h__
#define __CCPUTILS_ISYMMETRICCIPHER_h__


#include <misc/icipher.hpp>
#include <misc/ikey.hpp>

#include <openssl/evp.h>
#include <openssl/engine.h>

#include <cstdlib>



namespace CppUtils
{
    namespace Misc
    {
        
        class SymmetricalCipher: public ICipher
        {
        public:
            SymmetricalCipher();               
            std::size_t encrypt(const char *inputBuffer, std::size_t inputLength, char *outputBuffer , std::size_t &outLength  , IKey& key)  override;
            std::size_t decrypt(const char *inputBuffer, std::size_t inputLength, char *outputBuffer , std::size_t &outLength  , IKey& key)  override;
            
            ~SymmetricalCipher() = default;
        };
    }
}


#endif
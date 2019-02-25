#ifndef __CCPUTILS_ASYMMETRICALCIPHER_h__
#define __CCPUTILS_ASYMMETRICALCIPHER_h__


#include <misc/icipher.hpp>
#include <misc/ikey.hpp>

#include <openssl/evp.h>
#include <openssl/engine.h>

#include <cstdlib>



namespace CppUtils
{
    namespace Misc
    {
        
        class AsymmetricalCipher: public ICipher
        {
        public:
            AsymmetricalCipher();               
            std::size_t encrypt(const char *inputBuffer, std::size_t inputLength, char *outputBuffer , std::size_t &outLength  , IKey& key)  override;
            std::size_t decrypt(const char *inputBuffer, std::size_t inputLength, char *outputBuffer , std::size_t &outLength  , IKey& key)  override;
            
            ~AsymmetricalCipher() = default;
        };
    }
}


#endif
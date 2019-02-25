#ifndef __CCPUTILS_ICIPHER_h__
#define __CCPUTILS_ICIPHER_h__


#include <misc/ikey.hpp>

#include <string>

#include <cstdlib>

namespace CppUtils
{
    namespace Misc
    {
        
        class ICipher
        {
        public:
            
            virtual std::size_t encrypt(const char *inputBuffer, std::size_t inputLength, char *outputBuffer , std::size_t &outLength  , IKey& key)  = 0;
            virtual std::size_t decrypt(const char *inputBuffer, std::size_t inputLength, char *outputBuffer , std::size_t &outLength  , IKey& key)  = 0;
            
            virtual ~ICipher() = default;
        };
    }
}


#endif
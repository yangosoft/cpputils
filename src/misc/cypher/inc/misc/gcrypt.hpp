#ifndef __CCPUTILS_GCRYPT_h__
#define __CCPUTILS_GCRYPT_h__

#include <gcrypt.h>

namespace CppUtils
{
    namespace Misc
    {
        
        class Gcrypt
        {
        public:
            bool init();
        };

    }
}

#endif //__CCPUTILS_GCRYPT_h__

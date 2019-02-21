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
            
            bool createKeys(const std::string& filename);
            
            /* Estimate the size of the encrypted key pair. */
            size_t get_keypair_size(int nbits) const ;

            /* Create an AES context out of a user's password. */
            void get_aes_ctx(gcry_cipher_hd_t* aes_hd) const;
        };

    }
}

#endif //__CCPUTILS_GCRYPT_h__

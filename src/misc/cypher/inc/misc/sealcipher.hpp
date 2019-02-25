#ifndef __CCPUTILS_SEALCIPHER_h__
#define __CCPUTILS_SEALCIPHER_h__


#include <misc/icipher.hpp>
#include <misc/ikey.hpp>

#include <openssl/evp.h>
#include <openssl/engine.h>

#include <cstdlib>



namespace CppUtils
{
    namespace Misc
    {
        
        class SealCipher: public ICipher
        {
        public:
            SealCipher();               
            std::size_t encrypt(const char *inputBuffer, std::size_t inputLength, char *outputBuffer , std::size_t &outLength  , IKey& key)  override;
            std::size_t decrypt(const char *inputBuffer, std::size_t inputLength, char *outputBuffer , std::size_t &outLength  , IKey& key)  override;
            ~SealCipher() = default;
        private:
            int envelope_seal(EVP_PKEY **pub_key, unsigned char *plaintext, int plaintext_len, unsigned char **encrypted_key, int *encrypted_key_len, unsigned char *iv, 	unsigned char *ciphertext);
            
            int envelope_open(EVP_PKEY *priv_key, unsigned char *ciphertext, int ciphertext_len, unsigned char *encrypted_key, int encrypted_key_len, unsigned char *iv, unsigned char *plaintext);
            
            int EVP_SealInit(EVP_CIPHER_CTX *ctx, const EVP_CIPHER *type, unsigned char **ek, int *ekl, unsigned char *iv, EVP_PKEY **pubk, int npubk);
        };
    }
}


#endif
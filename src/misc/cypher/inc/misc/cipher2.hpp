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
            Cipher2();
            
            RSA* getPublicKey(const std::string& pemCertificatePath);
            RSA* getPrivateKey(const std::string& pemCertificatePath);
            
            RSA* loadPUBLICKeyFromString( const char* publicKeyStr );
            bool encryptFile(const std::string& pemCertificatePath);
            bool decryptFile(const std::string& pemCertificatePath, unsigned char* msg);
            void seal();
            
            int envelope_seal(EVP_PKEY **pub_key, unsigned char *plaintext, int plaintext_len,
	unsigned char **encrypted_key, int *encrypted_key_len, unsigned char *iv,
	unsigned char *ciphertext);
            int envelope_open(EVP_PKEY *priv_key, unsigned char *ciphertext, int ciphertext_len,
	unsigned char *encrypted_key, int encrypted_key_len, unsigned char *iv,
	unsigned char *plaintext);
            
            int EVP_SealInit(EVP_CIPHER_CTX *ctx, const EVP_CIPHER *type,
                 unsigned char **ek, int *ekl, unsigned char *iv,
                 EVP_PKEY **pubk, int npubk);
        };

    }
}

#endif //__CCPUTILS_CIPHER2_h__

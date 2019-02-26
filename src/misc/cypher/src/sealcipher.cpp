
#include <misc/sealcipher.hpp>

#include <iostream>

using namespace CppUtils::Misc;


SealCipher::SealCipher()
{
    OpenSSL_add_all_algorithms();
    OpenSSL_add_all_ciphers();
}


std::size_t SealCipher::encrypt(const char *inputBuffer, std::size_t inputLength, char *outputBuffer , std::size_t &outLength  , IKey& key)
{
    std::cout << __FUNCTION__ << std::endl;
    RSA *rsa_pubkey= key.getAsRSA(); 
    EVP_PKEY *evp_pubkey = EVP_PKEY_new();
    EVP_PKEY_assign_RSA(evp_pubkey,rsa_pubkey);

    if(outLength < 256)
    {
        //TODO throw
        return 0;
    }
    if(inputLength > 256)
    {
        //TODO throw
        return 0;
    }
    
    if(m_iv.empty())
    {
        //TODO throw
        return 0;
    }
    
    if(m_cipherKey.empty())
    {
        //TODO throw
        return 0;
    }
    
    
    
        
        EVP_CIPHER_CTX *ctx;

	int ciphertext_len;

	int len;
        {

	/* Create and initialise the context */
	if(!(ctx = EVP_CIPHER_CTX_new())) 
        {
            std::cout << "error " << __LINE__ << std::endl;
        }

        
        int ret1 = EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, &m_cipherKey[0], &m_iv[0]);
	
	if(1 != ret1)
        {
            std::cout << "error " << __LINE__ << std::endl;
        }

	/* Provide the message to be encrypted, and obtain the encrypted output.
	 * EVP_SealUpdate can be called multiple times if necessary
	 */
	if(1 != EVP_SealUpdate(ctx, reinterpret_cast<unsigned char *>(outputBuffer), &len, reinterpret_cast<const unsigned char *>(inputBuffer), inputLength))
        {
            std::cout << "error " << __LINE__ << std::endl;
        }
	ciphertext_len = len;

	/* Finalise the encryption. Further ciphertext bytes may be written at
	 * this stage.
	 */
	if(1 != EVP_SealFinal(ctx, reinterpret_cast<unsigned char *>(outputBuffer) + len, &len)) 
        {
            std::cout << "error " << __LINE__ << std::endl;
        }
	ciphertext_len += len;

	/* Clean up */
	EVP_CIPHER_CTX_free(ctx);
        
    }
    
    
    
    
    
    /*int ciphertextlength;
    unsigned char *encKey  =  &m_cipherKey[0]; // new std::uint8_t[ RSA_size(rsa_pubkey) ];
    std::uint8_t *iv = &m_iv[0];

    
    auto ret = envelope_seal(&evp_pubkey,reinterpret_cast<const unsigned char *>(inputBuffer),inputLength,&encKey, &ciphertextlength,iv,reinterpret_cast<unsigned char *>(outputBuffer));
    std::cout << "envelope_seal ret " << ret << std::endl;*/
    
    
    
//     if(ret != 0)
//     {
//         TODO throw
//         return 0;
//     }
    
    
    
    return ciphertext_len;
}

std::size_t SealCipher::decrypt(const char *inputBuffer, std::size_t inputLength, char *outputBuffer , std::size_t &outLength  , IKey& key)
{
    std::cout << __FUNCTION__ << std::endl;
    
    if(m_iv.empty())
    {
        //TODO throw
        return 0;
    }
    
    if(m_cipherKey.empty())
    {
        //TODO throw
        return 0;
    }
    
    RSA *rsa_prikey= key.getAsRSA(); 
   
    EVP_PKEY *evp_prikey = EVP_PKEY_new();



    EVP_PKEY_assign_RSA(evp_prikey,rsa_prikey);
    
    
    EVP_CIPHER_CTX *ctx;

	int len;

	int plaintext_len;
    {
        


	/* Create and initialise the context */
	if(!(ctx = EVP_CIPHER_CTX_new())) 
        {
            std::cout << "error " << __LINE__ << std::endl;
        }

	/* Initialise the decryption operation. The asymmetric private key is
	 * provided and priv_key, whilst the encrypted session key is held in
	 * encrypted_key */
	if(1 != EVP_OpenInit(ctx, EVP_aes_256_cbc(), &m_cipherKey[0], m_cipherKey.size(), &m_iv[0], evp_prikey))
        {
            std::cout << "error " << __LINE__ << std::endl;
        }
		

	/* Provide the message to be decrypted, and obtain the plaintext output.
	 * EVP_OpenUpdate can be called multiple times if necessary
	 */
	if(1 != EVP_OpenUpdate(ctx, reinterpret_cast<unsigned char * >(outputBuffer), &len, reinterpret_cast<const unsigned char * >(inputBuffer), inputLength))
        {
            std::cout << "error " << __LINE__ << std::endl;
        }
            
            
	plaintext_len = len;

	/* Finalise the decryption. Further plaintext bytes may be written at
	 * this stage.
	 */
	if(1 != EVP_OpenFinal(ctx, reinterpret_cast<unsigned char * >(outputBuffer) + len, &len)) 
        {
            std::cout << "error " << __LINE__ << std::endl;
        }
	plaintext_len += len;

	/* Clean up */
	EVP_CIPHER_CTX_free(ctx);
    }
    
    
    
//     std::uint8_t *encKey  =  &m_cipherKey[0];
//     
//     unsigned int enclen = EVP_PKEY_size(evp_prikey);
//     std::uint8_t *iv = &m_iv[0];
//     
//     
//     auto ret = envelope_open(evp_prikey, reinterpret_cast<const unsigned char *>(inputBuffer), inputLength, encKey, enclen,iv,reinterpret_cast<unsigned char *>(outputBuffer));
//     if( ret <= 0)
//     {
//         //TODO throw
//         ret = 0;
//     }
    
    return plaintext_len;
}

int SealCipher::EVP_SealInit(EVP_CIPHER_CTX *ctx, const EVP_CIPHER *type,
                 unsigned char **ek, int *ekl, unsigned char *iv,
                 EVP_PKEY **pubk, int npubk)
{
    unsigned char key[EVP_MAX_KEY_LENGTH];
    int i;
    int rv = 0;

    if (type) {
        //EVP_CIPHER_CTX_reset(ctx);
        if (!EVP_EncryptInit_ex(ctx, type, NULL, NULL, NULL))
            return 0;
    }
    if ((npubk <= 0) || !pubk)
        return 1;
    if (EVP_CIPHER_CTX_rand_key(ctx, key) <= 0)
        return 0;

    /*if (EVP_CIPHER_CTX_iv_length(ctx)
            && RAND_bytes(iv, EVP_CIPHER_CTX_iv_length(ctx)) <= 0)
        goto err;

    for(auto i = 0; i < EVP_CIPHER_CTX_iv_length(ctx); ++i)
    {
        iv[i] = i;
    }*/
    
    if (!EVP_EncryptInit_ex(ctx, NULL, NULL, key, iv))
        goto err;

    for (i = 0; i < npubk; i++) {
        ekl[i] =
            EVP_PKEY_encrypt_old(ek[i], key, EVP_CIPHER_CTX_key_length(ctx),
                                 pubk[i]);
        if (ekl[i] <= 0) {
            rv = -1;
            goto err;
        }
    }
    rv = npubk;
err:
    OPENSSL_cleanse(key, sizeof(key));
    return rv;
}


/*
int SealCipher::EVP_SealInit(EVP_CIPHER_CTX *ctx, const EVP_CIPHER *type, unsigned char **ek, int *ekl, unsigned char *iv,              EVP_PKEY **pubk, int npubk)
{
     unsigned char key[EVP_MAX_KEY_LENGTH];
    
    //unsigned char *key = ek[0];
    
    int i;
    int rv = 0;

    if (type) 
    {
        //EVP_CIPHER_CTX_reset(ctx);
        if (!EVP_EncryptInit_ex(ctx, type, NULL, NULL, NULL))
        {
            return 0;
        }
    }
    
    if ((npubk <= 0) || !pubk)
    {
        return 1;
    }
    
    
    
    
    //int l = EVP_CIPH_CUSTOM_IV;
    //ctx->cipher->ctrl(ctx, EVP_CIPH_CUSTOM_KEY_LENGTH, 1, &l);
//     ctx->key = key;
//     ctx->key_len = EVP_MAX_KEY_LENGTH;
    
    
    
    //ctx->cipher->ctrl(ctx, type, 0, key);
    EVP_CIPHER_CTX_rand_key(ctx, key);
     //|->EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_RAND_KEY, 0, key);
    
    

    if (!EVP_EncryptInit_ex(ctx, NULL, NULL, key, iv))
    {
        std::cout << "Error init" << std::endl;
        goto err;
    }

    for (i = 0; i < npubk; i++) {
        ekl[i] =
            EVP_PKEY_encrypt_old(ek[i], key, EVP_CIPHER_CTX_key_length(ctx),
                                 pubk[i]);
        if (ekl[i] <= 0) {
            rv = -1;
            std::cout << "Error EVP_PKEY_encrypt_old" << std::endl;
            goto err;
        }
    }
    rv = npubk;
err:
    OPENSSL_cleanse(key, sizeof(key));
    return rv;
}*/


/*int SealCipher::envelope_seal(EVP_PKEY **pub_key, const unsigned char *plaintext, int plaintext_len, unsigned char **encrypted_key, int *encrypted_key_len, unsigned char *iv,	unsigned char *ciphertext)
{
        std::cout << __FUNCTION__ << std::endl;
    
	EVP_CIPHER_CTX *ctx;

	int ciphertext_len;

	int len;


	
	if(!(ctx = EVP_CIPHER_CTX_new())) 
        {
            std::cout << "error " << __LINE__ << std::endl;
        }

	
	if(1 != EVP_SealInit(ctx, EVP_aes_256_cbc(), encrypted_key, encrypted_key_len, iv, pub_key, 1))
        {
            std::cout << "error " << __LINE__ << std::endl;
        }
        
//         for(auto i = 0; i < 16; ++i)
//         {
//             std::cout << " "  << iv[i];
//         }
//     
//         std::cout << std::endl;
//         
//         std::cout << "--" << std::endl;
//         for(auto i = 0; i < 512; ++i)
//         {
//             std::cout << " "  << m_cipherKey[i];
//         }
//         std::cout << std::endl;
            
        
        

	/* Provide the message to be encrypted, and obtain the encrypted output.
	 * EVP_SealUpdate can be called multiple times if necessary
	 
	if(1 != EVP_SealUpdate(ctx, ciphertext, &len, plaintext, plaintext_len))
        {
            std::cout << "error " << __LINE__ << std::endl;
        }
	ciphertext_len = len;
        std::cout << "cipher text  len " << len << " plain " << plaintext << " len " << plaintext_len << std::endl;

	/* Finalise the encryption. Further ciphertext bytes may be written at
	 * this stage.
	 
	if(1 != EVP_SealFinal(ctx, ciphertext + len, &len)) 
        {
            std::cout << "error " << __LINE__ << std::endl;
        }
	ciphertext_len += len;

	/* Clean up 
	EVP_CIPHER_CTX_free(ctx);

	return ciphertext_len;
}*/

        
/*int SealCipher::envelope_open(EVP_PKEY *priv_key, const unsigned char *ciphertext, int ciphertext_len,	unsigned char *encrypted_key, int encrypted_key_len, unsigned char *iv,	unsigned char *plaintext)
{
    
    std::cout << __FUNCTION__ << " ciphertext_len " << ciphertext_len << std::endl;
    std::cout << "encrypted_key_len " << encrypted_key_len << std::endl;
    
    for(auto i = 0 ; i < ciphertext_len; i++)
    {
        std::cout << std::hex << ciphertext[i];
    }
    
    std::cout << std::dec << std::endl;
    
    
	EVP_CIPHER_CTX *ctx;

	int len;

	int plaintext_len;


	/* Create and initialise the context 
	if(!(ctx = EVP_CIPHER_CTX_new())) 
        {
            std::cout << "error " << __LINE__ << std::endl;
        }
        
        
//         for(auto i = 0; i < 16; ++i)
//         {
//             std::cout << std::hex  << iv[i] << " ";
//         }
//     
//         std::cout << std::endl;
//         
//         std::cout << "--" << std::endl;
//         for(auto i = 0; i < 512; ++i)
//         {
//             std::cout << std::hex  << encrypted_key[i] << " ";
//         }
//         std::cout << std::endl;
        

	/* Initialise the decryption operation. The asymmetric private key is
	 * provided and priv_key, whilst the encrypted session key is held in
	 * encrypted_key 
	if(1 != ::EVP_OpenInit(ctx, EVP_aes_256_cbc(), encrypted_key, encrypted_key_len, iv, priv_key))
        {
            std::cout << "EVP_OpenInit error " << __LINE__ << std::endl;
            return 0;
        }
		
        

	/* Provide the message to be decrypted, and obtain the plaintext output.
	 * EVP_OpenUpdate can be called multiple times if necessary
	 
	if(1 != EVP_OpenUpdate(ctx, plaintext, &len, ciphertext, ciphertext_len))
        {
            std::cout << "EVP_OpenUpdate error " << __LINE__ << std::endl;
            std::uint32_t err = ERR_get_error();
            std::cout << "EVP_OpenUpdate error " << err << std::endl;
        }
            
            
	plaintext_len = len;

	/* Finalise the decryption. Further plaintext bytes may be written at
	 * this stage.
	 
	if(1 != EVP_OpenFinal(ctx, plaintext + len, &len)) 
        {
            std::uint32_t err = ERR_get_error();
            std::cout << "EVP_OpenFinal error " << err << std::endl;
        }
	plaintext_len += len;

	/* Clean up 
	EVP_CIPHER_CTX_free(ctx);

	return plaintext_len;
}*/
        
        
        
int SealCipher::envelope_seal(EVP_PKEY **pub_key, const unsigned char *plaintext, int plaintext_len,
	unsigned char **encrypted_key, int *encrypted_key_len, unsigned char *iv,
	unsigned char *ciphertext)
{
	EVP_CIPHER_CTX *ctx;

	int ciphertext_len;

	int len;


	/* Create and initialise the context */
	if(!(ctx = EVP_CIPHER_CTX_new())) 
        {
            std::cout << "error " << __LINE__ << std::endl;
        }

	/* Initialise the envelope seal operation. This operation generates
	 * a key for the provided cipher, and then encrypts that key a number
	 * of times (one for each public key provided in the pub_key array). In
	 * this example the array size is just one. This operation also
	 * generates an IV and places it in iv. */
	if(1 != EVP_SealInit(ctx, EVP_aes_256_cbc(), encrypted_key,
		encrypted_key_len, iv, pub_key, 1))
        {
            std::cout << "error " << __LINE__ << std::endl;
        }

	/* Provide the message to be encrypted, and obtain the encrypted output.
	 * EVP_SealUpdate can be called multiple times if necessary
	 */
	if(1 != EVP_SealUpdate(ctx, ciphertext, &len, plaintext, plaintext_len))
        {
            std::cout << "error " << __LINE__ << std::endl;
        }
	ciphertext_len = len;

	/* Finalise the encryption. Further ciphertext bytes may be written at
	 * this stage.
	 */
	if(1 != EVP_SealFinal(ctx, ciphertext + len, &len)) 
        {
            std::cout << "error " << __LINE__ << std::endl;
        }
	ciphertext_len += len;

	/* Clean up */
	EVP_CIPHER_CTX_free(ctx);

	return ciphertext_len;
}

int SealCipher::envelope_open(EVP_PKEY *priv_key, const unsigned char *ciphertext, int ciphertext_len,
	unsigned char *encrypted_key, int encrypted_key_len, unsigned char *iv,
	unsigned char *plaintext)
{
	EVP_CIPHER_CTX *ctx;

	int len;

	int plaintext_len;


	/* Create and initialise the context */
	if(!(ctx = EVP_CIPHER_CTX_new())) 
        {
            std::cout << "error " << __LINE__ << std::endl;
        }

	/* Initialise the decryption operation. The asymmetric private key is
	 * provided and priv_key, whilst the encrypted session key is held in
	 * encrypted_key */
	if(1 != EVP_OpenInit(ctx, EVP_aes_256_cbc(), encrypted_key,
		encrypted_key_len, iv, priv_key))
        {
            std::cout << "error " << __LINE__ << std::endl;
        }
		

	/* Provide the message to be decrypted, and obtain the plaintext output.
	 * EVP_OpenUpdate can be called multiple times if necessary
	 */
	if(1 != EVP_OpenUpdate(ctx, plaintext, &len, ciphertext, ciphertext_len))
        {
            std::cout << "error " << __LINE__ << std::endl;
        }
            
            
	plaintext_len = len;

	/* Finalise the decryption. Further plaintext bytes may be written at
	 * this stage.
	 */
	if(1 != EVP_OpenFinal(ctx, plaintext + len, &len)) 
        {
            std::cout << "error " << __LINE__ << std::endl;
        }
	plaintext_len += len;

	/* Clean up */
	EVP_CIPHER_CTX_free(ctx);

	return plaintext_len;
}

void SealCipher::setIV(const std::vector<std::uint8_t>& iv)
{
    m_iv = iv;
}

void SealCipher::setCipherKey(const std::vector<std::uint8_t>& cipherKey)
{
    m_cipherKey = cipherKey;
}

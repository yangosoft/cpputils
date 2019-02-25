
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
    return 0;
}

std::size_t SealCipher::decrypt(const char *inputBuffer, std::size_t inputLength, char *outputBuffer , std::size_t &outLength  , IKey& key)
{
    return 0;
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


int SealCipher::envelope_seal(EVP_PKEY **pub_key, unsigned char *plaintext, int plaintext_len,
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

int SealCipher::envelope_open(EVP_PKEY *priv_key, unsigned char *ciphertext, int ciphertext_len,
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
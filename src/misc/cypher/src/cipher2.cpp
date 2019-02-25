#include "misc/cipher2.hpp"

#include <openssl/evp.h>
#include <openssl/engine.h>
#include <openssl/err.h>
#include <openssl/rand.h>
#include <openssl/rsa.h>
#include <openssl/evp.h>
#include <openssl/objects.h>
#include <openssl/x509.h>

#include <iostream>

using namespace CppUtils::Misc;
/*
RSA* loadPUBLICKeyFromString( const char* publicKeyStr )
{
  // A BIO is an I/O abstraction (Byte I/O?)
  
  // BIO_new_mem_buf: Create a read-only bio buf with data
  // in string passed. -1 means string is null terminated,
  // so BIO_new_mem_buf can find the dataLen itself.
  // Since BIO_new_mem_buf will be READ ONLY, it's fine that publicKeyStr is const.
  BIO* bio = BIO_new_mem_buf( (void*)publicKeyStr, -1 ) ; // -1: assume string is null terminated
  
  BIO_set_flags( bio, BIO_FLAGS_BASE64_NO_NL ) ; // NO NL
  
  // Load the RSA key from the BIO
  RSA* rsaPubKey = PEM_read_bio_RSA_PUBKEY( bio, NULL, NULL, NULL ) ;
  if( !rsaPubKey )
    printf( "ERROR: Could not load PUBLIC KEY!  PEM_read_bio_RSA_PUBKEY FAILED: %s\n", ERR_error_string( ERR_get_error(), NULL ) ) ;
  
  BIO_free( bio ) ;
  return rsaPubKey ;
}
*/

int some_func(char *buf, int size, int rwflag, void *userdata) {
    const std::string pass{ "123456" };
    sprintf(buf,"%s",pass.c_str());
    std::cout << "PASS " << std::string(buf) << std::endl;
    return pass.size();
}

void Cipher2::seal()
{
    EVP_CIPHER_CTX *ctx;
    unsigned char **encrypted_key;
    int *encrypted_key_len;
    int ciphertext_len;

    int len;
    int plaintext_len;
    const char *plaintext = "HELLO WORLD";
    /* Create and initialise the context */
    
    if(!(ctx = EVP_CIPHER_CTX_new())) {
        std::cout << "ctx failed" << std::endl;
        return;
    }
    
    if(ctx == nullptr)
    {
        std::cout << "error nullptr ctx" << std::endl;
        return;
    }
    
    EVP_CipherInit_ex(ctx, EVP_aes_256_cbc(), NULL, NULL, NULL,NULL);
    
    int ivLength = EVP_CIPHER_CTX_iv_length(ctx);
    std::cout << "Length: " << ivLength << std::endl;

    
    unsigned char iv[ivLength];

    for(int i = 0; i < ivLength ; ++i)
    {
        iv[i] = i;
    }
    std::cout << "IV created" << std::endl;    
    
    unsigned char key[EVP_MAX_KEY_LENGTH];
    
    unsigned char ciphertext[4096];
    
    std::string keyPath{"/home/dzayas/custom/cpputils-github/src/public.pem"};
    
    RSA *rsa = getPublicKey(keyPath);
    
    EVP_PKEY *evp_pubkey = EVP_PKEY_new();
    EVP_PKEY *evp_prikey = EVP_PKEY_new();
    
    EVP_PKEY_assign_RSA(evp_pubkey,rsa);
    
    int i;
    int rv = 0;
    const EVP_CIPHER *type = EVP_aes_256_cbc();
    
    
 
    
    
    if (!EVP_EncryptInit_ex(ctx, type, NULL, key, iv))
    {
        std::cout << "Error init" << std::endl;
        return;
    }
    
    std::cout << "EVP_EncryptInit_ex" << std::endl;
    
    if(1 != EVP_SealUpdate(ctx, ciphertext, &len, (const unsigned char*)plaintext, plaintext_len))
    {
        std::cout << "Error seal update" << std::endl;
        return;
    }
    
    std::cout << "EVP_SealUpdate" << std::endl;
    
    if(1 != EVP_SealFinal(ctx, ciphertext + len, &len)) 
    {
        std::cout << "Error final" << std::endl;
        return;
    }
    
    std::cout << "EVP_SealFinal" << std::endl;
    
    
    
    std::cout << ciphertext << std::endl;
    
    ciphertext_len += len;
        
    std::cout << "len: " << ciphertext_len << std::endl;
    for(auto i = 0; i < ciphertext_len; ++i)
    {
        std::cout << ciphertext[i] << " ";
    }
    

    /* Clean up */
    EVP_CIPHER_CTX_free(ctx);
    
}


bool Cipher2::decryptFile(const std::string& pemCertificatePath, unsigned char* msg)
{
      


  RSA *rsa = RSA_new();
  RSA *rsa2 = RSA_new();
  BIO *bp_public = nullptr;
  RSA *pubkey = nullptr;
  
  BIO *keybio = BIO_new(BIO_s_file());
  BIO_read_filename(keybio, pemCertificatePath.c_str());
  std::cout <<  "PRIVATE " << pemCertificatePath << std::endl;
  auto f = fopen(pemCertificatePath.c_str(), "r");
  
  rsa = PEM_read_RSAPrivateKey(f, NULL,  some_func, NULL);
  
  if(nullptr == rsa)
  {
      std::cout << "RSA null" << std::endl;
  }
  
  

  /*RSA_print(keybio, rsa, 0);
  char buffer [2048];

  while (BIO_read (keybio, buffer, 2048) > 0)
  {
      std::cout << "Reading BIO..." << std::endl;
  }
  
  
  
  if (pubkey == nullptr)
  {
      std::cout <<"pubkey went wrong" << std::endl;
//     return false;
  }
  if( rsa == nullptr)
  {
    std::cout <<"rsa went wrong" << std::endl;
    
  }*/

  

  
  
  unsigned char decrypted[RSA_size(rsa)];
  
  std::cout << "Calling decrypt" << std::endl;
  
  int size = RSA_private_decrypt(RSA_size(rsa), msg, decrypted, rsa, RSA_PKCS1_OAEP_PADDING);
  std:: cout << size << " bytes decrypted" << std::endl;
  

  std::cout << decrypted << std::endl;
  
  
  //decrypt with private
    
  
  
    
    return true;
}

RSA* Cipher2::getPublicKey(const std::string& pemCertificatePath)
{
  RSA *rsa = RSA_new();
  
 
  
  BIO *keybio = BIO_new(BIO_s_file());
  BIO_read_filename(keybio, pemCertificatePath.c_str());
  rsa = PEM_read_bio_RSA_PUBKEY(keybio, &rsa, NULL, NULL);

  
  return rsa;
}


RSA* Cipher2::getPrivateKey(const std::string& pemCertificatePath)
{
   RSA *rsa = RSA_new();
  RSA *rsa2 = RSA_new();
  BIO *bp_public = nullptr;
  RSA *pubkey = nullptr;
  
  BIO *keybio = BIO_new(BIO_s_file());
  BIO_read_filename(keybio, pemCertificatePath.c_str());
  std::cout <<  "PRIVATE " << pemCertificatePath << std::endl;
  auto f = fopen(pemCertificatePath.c_str(), "r");
  
  rsa = PEM_read_RSAPrivateKey(f, NULL,  some_func, NULL);

  
  return rsa;
}

Cipher2::Cipher2()
{
    OpenSSL_add_all_algorithms();
    OpenSSL_add_all_ciphers();
}

bool Cipher2::encryptFile(const std::string& pemCertificatePath)
{
  
    
  RSA *rsa = RSA_new();
  
 
  
  BIO *keybio = BIO_new(BIO_s_file());
  BIO_read_filename(keybio, pemCertificatePath.c_str());
  rsa = PEM_read_bio_RSA_PUBKEY(keybio, &rsa, NULL, NULL);

  RSA_print(keybio, rsa, 0);
  
  

  
 
  if( rsa == nullptr)
  {
    std::cout <<"rsa went wrong" << std::endl;
    return false;
  }

  char msg[] = "Hello";
  

  
  
  unsigned char encrypted[RSA_size(rsa)];
  
  std::cout << "Calling encrypt" << std::endl;
  
  RSA_public_encrypt(5, (unsigned char *)msg, encrypted, rsa, RSA_PKCS1_OAEP_PADDING);

  std::cout <<"Result \n" << encrypted << std::endl;
  
  
  //decrypt with private
decryptFile("/home/dzayas/custom/cpputils-github/src/private.pem",encrypted);
  
  
    
    return true;
}


int Cipher2::EVP_SealInit(EVP_CIPHER_CTX *ctx, const EVP_CIPHER *type,
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


int Cipher2::envelope_seal(EVP_PKEY **pub_key, unsigned char *plaintext, int plaintext_len,
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

int Cipher2::envelope_open(EVP_PKEY *priv_key, unsigned char *ciphertext, int ciphertext_len,
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



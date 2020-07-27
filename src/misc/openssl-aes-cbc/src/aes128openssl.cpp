#include <stdint.h>
#include <openssl/conf.h>
#include <openssl/evp.h>
#include <openssl/err.h>
#include <string.h>


static const uint8_t pKeyAES1[16] = {0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA};
static const uint8_t pInitVectAES1[16]= {0xBB,0xBB,0xBB,0xBB,0xBB,0xBB,0xBB,0xBB,0xBB,0xBB,0xBB,0xBB,0xBB,0xBB,0xBB,0xBB};

/* Plaintext */
uint8_t aPlaintextCBC[128] =
                        { 0xE2,0xBE,0xC1,0x6B ,0x96,0x9F,0x40,0x2E ,0x11,0x7E,0x3D,0xE9 ,0x2A,0x17,0x93,0x73 ,
                          0x57,0x8A,0x2D,0xAE ,0x9C,0xAC,0x03,0x1E ,0xAC,0x6F,0xB7,0x9E ,0x51,0x8E,0xAF,0x45 ,
                          0x46,0x1C,0xC8,0x30 ,0x11,0xE4,0x5C,0xA3 ,0x19,0xC1,0xFB,0xE5 ,0xEF,0x52,0x0A,0x1A ,
                          0x45,0x24,0x9F,0xF6 ,0x17,0x9B,0x4F,0xDF ,0x7B,0x41,0x2B,0xAD ,0x10,0x37,0x6C,0xE6};

void handleErrors(char *string)
{
    printf("ERROR %s\n",string);
}

int encrypt(unsigned char *ciphertext)
{
    EVP_CIPHER_CTX *ctx;

    int len;

    int ciphertext_len;

    /* Create and initialise the context */
    if(!(ctx = EVP_CIPHER_CTX_new()))
    {
        handleErrors("Error context!");
    }

    /*
     * Initialise the encryption operation. IMPORTANT - ensure you use a key
     * and IV size appropriate for your cipher
     * In this example we are using 128 bit AES (i.e. a 128 bit key). The
     * IV size for *most* modes is the same as the block size. For AES this
     * is 128 bits
     */
    if(1 != EVP_EncryptInit_ex(ctx, EVP_aes_128_cbc(), NULL, pKeyAES1, pInitVectAES1))
    {
        handleErrors("INIT");
    }

    /*
     * Provide the message to be encrypted, and obtain the encrypted output.
     * EVP_EncryptUpdate can be called multiple times if necessary
     */
    if(1 != EVP_EncryptUpdate(ctx, ciphertext, &len, aPlaintextCBC, 128))
    {
        handleErrors("UPDATE");
    }
    ciphertext_len = len;

    /*
     * Finalise the encryption. Further ciphertext bytes may be written at
     * this stage.
     */
    if(1 != EVP_EncryptFinal_ex(ctx, ciphertext + len, &len))
    {
        handleErrors("");
    }
    ciphertext_len += len;

    /* Clean up */
    EVP_CIPHER_CTX_free(ctx);

    return ciphertext_len;
}

int decrypt(unsigned char *ciphertext, int ciphertext_len, unsigned char *plaintext)
{
    EVP_CIPHER_CTX *ctx;

    int len;

    int plaintext_len;

    /* Create and initialise the context */
    if(!(ctx = EVP_CIPHER_CTX_new()))
        handleErrors("");

    /*
     * Initialise the decryption operation. IMPORTANT - ensure you use a key
     * and IV size appropriate for your cipher
     * In this example we are using 256 bit AES (i.e. a 256 bit key). The
     * IV size for *most* modes is the same as the block size. For AES this
     * is 128 bits
     */
    if(1 != EVP_DecryptInit_ex(ctx, EVP_aes_128_cbc(), NULL,  pKeyAES1, pInitVectAES1))
        handleErrors("");

    /*
     * Provide the message to be decrypted, and obtain the plaintext output.
     * EVP_DecryptUpdate can be called multiple times if necessary.
     */
    if(1 != EVP_DecryptUpdate(ctx, plaintext, &len, ciphertext, ciphertext_len))
        handleErrors("");
    plaintext_len = len;

    /*
     * Finalise the decryption. Further plaintext bytes may be written at
     * this stage.
     */
    if(1 != EVP_DecryptFinal_ex(ctx, plaintext + len, &len))
        handleErrors("");
    plaintext_len += len;

    /* Clean up */
    EVP_CIPHER_CTX_free(ctx);

    return plaintext_len;
}


int main (void)
{
   
    unsigned char ciphertext[256];

    /* Buffer for the decrypted text */
    unsigned char decryptedtext[256];

    int decryptedtext_len, ciphertext_len;

    /* Encrypt the plaintext */
   
    ciphertext_len = encrypt (ciphertext);
    printf("Ciphered data is %d bytes:\n",ciphertext_len);
    BIO_dump_fp (stdout, (const char *)ciphertext, ciphertext_len);

    
    /* Decrypt the ciphertext */
    decryptedtext_len = decrypt(ciphertext, ciphertext_len, decryptedtext);
    printf("Decrypted data is %d bytes:\n",decryptedtext_len);
    BIO_dump_fp (stdout, (const char *)decryptedtext, decryptedtext_len);
    
    printf("Comparing with hardcoded original data...\n");
    for(int i = 0; i < decryptedtext_len; i++)
    {
        if(decryptedtext[i] != aPlaintextCBC[i])
        {
            printf("ERROR data mismatch\n");
            return -1;
        }
    }
    

    printf("OK SAME DATA!\n");
    return 0;
}

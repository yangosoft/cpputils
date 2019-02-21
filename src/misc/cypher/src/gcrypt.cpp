#include <iostream>

#include <stdio.h>

#include <misc/gcrypt.hpp>




using namespace CppUtils::Misc;

bool Gcrypt::init()
{
     gcry_error_t err = 0;

    /* We don't want to see any warnings, e.g. because we have not yet
       parsed program options which might be used to suppress such
       warnings. */
    err = gcry_control (GCRYCTL_SUSPEND_SECMEM_WARN);

    /* ... If required, other initialization goes here.  Note that the
       process might still be running with increased privileges and that
       the secure memory has not been intialized.  */

    /* Allocate a pool of 16k secure memory.  This make the secure memory
       available and also drops privileges where needed.  */
    err |= gcry_control (GCRYCTL_INIT_SECMEM, 16384, 0);

    /* It is now okay to let Libgcrypt complain when there was/is
       a problem with the secure memory. */
    err |= gcry_control (GCRYCTL_RESUME_SECMEM_WARN);

    /* ... If required, other initialization goes here.  */

    /* Tell Libgcrypt that initialization has completed. */
    err |= gcry_control (GCRYCTL_INITIALIZATION_FINISHED, 0);

    if (err) {
        return false;
    }
    
    return true;
}

bool Gcrypt::createKeys(const std::string& filename)
{
    const char* fname = filename.c_str();
    FILE* lockf = fopen(fname, "wb");
    if (!lockf) {
        return false;
    }

    /* Generate a new RSA key pair. */
    gcry_error_t err = 0;
    gcry_sexp_t rsa_parms;
    gcry_sexp_t rsa_keypair;

    err = gcry_sexp_build(&rsa_parms, NULL, "(genkey (rsa (nbits 4:4096)(rsa-use-e 5:65539)))");
    if (err) {
        //xerr("gcrypt: failed to create rsa params");
        return false;
    }

    err = gcry_pk_genkey(&rsa_keypair, rsa_parms);
    if (err) {
//         xerr("gcrypt: failed to create rsa key pair");
        return false;
    }

//     printf("RSA key generation complete! Please enter a password to lock \n"
//            "your key pair. This password must be committed to memory. \n\n");

    /* Grab a key pair password and create an encryption context with it. */
    gcry_cipher_hd_t aes_hd;
    get_aes_ctx(&aes_hd);

    /* Encrypt the RSA key pair. */
    size_t rsa_len = get_keypair_size(4096);
    void* rsa_buf = calloc(1, rsa_len);
    if (!rsa_buf) {
        return false;
        //xerr("malloc: could not allocate rsa buffer");
    }
    gcry_sexp_sprint(rsa_keypair, GCRYSEXP_FMT_CANON, rsa_buf, rsa_len);

    /*err = gcry_cipher_encrypt(aes_hd, (unsigned char*) rsa_buf, 
                              rsa_len, NULL, 0);
    if (err) {
        //xerr("gcrypt: could not encrypt with AES");
        return false;
    }*/

    /* Write the encrypted key pair to disk. */
    if (fwrite(rsa_buf, rsa_len, 1, lockf) != 1) {
        //perror("fwrite");
        return false;
        //xerr("fwrite() failed");
    }

    /* Release contexts. */
    gcry_sexp_release(rsa_keypair);
    gcry_sexp_release(rsa_parms);
    //gcry_cipher_close(aes_hd);
    free(rsa_buf);
    fclose(lockf);

}

size_t Gcrypt::get_keypair_size(int nbits) const
{
    size_t aes_blklen = gcry_cipher_get_algo_blklen(GCRY_CIPHER_AES128);

    // format overhead * {pub,priv}key (2 * bits)
    size_t keypair_nbits = 4 * (2 * nbits);

    size_t rem = keypair_nbits % aes_blklen;
    return (keypair_nbits + rem) / 8;
}

void Gcrypt::get_aes_ctx(gcry_cipher_hd_t* aes_hd) const
{
    /*const size_t keylen = 16;
    char passwd_hash[keylen];

    char* passwd = getpass("Keypair Password: ");
    size_t pass_len = passwd ? strlen(passwd) : 0;
    if (pass_len == 0) {
        xerr("getpass: not a valid password");
    }

    int err = gcry_cipher_open(aes_hd, GCRY_CIPHER_AES128, 
                               GCRY_CIPHER_MODE_CFB, 0);
    if (err) {
        xerr("gcrypt: failed to create aes handle");
    }

    gcry_md_hash_buffer(GCRY_MD_MD5, (void*) &passwd_hash, 
                        (const void*) passwd, pass_len);

    err = gcry_cipher_setkey(*aes_hd, (const void*) &passwd_hash, keylen);
    if (err) {
        xerr("gcrypt: could not set cipher key");
    }

    err = gcry_cipher_setiv(*aes_hd, (const void*) &passwd_hash, keylen);
    if (err) {
        xerr("gcrypt: could not set cipher initialization vector");
    }*/
}
//Code from https://github.com/vedantk/gcrypt-example


#include <iostream>


#include <misc/cipher2.hpp>
#include <misc/cypher.hpp>
#include <misc/gcrypt.hpp>
#include <misc/pemkey.hpp>

#include <misc/asymmetricalcipher.hpp>
#include <misc/sealcipher.hpp>


#include <cstdint>
#include <vector>

gcry_error_t err;


int main(int argc, char** argv)
{
    
    CppUtils::Misc::PemKey pr{"/home/dzayas/custom/cpputils-github/src/private.pem"};
    CppUtils::Misc::PemKey pu{"/home/dzayas/custom/cpputils-github/src/public.pem"};
    pr.load("123456");
    RSA *rsaPr = pr.getAsRSA();
    RSA *rsaPu = pu.getAsRSA();
    
    CppUtils::Misc::SealCipher sealC;
    
     CppUtils::Misc::AsymmetricalCipher sc;
    
        std::size_t iSize = 128;
        std::size_t oSize = 512;
        char inBuffer[iSize*4];
        char outBuffer[oSize];
        char outBuffer2[oSize];
        
        
        sprintf(inBuffer, "%s", "Hello world :)");
        
    
    std::vector<std::uint8_t> myIv(16);
    
    std::vector<std::uint8_t> myCipherKey(EVP_MAX_KEY_LENGTH);
    
    for(auto i = 0; i < myIv.size(); ++i)
    {
        myIv.at(i) = 'a'+i;
    }
    
    for(auto i = 0; i < myCipherKey.size(); ++i)
    {
        myCipherKey.at(i) = '0'+i;
    }
    
    sealC.setIV(myIv);
    sealC.setCipherKey(myCipherKey);
    
    auto n1 = sealC.encrypt( inBuffer,strlen(inBuffer), outBuffer, oSize, pu );
    std::cout << "n1 " << std::dec << n1 << std::endl;
    std::cout << std::string(outBuffer) << std::endl;
    
    
        
    auto n = sealC.decrypt( outBuffer,n1, outBuffer2, oSize, pr );
    std::cout << "n " << std::dec << n << std::endl;
    std::cout << std::string(outBuffer2) << std::endl;
    
    return 0;
    
    
    
    
       
        
        
//     auto n1 = sc.encrypt( inBuffer,strlen(inBuffer), outBuffer, oSize, pu );
//     std::cout << "n1 " << n1 << std::endl;
//     std::cout << std::string(outBuffer) << std::endl;
//         
//     auto n = sc.decrypt( outBuffer,n1, outBuffer2, oSize, pr );
//     std::cout << "n " << n << std::endl;
//     std::cout << std::string(outBuffer2) << std::endl;
//         
//     return 0;
    

    
    
  CppUtils::Misc::Cipher2 c3;
  
    RSA *rsa_pubkey= pu.getAsRSA(); //c3.getPublicKey("/home/dzayas/custom/cpputils-github/src/public.pem"); // RSA_new();
    RSA *rsa_prikey= pr.getAsRSA(); //c3.getPrivateKey("/home/dzayas/custom/cpputils-github/src/private.pem"); // RSA_new();
    EVP_PKEY *evp_pubkey = EVP_PKEY_new();
    EVP_PKEY *evp_prikey = EVP_PKEY_new();
//     FILE *rsa_prikey_file = NULL;
//     FILE *rsa_pubkey_file = NULL;
//     rsa_pubkey_file = fopen("pubkey.pem", "r");
//     if (!rsa_pubkey_file)
//     {
//         fprintf(stderr, "Error loading PEM RSA Public Key File.\n");
//         exit(2);
//     }

//     PEM_read_RSA_PUBKEY(rsa_pubkey_file, &rsa_pubkey,NULL, NULL);

    EVP_PKEY_assign_RSA(evp_pubkey,rsa_pubkey);

//     rsa_prikey_file = fopen("key.pem", "r");
//     if (!rsa_prikey_file)
//     {
//         fprintf(stderr, "Error loading PEM RSA private Key File.\n");
//         exit(2);
//     }
//     PEM_read_RSAPrivateKey(rsa_prikey_file, &rsa_prikey,NULL, NULL);

    EVP_PKEY_assign_RSA(evp_prikey,rsa_prikey);


    unsigned char *plaintext = (unsigned char*) "The quick brown fox jumps over thes lazy dog";
    unsigned char ciphertext[256] = {};
    unsigned char plaintextt[256] = {};
    int ciphertextlength;
    unsigned char *encKey  = (unsigned char*)malloc(RSA_size(rsa_pubkey));
    unsigned char iv[16] = {};
    unsigned char iv2[16] = {};
    unsigned int enclen = EVP_PKEY_size(evp_prikey);
    
    for(auto i = 0; i < 16; ++i)
    {
        iv[i] = i;
    }
    
    auto length = c3.envelope_seal(&evp_pubkey, plaintext,strlen((const char*)plaintext),&encKey, &ciphertextlength,iv,ciphertext);
    
    
    for(auto i = 0; i < 16; ++i)
    {
        iv2[i] = i;
    }
    c3.envelope_open(evp_prikey, ciphertext, length, encKey, enclen,iv2,plaintextt);

    std::cout <<"Result: "<<plaintextt<< std::endl;

    EVP_PKEY_free(evp_pubkey);
    EVP_PKEY_free(evp_prikey);
//     free(ciphertext);
//     free(encKey);
  
  
  //c3.seal();
  //return 0;
    
    CppUtils::Misc::Cipher2 c2;
    c2.encryptFile("/home/dzayas/custom/cpputils-github/src/public.pem");
    
    return 0;
    CppUtils::Misc::Gcrypt c;
    std::cout << c.init() << std::endl;
  
    
    c.createKeys("keys.keys");
  
    
    
    
    char* fname = "keys.keys";
    FILE* lockf = fopen(fname, "rb");
    if (!lockf) {
        std::cerr<< "fopen() failed" << std::endl;
        return 1;
    }
    
     /* Read and decrypt the key pair from disk. */
    size_t rsa_len = c.get_keypair_size(4096);
    void* rsa_buf = calloc(1, rsa_len);
    if (!rsa_buf) {
        std::cerr<< "malloc: could not allocate rsa buffer\n";
    }

    if (fread(rsa_buf, rsa_len, 1, lockf) != 1) {
        std::cerr<< "fread() failed\n";
    }
    
    
    /* Load the key pair components into sexps. */
    gcry_sexp_t rsa_keypair;
    err = gcry_sexp_new(&rsa_keypair, rsa_buf, rsa_len, 0);
    gcry_sexp_t pubk = gcry_sexp_find_token(rsa_keypair, "public-key", 0);
    gcry_sexp_t privk = gcry_sexp_find_token(rsa_keypair, "private-key", 0);

    {
         FILE* lockf = fopen("keys.keys.private", "wb");
        size_t rsa_len = c.get_keypair_size(4096);
        void* rsa_buf = calloc(1, rsa_len);
        if (!rsa_buf) {
            return 0;
            
        }
    
        gcry_sexp_sprint(privk, GCRYSEXP_FMT_CANON, rsa_buf, rsa_len);
         if (fwrite(rsa_buf, rsa_len, 1, lockf) != 1) {
      
            return 0;
       
        }
    }
    
    /* Create a message. */
    gcry_mpi_t msg;
    gcry_sexp_t data;
    const unsigned char* s = (const unsigned char*) "Hello world.";
    err = gcry_mpi_scan(&msg, GCRYMPI_FMT_USG, s, 
                        strlen((const char*) s), NULL);
    if (err) {
        std::cerr<< "failed to create a mpi from the message\n";
    }

    err = gcry_sexp_build(&data, NULL,"(data (flags raw) (value %m))", msg);
    if (err) {
        std::cerr<< "failed to create a sexp from the message\n";
    }

    /* Encrypt the message. */
    gcry_sexp_t ciph;
    err = gcry_pk_encrypt(&ciph, data, pubk);
    if (err) {
        std::cerr<< "gcrypt: encryption failed\n";
    }

    /* Decrypt the message. */
    gcry_sexp_t plain;
    err = gcry_pk_decrypt(&plain, ciph, privk);
    if (err) {
        std::cerr<< "gcrypt: decryption failed\n";
    }

    /* Pretty-print the results. */
    gcry_mpi_t out_msg = gcry_sexp_nth_mpi(plain, 0, GCRYMPI_FMT_USG);
    printf("Original:\n");
    gcry_mpi_dump(msg);
    printf("\n" "Decrypted:\n");
    gcry_mpi_dump(out_msg);
    printf("\n");

    if (gcry_mpi_cmp(msg, out_msg)) {
        std::cerr<< "data corruption!\n";
    } 

    printf("Messages match.\n");

    unsigned char obuf[64] = { 0 };
    err = gcry_mpi_print(GCRYMPI_FMT_USG, (unsigned char*) &obuf, 
                         sizeof(obuf), NULL, out_msg);
    if (err) {
        std::cerr<< "failed to stringify mpi\n";
    }
    printf("-> %s\n", (char*) obuf);


    /* Release contexts. */
    gcry_mpi_release(msg);
    gcry_mpi_release(out_msg);
    gcry_sexp_release(rsa_keypair);
    gcry_sexp_release(pubk);
    gcry_sexp_release(privk);
    gcry_sexp_release(data);
    gcry_sexp_release(ciph);
    gcry_sexp_release(plain);
//     gcry_cipher_close(aes_hd);
    free(rsa_buf);
    fclose(lockf);
    
    return 0;
}



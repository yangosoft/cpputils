#include <iostream>

#include <misc/cypher.hpp>
#include <misc/gcrypt.hpp>

int main(int argc, char** argv)
{
    CppUtils::Misc::Gcrypt c;
    std::cout << c.init() << std::endl;
    c.createKeys();
    gcry_error_t err;
    
    
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



#include "misc/cipher2.hpp"



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


bool Cipher2::decryptFile(const std::string& pemCertificatePath, unsigned char* msg)
{
    
   


  RSA *rsa = RSA_new();
  RSA *rsa2 = RSA_new();
  BIO *bp_public = nullptr;
  RSA *pubkey = nullptr;
  
  BIO *keybio = keybio = BIO_new(BIO_s_file());
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

bool Cipher2::encryptFile(const std::string& pemCertificatePath)
{
  OpenSSL_add_all_algorithms();
  OpenSSL_add_all_ciphers();
    
  RSA *rsa = RSA_new();
  BIO *bp_public = nullptr;
 
  
  BIO *keybio = keybio = BIO_new(BIO_s_file());
  BIO_read_filename(keybio, pemCertificatePath.c_str());
  rsa = PEM_read_bio_RSA_PUBKEY(keybio, &rsa, NULL, NULL);

  RSA_print(keybio, rsa, 0);
  char buffer [2048];

  /*while (BIO_read (keybio, buffer, 2048) > 0)
  {
      std::cout << "Reading BIO..." << std::endl;
  }*/
  
  BIO_free(bp_public);
  
 
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

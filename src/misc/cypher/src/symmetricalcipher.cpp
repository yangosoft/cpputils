
#include <misc/symmetricalcipher.hpp>

using namespace CppUtils::Misc;


SymmetricalCipher::SymmetricalCipher()
{
    OpenSSL_add_all_algorithms();
    OpenSSL_add_all_ciphers();
}


std::size_t SymmetricalCipher::encrypt(const char *inputBuffer, std::size_t inputLength, char *outputBuffer , std::size_t &outLength  , IKey& key)
{

  RSA *rsa = key.getAsRSA();
   
  if( rsa == nullptr)
  {
      //TODO: throw 
//     std::cout <<"rsa went wrong" << std::endl;
    return 0;
  }
  
  //TODO: ugly, fix sign comparisons!
  if(inputLength >= RSA_size(rsa) - 41)
  {
        //trhow
        return 0;
  }


  int out = RSA_public_encrypt(inputLength, reinterpret_cast<const unsigned char*>(inputBuffer), reinterpret_cast<unsigned char*>(outputBuffer), rsa, RSA_PKCS1_OAEP_PADDING);
  if( out == -1 )
  {
      return 0;
  }
  
  outLength = out;
  
  return outLength;
    
}

std::size_t SymmetricalCipher::decrypt(const char *inputBuffer, std::size_t inputLength, char *outputBuffer , std::size_t &outLength  , IKey& key)
{
    RSA *rsa = key.getAsRSA();
    
    
    int size = RSA_private_decrypt(RSA_size(rsa),  reinterpret_cast<const unsigned char*>(inputBuffer), reinterpret_cast<unsigned char*>(outputBuffer), rsa, RSA_PKCS1_OAEP_PADDING);
    if(size == -1)
    {
        return 0;
    }
    
    outLength = size;
    return outLength;
}
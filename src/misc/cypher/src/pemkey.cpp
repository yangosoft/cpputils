
#include <misc/pemkey.hpp>

#include <functional>

#include <openssl/evp.h>
#include <openssl/engine.h>
#include <openssl/err.h>
#include <openssl/rand.h>
#include <openssl/rsa.h>
#include <openssl/evp.h>
#include <openssl/objects.h>
#include <openssl/x509.h>
#include <openssl/pem.h>
#include <openssl/rsa.h>
#include <openssl/conf.h>

using namespace CppUtils::Misc;

PemKey* pThis;

int getPassCb(char *buf, int size, int rwflag, void *userdata)
{
    return pThis->getPassCb(buf, size, rwflag, userdata);
}


PemKey::PemKey(const std::string& path): m_path(std::move(path))
{
    
}


int PemKey::getPassCb(char *buf, int size, int rwflag, void *userdata) {
    sprintf(buf,"%s",m_password.c_str());
    return m_password.size();
}
            
bool PemKey::load(const std::string &password)
{
    m_password = std::move(password);
    return true;
}


RSA* PemKey::getAsRSA()
{
  RSA *rsa = RSA_new();

  BIO *keybio = BIO_new(BIO_s_file());
  BIO_read_filename(keybio, m_path.c_str());
  if(m_password.empty())
  {
        rsa = PEM_read_bio_RSA_PUBKEY(keybio, &rsa, nullptr, nullptr);
  }else
  {
        auto f = fopen(m_path.c_str(), "r");
        pThis = this;
        rsa = PEM_read_RSAPrivateKey(f, nullptr,  &::getPassCb, nullptr);
  }

  
  return rsa;
}
            
    
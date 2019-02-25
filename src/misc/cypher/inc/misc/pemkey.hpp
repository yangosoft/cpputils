#ifndef __CCPUTILS_PEMKEY_h__
#define __CCPUTILS_PEMKEY_h__

#include <misc/ikey.hpp>



namespace CppUtils
{
    namespace Misc
    {
        
        class PemKey: public IKey
        {
        public:
            PemKey(const std::string& path);
            
            bool load(const std::string &password) override;
            RSA* getAsRSA() override;
            int getPassCb(char *buf, int size, int rwflag, void *userdata);
            
        private:
            std::string m_path;
            std::string m_password;

            
            
        };
    }
}


#endif
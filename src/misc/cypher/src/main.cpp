#include <iostream>

#include <misc/cypher.hpp>
#include <misc/gcrypt.hpp>

int main(int argc, char** argv)
{
    CppUtils::Misc::Gcrypt c;
    std::cout << c.init() << std::endl;
    
    return 0;
}



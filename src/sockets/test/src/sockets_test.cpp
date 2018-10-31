#include <limits.h>
#include <cpputils/sockets/example.h>
#include <gtest/gtest.h>
namespace
{


TEST(ExampleTests, TestGet)
{

    CppUtils::example ex;
    
    EXPECT_NE(1, 2);
}

};

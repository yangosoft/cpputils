#include <limits.h>
#include <cpputils/sockets/socketclient.h>
#include <gtest/gtest.h>
namespace
{


TEST(ExampleTests, TestGet)
{

    CppUtils::TSocketClient s("localhost",8999);
    s.tryConnect();
    bool ok = s.writeData("Hello world!");
    
    
    EXPECT_TRUE(ok);
}

};

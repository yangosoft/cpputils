#include <chrono>
#include <functional>
#include <iostream>
#include <limits.h>



#include <cpputils/measuretime/measuretime.h>


#include <gtest/gtest.h>
namespace {

using namespace std;

void executeMe(int i)
{

    while (i > 0)
        i--;
}

    

TEST(ExampleTests, TestGet) {

    std::function<void(int)> fExec = executeMe;
    CppUtils::MeasureTime<  std::chrono::milliseconds >::execute(fExec,1000);
    EXPECT_TRUE(true);


}


};

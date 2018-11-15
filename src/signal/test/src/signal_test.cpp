
#include <iostream>
#include <gtest/gtest.h>

#include <cpputils/signal/signal.h>



namespace
{


TEST(SignalTest, TestTest)
{
        CppUtils::Signal<int, int> onEvent;

        onEvent.bind([](int a, int b) {
            std::cout << "Event triggered " << a << ", " << b << "\n";
            EXPECT_EQ(a,10);
            EXPECT_EQ(b,20);
        });

        onEvent.trigger(10, 20);
}

};

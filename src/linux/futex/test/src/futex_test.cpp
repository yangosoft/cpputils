#include <limits.h>

#include <futex/futex.hpp>
#include <futex/shared_futex.hpp>
#include <gtest/gtest.h>

#include <iostream>

namespace
{

TEST(ExampleFutex, TestInstance)
{
    CppUtils::Futex futex;
    futex.lock();
    futex.unlock();

    EXPECT_TRUE(true);
}

TEST(ExampleFutex, TestPost)
{
    std::atomic_int32_t atom(0);
    CppUtils::Futex futex(&atom);

    std::thread t([&futex]() {
        auto ret = futex.wait(0);
        EXPECT_NE(ret, -1);
    });

    std::thread t2([&futex]() {
        auto ret = futex.wait(0);
        EXPECT_NE(ret, -1);
    });

    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    atom.store(2);
    auto ret = futex.post(2);
    EXPECT_NE(ret, -1);

    atom.store(0);
    ret = futex.post(2);
    EXPECT_NE(ret, -1);

    t.join();
    t2.join();
}

TEST(ExampleFutex, TestShared)
{
    CppUtils::SharedFutex futex("/test_futex");
    futex.lock();
    futex.unlock();

    EXPECT_TRUE(true);
}

};  // namespace

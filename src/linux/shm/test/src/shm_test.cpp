#include <limits.h>

#include <shm/shm.hpp>

#include <gtest/gtest.h>

#include <iostream>

namespace
{

TEST(ExampleShm, TestInstance)
{
    CppUtils::Shm shm("/test_shm");
    auto ret = shm.allocate(sizeof(int32_t));
    EXPECT_NE(ret, -1);

    void* ptr = shm.get_raw_ptr();
    int32_t* ptr_int = reinterpret_cast<int32_t*>(ptr);
    std::cout << "ptr_int: " << *ptr_int << std::endl;
    *ptr_int = 42;

    int32_t val = *ptr_int;
    EXPECT_EQ(val, 42);

    shm.close();
    shm.unlink();

    EXPECT_TRUE(true);
}

TEST(ExampleShm, TestExisting)
{
    CppUtils::Shm shm("/test_shm");
    auto ret = shm.allocate(sizeof(int32_t));
    EXPECT_NE(ret, -1);

    void* ptr = shm.get_raw_ptr();
    int32_t* ptr_int = reinterpret_cast<int32_t*>(ptr);
    std::cout << "ptr_int: " << *ptr_int << std::endl;
    *ptr_int = 42;

    int32_t val = *ptr_int;
    EXPECT_EQ(val, 42);

    shm.close();

    CppUtils::Shm shm2("/test_shm");
    ret = shm.open_existing(sizeof(int32_t));
    EXPECT_NE(ret, -1);
    ptr = shm.get_raw_ptr();
    ptr_int = reinterpret_cast<int32_t*>(ptr);
    std::cout << "ptr_int: " << *ptr_int << std::endl;

    val = *ptr_int;
    EXPECT_EQ(val, 42);
    shm.close();
    shm.unlink();
}

};  // namespace

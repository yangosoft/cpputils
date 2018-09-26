#include <gtest/gtest.h>

#include <memallocatortracer/memallocatortracer.h>

int main(int argc, char **argv)
{

    ::testing::InitGoogleTest(&argc, argv);
    int ret = RUN_ALL_TESTS();

    return ret;
}

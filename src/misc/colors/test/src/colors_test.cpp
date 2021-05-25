
#include <iostream>
#include <gtest/gtest.h>

#include <misc/colors.h>



namespace
{


TEST(ColorTest, ColorTest)
{
        CppUtils::Misc::Pixel p1{255,255,255,0};
        CppUtils::Misc::Pixel p2{254,255,255,0};

        auto q1 = CppUtils::Misc::Lab2Rgb(p1);
        auto q2 = CppUtils::Misc::Lab2Rgb(p2);
        
        auto d = CppUtils::Misc::DeltaE(q1,q2);
        const double c = 0.50632069428467019;
        EXPECT_DOUBLE_EQ(d,c);
}

};

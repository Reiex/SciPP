#include "main.hpp"

TEST(MiscellaneousFunctions, Func_expoSq)
{
    EXPECT_EQ(expoSq(2, 10), 1024);
    EXPECT_EQ(expoSq(-2, 9), -512);
    EXPECT_EQ(expoSq(0, 10), 0);
    EXPECT_EQ(expoSq(2, 0), 1);
    EXPECT_EQ(expoSq(-2, 0), 1);
    EXPECT_EQ(expoSq(0, 0), 1);
    EXPECT_THROW(expoSq(2, -1), std::runtime_error);

    EXPECT_FLOAT_EQ(expoSq(2.5f, 3), 15.625);
}

TEST(MiscellaneousFunctions, Func_gcd)
{
    EXPECT_EQ(gcd(96, 128), 32);
    EXPECT_EQ(gcd(-96, 128), 32);
    EXPECT_EQ(gcd(96, -128), 32);
    EXPECT_EQ(gcd(-96, -128), 32);

    EXPECT_EQ(gcd(97, 101), 1);
    EXPECT_EQ(gcd(0, 101), 1);
}

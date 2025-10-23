#include <factorial.h>
#include <gtest/gtest.h>
#include <stdexcept>

TEST(FactorialTest, BasicValues)
{
    auto result = generateFactorials(5);
    std::vector<long long> expected = { 1, 2, 6, 24, 120 };
    EXPECT_EQ(result, expected);
}

TEST(FactorialTest, ThrowsOnZero)
{
    EXPECT_THROW(generateFactorials(0), std::invalid_argument);
}

TEST(FactorialTest, OverflowDetection)
{
    EXPECT_THROW(generateFactorials(25), std::overflow_error);
}

TEST(FactorialTest, LargeButValid)
{
    auto result = generateFactorials(20);
    EXPECT_EQ(result.back(), 2432902008176640000);
}
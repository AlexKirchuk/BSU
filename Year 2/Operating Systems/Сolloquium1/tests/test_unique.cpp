#include <unique.h>
#include <gtest/gtest.h>
#include <vector>

TEST(RemoveDuplicatesTest, BasicTest)
{
    std::vector<int> input = { 1, 2, 2, 3, 4, 4, 5 };
    std::vector<int> expected = { 1, 2, 3, 4, 5 };
    EXPECT_EQ(removeDuplicates(input), expected);
}

TEST(RemoveDuplicatesTest, EmptyInput)
{
    std::vector<int> input;
    std::vector<int> expected;
    EXPECT_EQ(removeDuplicates(input), expected);
}

TEST(RemoveDuplicatesTest, AllDuplicates)
{
    std::vector<int> input = { 7, 7, 7, 7 };
    std::vector<int> expected = { 7 };
    EXPECT_EQ(removeDuplicates(input), expected);
}
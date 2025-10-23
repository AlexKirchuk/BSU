#include <linked_list.h>
#include <gtest/gtest.h>
#include <vector>

std::vector<int> listToVector(const std::shared_ptr<Node>& head)
{
    std::vector<int> result;
    auto current = head;
    while (current)
    {
        result.push_back(current->value);
        current = current->next;
    }
    return result;
}

TEST(ReverseListTest, BasicTest)
{
    auto n1 = std::make_shared<Node>(1);
    auto n2 = std::make_shared<Node>(2);
    auto n3 = std::make_shared<Node>(3);
    n1->next = n2;
    n2->next = n3;

    auto reversed = reverseList(n1);
    std::vector<int> expected = { 3, 2, 1 };
    EXPECT_EQ(listToVector(reversed), expected);
}

TEST(ReverseListTest, SingleElement)
{
    auto n1 = std::make_shared<Node>(10);
    auto reversed = reverseList(n1);
    std::vector<int> expected = { 10 };
    EXPECT_EQ(listToVector(reversed), expected);
}

TEST(ReverseListTest, EmptyList)
{
    std::shared_ptr<Node> head = nullptr;
    auto reversed = reverseList(head);
    EXPECT_EQ(reversed, nullptr);
}
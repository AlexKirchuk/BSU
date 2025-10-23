#ifndef LINKED_LIST_H
#define LINKED_LIST_H
#include <memory>

struct Node
{
    int value;
    std::shared_ptr<Node> next;

    Node(int v);
};

std::shared_ptr<Node> reverseList(const std::shared_ptr<Node>& head);

#endif
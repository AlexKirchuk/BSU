#include <linked_list.h>

Node::Node(int v) : value(v), next(nullptr) {}

std::shared_ptr<Node> reverseList(const std::shared_ptr<Node>& head)
{
    if (!head) return nullptr;
    if (!head->next) return head;

    auto new_head = reverseList(head->next);
    head->next->next = head;
    head->next = nullptr;
    return new_head;
}
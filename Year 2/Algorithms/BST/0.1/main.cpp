#include <iostream>
#include <fstream>
#include <memory>

struct Node
{
    int key;
    std::shared_ptr<Node> left;
    std::shared_ptr<Node> right;
    Node(int k) : key(k) {}
};

void insert(std::shared_ptr<Node>& root, int key)
{
    if (!root)
    {
        root = std::make_shared<Node>(key);
        return;
    }
    if (key < root->key)
        insert(root->left, key);
    else if (key > root->key)
        insert(root->right, key);
}

void preorder(const std::shared_ptr<Node>& root, std::ofstream& out)
{
    if (root)
    {
        out << root->key << std::endl;
        preorder(root->left, out);
        preorder(root->right, out);
    }
}

int main()
{
    std::ifstream in("input.txt");
    std::ofstream out("output.txt");

    std::shared_ptr<Node> root = nullptr;
    int key;

    while (in >> key)
        insert(root, key);

    preorder(root, out);

    return 0;
}
#include <iostream>
#include <string>
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

std::shared_ptr<Node> findMin(std::shared_ptr<Node> node)
{
    while (node->left)
        node = node->left;
    return node;
}

std::shared_ptr<Node> remove(std::shared_ptr<Node> root, int key)
{
    if (!root) return nullptr;

    if (key < root->key)
        root->left = remove(root->left, key);
    else if (key > root->key)
        root->right = remove(root->right, key);
    else
    {
        if (!root->left && !root->right)
            return nullptr;
        if (!root->left)
            return root->right;
        else if (!root->right)
            return root->left;
        else
        {
            std::shared_ptr<Node> minNode = findMin(root->right);
            root->key = minNode->key;
            root->right = remove(root->right, minNode->key);
        }
    }
    return root;
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

    std::string str;
    std::shared_ptr<Node> root = nullptr;
    int key, el;

    in >> el;

    std::getline(in, str);

    while (in >> key)
        insert(root, key);

    root = remove(root, el);

    preorder(root, out);

    return 0;
}
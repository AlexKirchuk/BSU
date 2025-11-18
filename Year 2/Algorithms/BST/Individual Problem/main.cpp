#include <iostream>
#include <string>
#include <fstream>
#include <memory>

int myMax(const int& a, const int& b)
{
    return (a > b) ? a : b;
}

struct Node
{
    static int mslT, rootKey;
    int key, h, l, msl, b, a, c;
    std::shared_ptr<Node> left;
    std::shared_ptr<Node> right;
    Node(int k) : key(k), h(0), l(0), msl(0), b(0), a(0), c(0) {}
};

int getRootKey(std::shared_ptr<Node> root)
{
    return root->key;
}

int Node::mslT = 0;
int Node::rootKey = 0;

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

void postorder(const std::shared_ptr<Node>& root)
{
    if (root)
    {
        postorder(root->left);
        postorder(root->right);
        if (!root->left && !root->right)
        {
            root->h = 0;
            root->l = 1;
            root->msl = 0;
            if (root->msl > Node::mslT)
                Node::mslT = root->msl;
        }
        else if (!root->left && root->right)
        {
            root->h = root->right->h + 1;
            root->l = root->right->l;
            root->msl = root->right->h + 1;
            if (root->msl > Node::mslT)
                Node::mslT = root->msl;
        }
        else if (root->left && !root->right)
        {
            root->h = root->left->h + 1;
            root->l = root->left->l;
            root->msl = root->left->h + 1;
            if (root->msl > Node::mslT)
                Node::mslT = root->msl;
        }
        else
        {
            root->h = myMax(root->left->h, root->right->h) + 1;
            if (root->left->h == root->right->h)
                root->l = root->left->l + root->right->l;
            else if (root->left->h > root->right->h)
                root->l = root->left->l;
            else
                root->l = root->right->l;
            root->msl = root->left->h + root->right->h + 2;
            if (root->msl > Node::mslT)
                Node::mslT = root->msl;
        }
    }
}

void preorderb(const std::shared_ptr<Node>& root)
{
    if (root)
    {
        if (root->msl == Node::mslT)
        {
            if (!root->left && !root->right)
                root->b = 1;
            else if (!root->left && root->right)
                root->b = root->right->l;
            else if (root->left && !root->right)
                root->b = root->left->l;
            else
                root->b = root->left->l * root->right->l;
        }
        else
            root->b = 0;
        preorderb(root->left);
        preorderb(root->right);
    }
}

void preorderfinal(const std::shared_ptr<Node>& root)
{
    if (root)
    {
        if (root->key == Node::rootKey)
        {
            root->a = 0;
            root->c = root->b;
        }
        if (!root->left && root->right)
        {
            root->right->a = root->a + root->b;
            root->right->c = root->right->a + root->right->b;
        }
        else if (root->left && !root->right)
        {
            root->left->a = root->a + root->b;
            root->left->c = root->left->a + root->left->b;
        }
        else if (root->left && root->right)
        {
            if (root->left->h > root->right->h)
            {
                root->left->a = root->a + root->b;
                root->right->a = root->b;
            }
            else if (root->left->h < root->right->h)
            {
                root->right->a = root->a + root->b;
                root->left->a = root->b;
            }
            else
            {
                root->right->a = root->right->l * (root->a / root->l) + root->b;
                root->left->a = root->left->l * (root->a / root->l) + root->b;
            }
            root->right->c = root->right->a + root->right->b;
            root->left->c = root->left->a + root->left->b;
        }
        preorderfinal(root->left);
        preorderfinal(root->right);
    }
}

void preorderout(const std::shared_ptr<Node>& root, std::ofstream& out)
{
    if (root)
    {
        out << root->key << " " << root->c << std::endl;
        preorderout(root->left, out);
        preorderout(root->right, out);
    }
}

int main()
{
    std::ifstream in("input.txt");
    std::ofstream out("output.txt");

    std::shared_ptr<Node> root = nullptr;
    int fst, key;

    in >> fst;
    insert(root, fst);

    while (in >> key)
        insert(root, key);

    root = remove(root, fst);
    root->rootKey = getRootKey(root);

    postorder(root);
    preorderb(root);
    preorderfinal(root);
    preorderout(root, out);

    return 0;
}
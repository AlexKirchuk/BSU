#include <fstream>
#include <vector>
#include <memory>

struct Node
{
    std::shared_ptr<Node> parent;
    int size;

    Node() : parent(nullptr), size(1) {}
};

struct DSU
{
    std::vector<std::shared_ptr<Node>> nodes;

    DSU(int n)
    {
        nodes.resize(n + 1);
        for (int i = 1; i <= n; ++i)
        {
            nodes[i] = std::make_shared<Node>();
            nodes[i]->parent = nodes[i];
        }
    }

    std::shared_ptr<Node> findSet(std::shared_ptr<Node> v)
    {
        if (v->parent == v)
        {
            return v;
        }
        v->parent = findSet(v->parent);
        return v->parent;
    }

    bool unionSets(int a, int b)
    {
        auto A = findSet(nodes[a]);
        auto B = findSet(nodes[b]);
        if (A == B)
        {
            return false;
        }
        if (A->size < B->size)
        {
            std::swap(A, B);
        }
        B->parent = A;
        A->size += B->size;
        return true;
    }
};

int main()
{
    std::ifstream in("input.txt");
    std::ofstream out("output.txt");

    int n, q;
    in >> n >> q;

    DSU dsu(n);
    int components = n;

    for (int i = 0; i < q; ++i)
    {
        int u, v;
        in >> u >> v;
        if (dsu.unionSets(u, v))
        {
            components--;
        }
        out << components << '\n';
    }

    return 0;
}
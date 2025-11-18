#include <fstream>
#include <string>
#include <vector>
#include <tuple>
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

    int n, m, q;
    in >> n >> m >> q;

    DSU dsu(n);
    int count = n;
    std::vector<int> components;

    std::vector<std::pair<int, int>> roads(m);
    std::vector<int> earthquakes(q);

    for (int i = 0; i < m; i++)
    {
        int fst, snd;
        in >> fst >> snd;
        std::pair<int, int> tmp(fst, snd);
        roads[i] = tmp;
    }

    for (int i = 0; i < q; i++)
    {
        int tmp;
        in >> tmp;
        earthquakes[i] = tmp;
    }

    std::string str;

    std::vector<bool> destroyed(m + 1, false);
    for (int x : earthquakes)
    {
        destroyed[x] = true;
    }

    for (int i = 1; i <= m; ++i)
    {
        if (!destroyed[i])
        {
            if (dsu.unionSets(roads[i - 1].first, roads[i - 1].second))
            {
                count--;
            }
        }
    }

    for (int i = q - 1; i >= 0; --i)
    {
        components.push_back(count);
        if (dsu.unionSets(roads[earthquakes[i] - 1].first, roads[earthquakes[i] - 1].second))
        {
            count--;
        }
    }

    for (int i = components.size() - 1; i >= 0; i--)
    {
        if (components[i] == 1)
        {
            str += "1";
        }
        else
        {
            str += "0";
        }
    }

    out << str;
    return 0;
}
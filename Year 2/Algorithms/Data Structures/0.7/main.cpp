/*
¬ Ѕерл€ндии n городов, св€занных m дорогами.
√арантируетс€, что изначально граф из городов св€зный,
т.е. существует путь между любой парой вершин.
¬ Ѕерл€ндии происходит q землетр€сений,
в ходе каждого из них разрушаетс€ ровно одна дорога.
Ќеобходимо после каждого землетр€сени€ узнать,
€вл€етс€ ли полученный граф из городов св€зным.
ѕосле очередного землетр€сений дорога не перестраиваетс€,
то есть разрушаетс€ навсегда.

Input
ѕерва€ строка входного файла содержит три числа n, m, q
(1 <= n, m, q <= 750000) - количество городов,
дорог и землетр€сений в Ѕерл€ндии соответственно.
—ледующие m строк содержат по два натуральных числа u и v
(1 <= u, v <= n) - номера городов, св€занных дорогой.
√арантируетс€, что u != v и между каждой парой городов
существует не больше одной дороги.
—ледующие q строк содержат по одному числу x_i (1 <= x_i <= m) -
номер дороги, котора€ пострадает во врем€ i-ого землетр€сени€.
√арантируетс€, что два различных землетр€сени€ не разрушают
одну и ту же дорогу.

Output
¬ыведите строку длины q из нулей и единиц.
i-ый символ равен 1, если после i-ого землетр€сени€ граф
оказалс€ св€зным, в противном случае выведите 0.
*/

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
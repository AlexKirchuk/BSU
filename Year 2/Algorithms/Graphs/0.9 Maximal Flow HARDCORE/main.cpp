#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>

using LL = long long;

struct Edge
{
    LL to, cap, rev;
};

const LL INF = 1e18;

std::vector<std::vector<Edge>> g;
std::vector<LL> level;
std::vector<LL> ptr;

void add_edge(LL v, LL u, LL cap)
{
    Edge a = { u, cap, g[u].size() };
    Edge b = { v, 0, g[v].size() };
    g[v].push_back(a);
    g[u].push_back(b);
}

bool bfs(LL s, LL t)
{
    std::fill(level.begin(), level.end(), -1);

    std::queue<LL> q;
    level[s] = 0;
    q.push(s);

    while (!q.empty())
    {
        LL v = q.front();
        q.pop();

        for (auto& e : g[v])
        {
            if (e.cap > 0 && level[e.to] == -1)
            {
                level[e.to] = level[v] + 1;
                q.push(e.to);
            }
        }
    }

    return level[t] != -1;
}

LL dfs(LL v, LL t, LL pushed)
{
    if (v == t || pushed == 0)
    {
        return pushed;
    }

    for (LL& cid = ptr[v]; cid < g[v].size(); cid++)
    {
        Edge& e = g[v][cid];

        if (e.cap > 0 && level[e.to] == level[v] + 1)
        {
            LL tr = dfs(e.to, t, std::min(pushed, e.cap));
            if (tr == 0)
            {
                continue;
            }

            e.cap -= tr;
            g[e.to][e.rev].cap += tr;
            return tr;
        }
    }

    return 0;
}

LL dinic(LL s, LL t)
{
    LL flow = 0;

    while (bfs(s, t))
    {
        fill(ptr.begin(), ptr.end(), 0);
        while (long long pushed = dfs(s, t, INF))
        {
            flow += pushed;
        }
    }

    return flow;
}

int main()
{
    LL n, m;
    std::cin >> n >> m;

    g.assign(n + 1, std::vector<Edge>());
    level.resize(n + 1);
    ptr.resize(n + 1);

    for (LL i = 0; i < m; i++)
    {
        LL u, v, w;
        std::cin >> u >> v >> w;
        add_edge(u, v, w);
    }

    std::cout << dinic(1, n);

    return 0;
}
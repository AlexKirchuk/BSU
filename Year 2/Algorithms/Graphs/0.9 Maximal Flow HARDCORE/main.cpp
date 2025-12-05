#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using LL = long long;

struct Edge
{
    int to;
    LL cap;
    int rev;
};

const LL INF = 1e18;

std::vector<std::vector<Edge>> g;
std::vector<int> level;
std::vector<int> ptr;

void add_edge(int v, int u, LL cap)
{
    Edge a = { u, cap, (int)g[u].size() };
    Edge b = { v, 0, (int)g[v].size() };
    g[v].push_back(a);
    g[u].push_back(b);
}

bool bfs(int s, int t)
{
    std::fill(level.begin(), level.end(), -1);

    std::queue<int> q;
    level[s] = 0;
    q.push(s);

    while (!q.empty())
    {
        int v = q.front();
        q.pop();

        for (auto& e : g[v])
        {
            if (e.cap > 0 && level[e.to] == -1)
            {
                level[e.to] = level[v] + 1;
                q.push(e.to);

                if (e.to == t)
                {
                    return true;
                }
            }
        }
    }

    return level[t] != -1;
}

LL dfs(int v, int t, LL pushed)
{
    if (v == t)
    {
        return pushed;
    }

    for (int& cid = ptr[v]; cid < (int)g[v].size(); cid++)
    {
        Edge& e = g[v][cid];

        if (e.cap > 0 && level[e.to] == level[v] + 1)
        {
            LL tr;

            if (pushed == INF)
            {
                tr = dfs(e.to, t, e.cap);
            }
            else
            {
                tr = dfs(e.to, t, (pushed < e.cap ? pushed : e.cap));
            }

            if (tr == 0)
            {
                continue;
            }

            e.cap -= tr;
            g[e.to][e.rev].cap += tr;

            return tr;
        }
    }

    level[v] = -1;
    return 0;
}

LL dinic(int s, int t)
{
    LL flow = 0;

    while (bfs(s, t))
    {
        std::fill(ptr.begin(), ptr.end(), 0);

        while (true)
        {
            LL pushed = dfs(s, t, INF);
            if (pushed == 0)
            {
                break;
            }
            flow += pushed;
        }
    }

    return flow;
}

int main()
{
    int n, m;
    std::cin >> n >> m;

    g.assign(n + 1, std::vector<Edge>());
    level.resize(n + 1);
    ptr.resize(n + 1);

    for (int i = 1; i <= n; i++)
    {
        g[i].reserve((m / n) + 2);
    }

    for (int i = 0; i < m; i++)
    {
        int u, v;
        LL w;
        std::cin >> u >> v >> w;
        add_edge(u, v, w);
    }

    std::cout << dinic(1, n);

    return 0;
}
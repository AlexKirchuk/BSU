#include <fstream>
#include <vector>
#include <queue>
#include <algorithm>

struct edge
{
    long long u, v, w;
};

int main()
{
    std::ifstream fin("input.txt");
    std::ofstream fout("output.txt");

    using LL = long long;
    using P = std::pair<LL, LL>;

    const LL INF = 1e18;
    LL n, m;
    fin >> n >> m;

    std::vector<edge> edges(m);
    std::vector<std::vector<LL>> adjacency(n);
    std::vector<LL> dist(n, INF);
    std::vector<bool> processed(n, false);

    for (LL i = 0; i < m; i++)
    {
        fin >> edges[i].u >> edges[i].v >> edges[i].w;

        LL a = edges[i].u - 1;
        LL b = edges[i].v - 1;

        adjacency[a].push_back(i);
        adjacency[b].push_back(i);
    }

    std::priority_queue<P, std::vector<P>, std::greater<P>> pq;

    dist[0] = 0;
    pq.push(P(0, 0));

    while (!pq.empty())
    {
        P top = pq.top();
        pq.pop();

        LL dv = top.first;
        LL v = top.second;

        if (processed[v]) { continue; }
        processed[v] = true;
        dist[v] = dv; // unnecessary

        LL cnt = adjacency[v].size();

        for (LL i = 0; i < cnt; i++)
        {
            LL edge_id = adjacency[v][i];

            LL u = edges[edge_id].u - 1;
            LL w = edges[edge_id].w;

            if (u == v)
            {
                u = edges[edge_id].v - 1;
            }
            else
            {
                w = edges[edge_id].w;
            }

            if (!processed[u] && dv + w < dist[u])
            {
                dist[u] = dv + w;
                pq.push(P(dist[u], u));
            }
        }
    }

    fout << dist[n - 1];

    fin.close();
    fout.close();
    return 0;
}
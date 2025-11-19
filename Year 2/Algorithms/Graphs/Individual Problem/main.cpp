#include <fstream>
#include <iomanip>
#include <vector>
#include <queue>
#include <algorithm>

using LL = long long;
using P = std::pair<LL, LL>;

LL gcdll(LL a, LL b)
{
    while (b)
    {
        LL t = a % b;
        a = b;
        b = t;
    }
    return a;
}

LL lcmll(LL a, LL b)
{
    return a / gcdll(a, b) * b;
}

LL nextActivation(LL cur, LL L)
{
    if (cur <= L)
    {
        return L;
    }

    LL k = (cur - 1) / L;
    return L + k * L;
}

struct Edge
{
    LL to, L, idx;
};

int main()
{
    std::ifstream fin("input.txt");
    std::ofstream fout("output.txt");

    LL N, M;
    fin >> N >> M;

    std::vector<std::vector<Edge>> g(N + 1);
    g.reserve(N + 1);

    for (LL i = 1; i <= M; i++)
    {
        LL r1, t1, r2, t2;
        fin >> r1 >> t1 >> r2 >> t2;

        LL T1 = t1 * 2;
        LL T2 = t2 * 2;

        LL L = lcmll(T1, T2);

        g[r1].push_back({ r2, L, i });
        g[r2].push_back({ r1, L, i });
    }

    const LL INF = 1e18;
    std::vector<LL> dist(N + 1, INF);
    std::vector<LL> parentNode(N + 1, -1);
    std::vector<LL> parentEdge(N + 1, -1);

    std::priority_queue<P, std::vector<P>, std::greater<P>> pq;

    dist[1] = 0;
    pq.push({ 0, 1 });

    while (!pq.empty())
    {
        auto top = pq.top();
        LL cur = top.first;
        LL v = top.second;
        pq.pop();

        if (cur != dist[v])
        {
            continue;
        }
        if (v == N)
        {
            break;
        }

        for (auto& e : g[v])
        {
            LL L = e.L;

            LL arrival = nextActivation(cur, L) + 1;

            if (arrival < dist[e.to])
            {
                dist[e.to] = arrival;
                parentNode[e.to] = v;
                parentEdge[e.to] = e.idx;
                pq.push({ arrival, e.to });
            }
        }
    }

    double result = dist[N] / 2.0;
    fout.setf(std::ios::fixed);
    fout << std::setprecision(1) << result << "\n";

    std::vector<LL> path;
    LL x = N;

    while (x != 1)
    {
        path.push_back(parentEdge[x]);
        x = parentNode[x];
    }

    std::reverse(path.begin(), path.end());

    for (LL i = 0; i < path.size(); i++)
    {
        if (i)
        {
            fout << " ";
        }
        fout << path[i];
    }

    return 0;
}
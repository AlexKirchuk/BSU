#include <fstream>
#include <vector>

int myMin(int a, int b)
{
    return a < b ? a : b;
}

int main()
{
    std::ifstream fin("input.txt");
    std::ofstream fout("output.txt");

    const int INF = 1e9;
    int n;
    fin >> n;

    std::vector<std::pair<int, int>> a(n + 1);
    for (int i = 1; i <= n; ++i)
        fin >> a[i].first >> a[i].second;

    std::vector<int> dpL(n + 2, INF), dpR(n + 2, INF),
        newL(n + 2, INF), newR(n + 2, INF);
    // Rolling Array Optimization M(n^2) => M(n)

    for (int i = 1; i <= n; ++i)
        dpL[i] = dpR[i] = 0;

    // Algorithm O(n^2)
    for (int len = 2; len <= n; ++len)
    {
        for (int i = 1; i + len - 1 <= n; ++i)
        {
            int j = i + len - 1;
            int bestL = INF, bestR = INF;

            int di = a[i].first, dj = a[j].first;
            int ti = a[i].second, tj = a[j].second;

            if (dpL[i + 1] < INF)
            {
                int arrive = dpL[i + 1] + (a[i + 1].first - di);
                if (arrive <= ti) bestL = myMin(bestL, arrive);
            }

            if (dpR[i + 1] < INF)
            {
                int arrive = dpR[i + 1] + (dj - di);
                if (arrive <= ti) bestL = myMin(bestL, arrive);
            }

            if (dpL[i] < INF)
            {
                int arrive = dpL[i] + (dj - di);
                if (arrive <= tj) bestR = myMin(bestR, arrive);
            }

            if (dpR[i] < INF)
            {
                int arrive = dpR[i] + (dj - a[j - 1].first);
                if (arrive <= tj) bestR = myMin(bestR, arrive);
            }

            newL[i] = bestL;
            newR[i] = bestR;
        }

        dpL.swap(newL);
        dpR.swap(newR);
    }

    int ans = myMin(dpL[1], dpR[1]);
    if (ans >= INF) fout << "No solution" << std::endl;
    else fout << ans << std::endl;

    return 0;
}
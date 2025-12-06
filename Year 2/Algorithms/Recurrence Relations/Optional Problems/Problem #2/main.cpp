#include <fstream>
#include <vector>
#include <algorithm>

int main()
{
    std::ifstream fin("in.txt");
    std::ofstream fout("out.txt");

    long long m, n;
    fin >> m >> n;

    if (m > n)
    {
        std::swap(m, n);
    }

    long long S = static_cast<long long>(1 << m);
    std::vector<std::vector<bool> > ok(S, std::vector<bool>(S, 1));

    for (long long a = 0; a < S; ++a)
    {
        for (long long b = 0; b < S; ++b)
        {
            bool good = true;
            for (long long i = 0; i + 1 < m; ++i)
            {
                long long a0 = (a >> i) & 1;
                long long a1 = (a >> (i + 1)) & 1;
                long long b0 = (b >> i) & 1;
                long long b1 = (b >> (i + 1)) & 1;
                if (a0 == a1 && a1 == b0 && b0 == b1)
                {
                    good = false;
                    break;
                }
            }
            ok[a][b] = good ? 1 : 0;
        }
    }

    std::vector<long long> dp(S);
    for (long long mask = 0; mask < S; ++mask)
    {
        dp[mask] = 1;
    }

    for (long long col = 1; col < n; ++col)
    {
        std::vector<long long> ndp(S);
        for (long long a = 0; a < S; ++a)
        {
            if (dp[a] == 0)
            {
                continue;
            }
            for (long long b = 0; b < S; ++b)
            {
                if (ok[a][b])
                {
                    ndp[b] += dp[a];
                }
            }
        }
        dp.swap(ndp);
    }

    long long ans = 0;
    for (long long mask = 0; mask < S; ++mask)
    {
        ans += dp[mask];
    }

    fout << ans;
    return 0;
}
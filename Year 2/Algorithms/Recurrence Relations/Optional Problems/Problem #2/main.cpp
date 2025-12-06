#include <fstream>
#include <vector>
#include <algorithm>
#include <iomanip>

class BigInt
{
private:
    static const int BASE = 1000000000;
    std::vector<int> d;

public:
    BigInt()
    {
        d.push_back(0);
    }

    BigInt(long long x)
    {
        if (x == 0)
        {
            d.push_back(0);
            return;
        }
        while (x > 0)
        {
            d.push_back(x % BASE);
            x /= BASE;
        }
    }

    void trim()
    {
        while (d.size() > 1 && d.back() == 0)
        {
            d.pop_back();
        }
    }

    BigInt& operator+=(const BigInt& other)
    {
        int n = d.size();
        int m = other.d.size();
        int L = std::max(n, m);

        d.resize(L, 0);

        long long carry = 0;

        for (int i = 0; i < L; ++i)
        {
            long long sum = d[i] + carry;
            if (i < m)
            {
                sum += other.d[i];
            }
            d[i] = sum % BASE;
            carry = sum / BASE;
        }

        if (carry > 0)
        {
            d.push_back(carry);
        }

        return *this;
    }

    friend std::ostream& operator<<(std::ostream& out, const BigInt& v)
    {
        int n = v.d.size();
        out << v.d[n - 1];

        for (int i = n - 2; i >= 0; --i)
        {
            out << std::setw(9) << std::setfill('0') << v.d[i];
        }

        return out;
    }
};

int main()
{
    std::ifstream fin("in.txt");
    std::ofstream fout("out.txt");

    int m, n;
    fin >> m >> n;

    if (m > n)
    {
        std::swap(m, n);
    }

    int S = (1 << m);

    std::vector<std::vector<bool> > ok(S, std::vector<bool>(S, true));

    for (int a = 0; a < S; ++a)
    {
        for (int b = 0; b < S; ++b)
        {
            bool good = true;

            for (int i = 0; i + 1 < m; ++i)
            {
                int a0 = (a >> i) & 1;
                int a1 = (a >> (i + 1)) & 1;
                int b0 = (b >> i) & 1;
                int b1 = (b >> (i + 1)) & 1;

                if (a0 == a1 && a1 == b0 && b0 == b1)
                {
                    good = false;
                    break;
                }
            }

            ok[a][b] = good;
        }
    }

    std::vector<BigInt> dp(S);
    for (int mask = 0; mask < S; ++mask)
    {
        dp[mask] = BigInt(1);
    }

    for (int col = 1; col < n; ++col)
    {
        std::vector<BigInt> ndp(S);

        for (int a = 0; a < S; ++a)
        {
            for (int b = 0; b < S; ++b)
            {
                if (ok[a][b])
                {
                    ndp[b] += dp[a];
                }
            }
        }

        dp.swap(ndp);
    }

    BigInt ans(0);
    for (int mask = 0; mask < S; ++mask)
    {
        ans += dp[mask];
    }

    fout << ans;

    return 0;
}
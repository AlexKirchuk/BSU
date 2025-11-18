#include <iostream>
#include <vector>

const long long MOD = 1000000007;

long long myBinaryPow(long long a, long long p)
{
    long long res = 1;
    while (p > 0)
    {
        if (p & 1) res = (res * a) % MOD;
        a = (a * a) % MOD;
        p >>= 1;
    }
    return res;
}

int main()
{
    long long n, k;
    std::cin >> n >> k;

    std::vector<long long> fact(n + 1), invfact(n + 1);
    fact[0] = 1;
    for (int i = 1; i <= n; i++) fact[i] = (fact[i - 1] * i) % MOD;

    invfact[n] = myBinaryPow(fact[n], MOD - 2);
    for (int i = n - 1; i >= 0; i--) invfact[i] = (invfact[i + 1] * (i + 1)) % MOD;

    long long res = fact[n];
    res = (res * invfact[k]) % MOD;
    res = (res * invfact[n - k]) % MOD;

    std::cout << res << std::endl;
    return 0;
}
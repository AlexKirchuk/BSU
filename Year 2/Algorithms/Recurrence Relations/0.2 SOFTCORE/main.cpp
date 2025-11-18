#include <iostream>
#include <vector>

std::vector <std::vector<long long>> b;
const long long MOD = 1000000007;

long long comb(long long n, long long k)
{
	if (k == 0 || k == n) return 1;
	if (b[n][k] == -1)
		b[n][k] = (comb(n - 1, k - 1) + comb(n - 1, k)) % MOD;
	return b[n][k];
}

int main()
{
	long long n, k;
	std::cin >> n >> k;

	b.assign(n + 1, std::vector<long long>(k + 1, -1));

	std::cout << comb(n, k);
	return 0;
}
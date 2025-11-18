#include <iostream>
#include <vector>

long long myMax(long long a, long long b)
{
	return a > b ? a : b;
}

int main()
{
	long long n;
	std::cin >> n;

	std::vector<long long> a(n), b(n), pathA, pathB;

	for (long long i = 0; i < n; i++)
	{
		std::cin >> a[i];
	}
	for (long long i = 0; i < n; i++)
	{
		std::cin >> b[i];
	}

	std::vector<std::vector<long long>> c(n + 1, std::vector<long long>(n + 1, 0));

	for (long long i = 0; i < n; i++)
	{
		for (long long j = 0; j < n; j++)
		{
			if (a[i] == b[j])
			{
				c[i + 1][j + 1] = c[i][j] + 1;
			}
			else
			{
				c[i + 1][j + 1] = myMax(c[i][j + 1], c[i + 1][j]);
			}
		}
	}

	for (long long i = n - 1, j = n - 1; i > -1 || j > -1; )
	{
		if (c[i + 1][j + 1] == 0)
		{
			i = -1;
			j = -1;
			break;
		}
		if (a[i] == b[j])
		{
			pathA.push_back(i);
			pathB.push_back(j);
			i--;
			j--;
		}
		else if (c[i + 1][j + 1] == c[i][j + 1])
		{
			i--;
		}
		else if (c[i + 1][j + 1] == c[i + 1][j])
		{
			j--;
		}
	}

	std::cout << c[n][n] << std::endl;
	for (long long i = pathA.size() - 1; i >= 0; i--)
	{
		std::cout << pathA[i] << " ";
	}
	std::cout << std::endl;
	for (long long i = pathB.size() - 1; i >= 0; i--)
	{
		std::cout << pathB[i] << " ";
	}
	return 0;
}
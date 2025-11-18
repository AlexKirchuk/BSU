#include <fstream>
#include <vector>
#include <climits>

long long myMin(long long a, long long b)
{
	return a < b ? a : b;
}

int main()
{
	std::ifstream fin;
	std::ofstream fout;

	fin.open("input.txt");
	fout.open("output.txt");

	long long n;
	fin >> n;

	std::vector<long long> dim(n + 1);

	long long rows, cols;
	for (long long i = 0; i < n; i++)
	{
		fin >> rows >> cols;
		if (i == 0) dim[i] = rows;
		dim[i + 1] = cols;
	}

	std::vector<std::vector<long long>> b(n + 1, std::vector<long long>(n + 1, 0));
	long long j, cost;
	for (long long l = 2; l <= n; l++)
	{
		for (long long i = 1; i <= n - l + 1; i++)
		{
			j = i + l - 1;
			b[i][j] = LLONG_MAX;
			for (long long k = i; k < j; k++)
			{
				cost = b[i][k] + b[k + 1][j] + dim[i - 1] * dim[k] * dim[j];
				b[i][j] = myMin(b[i][j], cost);
			}
		}
	}

	fout << b[1][n];
	return 0;
}
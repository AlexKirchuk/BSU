/*
Даны две последовательности A и B, каждая имеет длину n.
Найти наибольшее k, для которого существуют
две последовательности индексов 0 <= i_1 < i_2 < ... < i_k < n
и 0 <= j_1 < j_2 < ... < j_k < n,
что A_{i_1} = B_{j_1}, A_{i_2} = B_{j_2}, …, A_{i_k} = B_{j_k}.
Также нужно найти и сами последовательности индексов.

Input
В первой строке записано число n (1 <= n <= 1000),
длина последовательностей A и B.
Во второй строке содержится n целых чисел a_i (1 <= a_i <= 1000)
— элементы последовательности A.
В третьей строке содержатся n целых чисел b_j (1 <= a_i <= 1000)
— элементы последовательности B.

Output
В первой строке выведите число k.
Во второй строке выведите индексы i_{1}\, i_{2}\, ..., i_k.
В третьей строке выведите индексы j_{1}\, j_{2}\, ..., j_k.
Если подходящий последовательностей индексов несколько,
выведите любые из них.
*/

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

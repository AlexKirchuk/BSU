/*
Дано число N. Необходимо определить,
сколько есть бинарных строк длины N,
в которых ровно K единиц.

Input
Первая строка входных данных содержит
два целых неотрицательных числа N
и K (0 <= K <= N <= 1000).
Output

Выведите одно число - ответ на задачу.
Так как ответ может быть очень большим,
необходимо его вывести по модулю 10^9 + 7.
*/

#include <iostream>
long long comb(long long n, long long k)
{
	if (n == k)
	{
		return 1;
	}
	if (k == 0)
	{
		return 1;
	}
	return comb(n - 1, k - 1) + comb(n - 1, k);
}

int main()
{
	long long N, K;
	std::cin >> N >> K;
	std::cout << comb(N, K);
	return 0;
}
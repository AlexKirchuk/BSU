/*
Рассмотрим следующую модельную задачу.
Изначально дана последовательность чисел A длины n (индексация с нуля):
a_0, a_1, a_2, ..., a_{n-1}.
Поступают запросы двух типов.
Запрос модификации. Задан индекс i и число x.
Нужно прибавить к i-му элементу число x.
Запрос суммы. Задана пара индексов l и r.
Нужно вычислить сумму элементов на полуинтервале [l, r),
т. е. a_l + a_{l+1} + ... + a_{r - 1}, и вернуть результат.

Input
В первой строке записано целое число n — количество элементов массива (1 <= n <= 300000).
Во второй строке записаны n целых чисел a_i (-10^9 <= a_i <= 10^9).
В третьей строке записано целое число q — количество запросов (1 <= q <= 300000).
Каждая из следующих q строк задаёт один запрос.
Если это запрос модификации, то в строке записано слово Add,
затем индекс i (0 <= i < n) и число x (-10^9 <= x <= 10^9).
Если это запрос суммы, то он задаётся словом FindSum и двумя индексами l и r
(0 <= l < r <= n) — границами полуинтервала.

Output
Для каждого запроса второго типа выведите в отдельной строке
сумму элементов на соответствующем полуинтервале.
*/

#include <iostream>
#include <string>
#include <vector>

void Build(const std::vector<long long>& a, std::vector<long long>& t, int v = 1, int tl = 0, int tr = -1)
{
    if (tr == -1)
    {
        tr = a.size();
    }
    if (tr - tl == 1)
    {
        t[v] = a[tl];
    }
    else
    {
        int m = (tl + tr) / 2;
        Build(a, t, 2 * v, tl, m);
        Build(a, t, 2 * v + 1, m, tr);
        t[v] = t[2 * v] + t[2 * v + 1];
    }
}

void Add(std::vector<long long>& t, int n, int i, long long x, int v = 1, int tl = 0, int tr = -1)
{
    if (tr == -1) tr = n;
    if (tr - tl == 1)
    {
        t[v] += x;
    }
    else
    {
        int m = (tl + tr) / 2;
        if (i < m)
        {
            Add(t, n, i, x, 2 * v, tl, m);
        }
        else
        {
            Add(t, n, i, x, 2 * v + 1, m, tr);
        }
        t[v] = t[2 * v] + t[2 * v + 1];
    }
}

long long FindSum(const std::vector<long long>& t, int n, int l, int r, int v = 1, int tl = 0, int tr = -1)
{
    if (tr == -1) tr = n;
    if (l == tl && r == tr)
    {
        return t[v];
    }
    int m = (tl + tr) / 2;
    if (r <= m)
    {
        return FindSum(t, n, l, r, 2 * v, tl, m);
    }
    else if (l >= m)
    {
        return FindSum(t, n, l, r, 2 * v + 1, m, tr);
    }
    else
    {
        return FindSum(t, n, l, m, 2 * v, tl, m) + FindSum(t, n, m, r, 2 * v + 1, m, tr);
    }
}

int main()
{
    int n;
    std::cin >> n;
    std::vector<long long> a(n);
    for (int i = 0; i < n; i++)
    {
        std::cin >> a[i];
    }

    std::vector<long long> t(4 * n);
    Build(a, t);

    int q;
    std::cin >> q;
    for (int i = 0; i < q; i++)
    {
        std::string type;
        std::cin >> type;
        if (type == "Add")
        {
            int i;
            long long x;
            std::cin >> i >> x;
            Add(t, n, i, x);
        }
        else if (type == "FindSum")
        {
            int l, r;
            std::cin >> l >> r;
            std::cout << FindSum(t, n, l, r) << '\n';
        }
    }
    return 0;
}
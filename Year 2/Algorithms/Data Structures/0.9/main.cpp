/*
Имеется последовательность s0, …, sn − 1, состоящая из нулей.
На этой последовательности могут выполняться запросы следующих типов:

    1. Установить значение si равным v.
    2. Прибавить к каждому элементу с индексом из отрезка [a, b] число v.
    3. Найти сумму элементов с индексами из отрезка [a, b].
    4. Найти минимум среди элементов с индексами из отрезка [a, b].
    5. Найти максимум среди элементов с индексами из отрезка [a, b].

Требуется написать программу, которая будет обрабатывать указанные запросы.

Input
Первая строка содержит одно целое число n (1 ≤ n ≤ 300 000) — длину последовательности.
Последующие строки имеют следующий формат: первое число — тип запроса (см. условие),
далее для запроса типа 1 два числа: i, индекс элемента в массиве, и значение v;
для запроса типа 2 три числа: a, b, v;
для запросов типа 3–5 два числа: a и b.
Вход заканчивается строкой с единственным числом 0.
Число строк не превосходит 300 003.
Абсолютная величина числа v в каждом запросе не превышает 1 000 000.
Числа a, b и i в каждом запросе удовлетворяют неравенствам 0 ≤ a ≤ b < n, 0 ≤ i < n.

Output
Для каждого запроса типа 3–5 выведите ответ на запрос.
*/

#include <fstream>
#include <vector>
#include <algorithm>

const long long INF = 1e18;

int n;
std::vector<long long> a;
std::vector<long long> sum, mn, mx, add;

void push(int v, int tl, int tr)
{
    if (add[v] != 0 && tl != tr)
    {
        int tm = (tl + tr) / 2;

        sum[v * 2] += add[v] * (tm - tl + 1);
        mn[v * 2] += add[v];
        mx[v * 2] += add[v];
        add[v * 2] += add[v];

        sum[v * 2 + 1] += add[v] * (tr - tm);
        mn[v * 2 + 1] += add[v];
        mx[v * 2 + 1] += add[v];
        add[v * 2 + 1] += add[v];

        add[v] = 0;
    }
}

void build(int v, int tl, int tr)
{
    if (tl == tr)
    {
        sum[v] = mn[v] = mx[v] = a[tl];
        add[v] = 0;
    }
    else
    {
        int tm = (tl + tr) / 2;
        build(v * 2, tl, tm);
        build(v * 2 + 1, tm + 1, tr);
        sum[v] = sum[v * 2] + sum[v * 2 + 1];
        mn[v] = std::min(mn[v * 2], mn[v * 2 + 1]);
        mx[v] = std::max(mx[v * 2], mx[v * 2 + 1]);
        add[v] = 0;
    }
}

void update_set(int v, int tl, int tr, int pos, long long val)
{
    if (tl == tr)
    {
        sum[v] = mn[v] = mx[v] = val;
        add[v] = 0;
        return;
    }
    push(v, tl, tr);
    int tm = (tl + tr) / 2;
    if (pos <= tm) update_set(v * 2, tl, tm, pos, val);
    else update_set(v * 2 + 1, tm + 1, tr, pos, val);
    sum[v] = sum[v * 2] + sum[v * 2 + 1];
    mn[v] = std::min(mn[v * 2], mn[v * 2 + 1]);
    mx[v] = std::max(mx[v * 2], mx[v * 2 + 1]);
}

void update_add(int v, int tl, int tr, int l, int r, long long val)
{
    if (l > r) return;
    if (l == tl && r == tr)
    {
        sum[v] += val * (tr - tl + 1);
        mn[v] += val;
        mx[v] += val;
        add[v] += val;
        return;
    }
    push(v, tl, tr);
    int tm = (tl + tr) / 2;
    update_add(v * 2, tl, tm, l, std::min(r, tm), val);
    update_add(v * 2 + 1, tm + 1, tr, std::max(l, tm + 1), r, val);
    sum[v] = sum[v * 2] + sum[v * 2 + 1];
    mn[v] = std::min(mn[v * 2], mn[v * 2 + 1]);
    mx[v] = std::max(mx[v * 2], mx[v * 2 + 1]);
}

long long query_sum(int v, int tl, int tr, int l, int r)
{
    if (l > r) return 0;
    if (l == tl && r == tr) return sum[v];
    push(v, tl, tr);
    int tm = (tl + tr) / 2;
    return query_sum(v * 2, tl, tm, l, std::min(r, tm)) +
        query_sum(v * 2 + 1, tm + 1, tr, std::max(l, tm + 1), r);
}

long long query_min(int v, int tl, int tr, int l, int r)
{
    if (l > r) return INF;
    if (l == tl && r == tr) return mn[v];
    push(v, tl, tr);
    int tm = (tl + tr) / 2;
    return std::min(query_min(v * 2, tl, tm, l, std::min(r, tm)),
        query_min(v * 2 + 1, tm + 1, tr, std::max(l, tm + 1), r));
}

long long query_max(int v, int tl, int tr, int l, int r)
{
    if (l > r) return -INF;
    if (l == tl && r == tr) return mx[v];
    push(v, tl, tr);
    int tm = (tl + tr) / 2;
    return std::max(query_max(v * 2, tl, tm, l, std::min(r, tm)),
        query_max(v * 2 + 1, tm + 1, tr, std::max(l, tm + 1), r));
}

int main()
{
    std::ifstream fin("input.txt");
    std::ofstream fout("output.txt");

    fin >> n;
    a.assign(n, 0);
    sum.assign(4 * n, 0);
    mn.assign(4 * n, 0);
    mx.assign(4 * n, 0);
    add.assign(4 * n, 0);

    build(1, 0, n - 1);

    while (true)
    {
        int type;
        fin >> type;
        if (type == 0) break;

        switch (type)
        {
        case 1:
        {
            int i;
            long long v;
            fin >> i >> v;
            update_set(1, 0, n - 1, i, v);
            break;
        }
        case 2:
        {
            int l, r;
            long long v;
            fin >> l >> r >> v;
            update_add(1, 0, n - 1, l, r, v);
            break;
        }
        case 3:
        {
            int l, r;
            fin >> l >> r;
            fout << query_sum(1, 0, n - 1, l, r) << "\n";
            break;
        }
        case 4:
        {
            int l, r;
            fin >> l >> r;
            fout << query_min(1, 0, n - 1, l, r) << "\n";
            break;
        }
        case 5:
        {
            int l, r;
            fin >> l >> r;
            fout << query_max(1, 0, n - 1, l, r) << "\n";
            break;
        }
        }
    }
    fin.close();
    fout.close();
    return 0;
}
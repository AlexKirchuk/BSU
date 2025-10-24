/*
ƒана строка, состо€ща€ из строчных букв латинского алфавита,
без пробелов. ѕалиндромом называетс€ текст,
одинаково читаемый слева-направо и справа-налево.
Ќеобходимо найти палиндром максимальной длины,
который можно получить из исходной строки
вычеркиванием символов (мен€ть пор€док символов нельз€).
“ак как ответов может быть несколько, то найти
минимальный и максимальный лексикографически (как в словаре).

Input
¬ первой строке дана строка из строчных букв латинского алфавита,
без пробелов, длиной от $1$ до $10000$ символов.

Output
¬ первой строке вывести лексикографически минимальный палиндром
максимальной длины, во второй - максимальный.
≈сли они совпадают, вывести оба, каждый в своей строке.
*/
#include <iostream>
#include <string>
#include <vector>

long long myMax(long long a, long long b)
{
    return a > b ? a : b;
}

std::string build(const std::string& s, const std::vector<std::vector<int>>& f, bool maximaze)
{
    int n = s.size();
    int i = 0, j = n - 1;
    std::string left = "", right = "";

    while (i <= j) {
        if (s[i] == s[j])
        {
            left += s[i];
            if (i != j) right = s[j] + right;
            ++i;
            --j;
        }
        else if (i + 1 < n && f[i + 1][j] > f[i][j - 1])
        {
            ++i;
        }
        else if (i + 1 < n && f[i + 1][j] < f[i][j - 1])
        {
            --j;
        }
        else
        {
            if (maximaze)
            {
                if (s[i] <= s[j]) ++i;
                else --j;
            }
            else
            {
                if (s[i] >= s[j]) ++i;
                else --j;
            }
        }
    }
    return left + right;
}

int main()
{
    std::string s;
    std::cin >> s;
    int n = s.size();

    std::vector<std::vector<int>> f(n, std::vector<int>(n, 0));
    for (int i = 0; i < n; ++i) f[i][i] = 1;

    for (int d = 1; d < n; ++d)
    {
        for (int i = 0; i < n - d; ++i)
        {
            int j = i + d;
            if (s[i] == s[j])
            {
                f[i][j] = f[i + 1][j - 1] + 2;
            }
            else
            {
                f[i][j] = myMax(f[i + 1][j], f[i][j - 1]);
            }
        }
    }

    std::string min_pal = build(s, f, false);
    std::string max_pal = build(s, f, true);

    std::cout << min_pal << "\n" << max_pal << "\n";
    return 0;
}
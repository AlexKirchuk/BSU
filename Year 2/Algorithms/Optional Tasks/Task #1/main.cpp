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

std::string myMin(std::string a, std::string b)
{
    return a < b ? a : b;
}

std::string myMax(std::string a, std::string b)
{
    return a > b ? a : b;
}

int main()
{
    std::string s;
    std::cin >> s;
    int n = s.size();

    std::vector<std::vector<int>> f(n, std::vector<int>(n, 0));
    std::vector<std::vector<std::string>> minp(n, std::vector<std::string>(n, ""));
    std::vector<std::vector<std::string>> maxp(n, std::vector<std::string>(n, ""));

    for (int i = 0; i < n; ++i)
    {
        f[i][i] = 1;
        minp[i][i] = maxp[i][i] = std::string(1, s[i]);
    }

    for (int d = 1; d < n; ++d)
    {
        for (int i = 0; i + d < n; ++i)
        {
            int j = i + d;
            if (s[i] == s[j])
            {
                f[i][j] = f[i + 1][j - 1] + 2;
                std::string mid_min = (i + 1 <= j - 1) ? minp[i + 1][j - 1] : "";
                std::string mid_max = (i + 1 <= j - 1) ? maxp[i + 1][j - 1] : "";
                minp[i][j] = s[i] + mid_min + s[j];
                maxp[i][j] = s[i] + mid_max + s[j];
            }
            else
            {
                if (f[i + 1][j] > f[i][j - 1])
                {
                    f[i][j] = f[i + 1][j];
                    minp[i][j] = minp[i + 1][j];
                    maxp[i][j] = maxp[i + 1][j];
                }
                else if (f[i + 1][j] < f[i][j - 1])
                {
                    f[i][j] = f[i][j - 1];
                    minp[i][j] = minp[i][j - 1];
                    maxp[i][j] = maxp[i][j - 1];
                }
                else
                {
                    f[i][j] = f[i + 1][j];
                    minp[i][j] = myMin(minp[i + 1][j], minp[i][j - 1]);
                    maxp[i][j] = myMax(maxp[i + 1][j], maxp[i][j - 1]);
                }
            }
        }
    }

    std::cout << minp[0][n - 1] << "\n";
    std::cout << maxp[0][n - 1] << "\n";

    return 0;
}
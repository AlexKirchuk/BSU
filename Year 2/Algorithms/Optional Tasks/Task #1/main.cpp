/*
���� ������, ��������� �� �������� ���� ���������� ��������,
��� ��������. ����������� ���������� �����,
��������� �������� �����-������� � ������-������.
���������� ����� ��������� ������������ �����,
������� ����� �������� �� �������� ������
������������� �������� (������ ������� �������� ������).
��� ��� ������� ����� ���� ���������, �� �����
����������� � ������������ ����������������� (��� � �������).

Input
� ������ ������ ���� ������ �� �������� ���� ���������� ��������,
��� ��������, ������ �� $1$ �� $10000$ ��������.

Output
� ������ ������ ������� ����������������� ����������� ���������
������������ �����, �� ������ - ������������.
���� ��� ���������, ������� ���, ������ � ����� ������.
*/
#include <iostream>
#include <string>
#include <vector>
#include <map>

std::string myMin(std::string a, std::string b)
{
    return a < b ? a : b;
}

std::string myMax(std::string a, std::string b)
{
    return a > b ? a : b;
}

int myMax(int a, int b)
{
    return a > b ? a : b;
}

std::string s;
std::vector<std::vector<int>> f;

std::map<int, std::map<int, std::string>> memo;

std::string getMin(int i, int j)
{
    if (i > j) return "";
    if (i == j) return std::string(1, s[i]);
    if (memo[i].count(j)) return memo[i][j];

    if (s[i] == s[j])
    {
        std::string mid = getMin(i + 1, j - 1);
        return memo[i][j] = s[i] + mid + s[j];
    }

    if (f[i + 1][j] > f[i][j - 1]) return memo[i][j] = getMin(i + 1, j);
    if (f[i + 1][j] < f[i][j - 1]) return memo[i][j] = getMin(i, j - 1);

    std::string left = getMin(i + 1, j);
    std::string right = getMin(i, j - 1);
    return memo[i][j] = myMin(left, right);
}

std::string getMax(int i, int j)
{
    if (i > j) return "";
    if (i == j) return std::string(1, s[i]);
    if (memo[i].count(j)) return memo[i][j];

    if (s[i] == s[j])
    {
        std::string mid = getMax(i + 1, j - 1);
        return memo[i][j] = s[i] + mid + s[j];
    }

    if (f[i + 1][j] > f[i][j - 1]) return memo[i][j] = getMax(i + 1, j);
    if (f[i + 1][j] < f[i][j - 1]) return memo[i][j] = getMax(i, j - 1);

    std::string left = getMax(i + 1, j);
    std::string right = getMax(i, j - 1);
    return memo[i][j] = myMax(left, right);
}

int main()
{
    std::cin >> s;
    int n = s.size();
    f.assign(n, std::vector<int>(n, 0));

    for (int i = 0; i < n; ++i) f[i][i] = 1;

    for (int len = 2; len <= n; ++len)
    {
        for (int i = 0; i <= n - len; ++i)
        {
            int j = i + len - 1;
            if (s[i] == s[j])
                f[i][j] = (len == 2 ? 2 : f[i + 1][j - 1] + 2);
            else
                f[i][j] = myMax(f[i + 1][j], f[i][j - 1]);
        }
    }

    std::string minPal = getMin(0, n - 1);
    memo.clear();
    std::string maxPal = getMax(0, n - 1);

    std::cout << minPal << "\n" << maxPal << "\n";

    return 0;
}
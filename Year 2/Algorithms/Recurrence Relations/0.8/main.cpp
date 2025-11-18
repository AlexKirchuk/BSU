#include <string>
#include <fstream>
#include <vector>

int myMin(int a, int b, int c)
{
    if (a <= b && a <= c)
    {
        return a;
    }
    else if (b <= a && b <= c)
    {
        return b;
    }
    else
    {
        return c;
    }
}

int main()
{
    std::ifstream fin("in.txt");
    std::ofstream fout("out.txt");

    int x, y, z, n, m;
    std::string a, b;
    fin >> x >> y >> z;
    fin >> a >> b;
    n = a.size();
    m = b.size();

    std::vector<std::vector<int>> f(n + 1, std::vector<int>(m + 1, 0));

    for (int i = 1; i <= n; i++)
    {
        f[i][0] = i * x;
    }

    for (int i = 1; i <= m; i++)
    {
        f[0][i] = i * y;
    }

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            f[i][j] = myMin(f[i - 1][j] + x, f[i][j - 1] + y, f[i - 1][j - 1] + static_cast<int>(a[i - 1] != b[j - 1]) * z);
        }
    }

    fout << f[n][m];
    return 0;
}
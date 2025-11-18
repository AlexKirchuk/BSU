#include <fstream>
#include <string>
#include <vector>

long long myMax(long long a, long long b)
{
    return a > b ? a : b;
}

int main() {
    std::ifstream fin("input.txt");
    std::ofstream fout("output.txt");

    std::string s;
    std::getline(fin, s);
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

    std::string left = "", right = "";
    int i = 0, j = n - 1;
    while (i <= j)
    {
        if (s[i] == s[j])
        {
            left += s[i];
            if (i != j) right = s[j] + right;
            ++i;
            --j;
        }
        else if (i + 1 < n && f[i + 1][j] >= f[i][j - 1])
        {
            ++i;
        }
        else
        {
            --j;
        }
    }
    std::string pal = left + right;

    fout << f[0][n - 1] << std::endl;
    fout << pal << std::endl;

    return 0;
}
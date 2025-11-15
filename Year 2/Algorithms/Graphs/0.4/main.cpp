#include <fstream>
#include <vector>

int main()
{
    std::ifstream fin("input.txt");
    std::ofstream fout("output.txt");

    int n;
    fin >> n;

    std::vector<std::vector<int>> adjacency(n, std::vector<int>(n));

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            fin >> adjacency[i][j];
        }
    }

    std::vector<int> canonical(n, 0);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (adjacency[j][i])
            {
                canonical[i] = j + 1;
            }
        }
    }

    for (int i = 0; i < n; i++)
    {
        fout << canonical[i] << " ";
    }

    fin.close();
    fout.close();
    return 0;
}
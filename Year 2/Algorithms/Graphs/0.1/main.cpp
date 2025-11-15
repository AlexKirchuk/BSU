#include <fstream>
#include <vector>

int main()
{
    std::ifstream fin("input.txt");
    std::ofstream fout("output.txt");

    int n, m;
    fin >> n >> m;

    std::vector<std::vector<int>> adjacency(n, std::vector<int>(n, 0));
    for (int i = 0; i < m; i++)
    {
        int fst, snd;
        fin >> fst >> snd;
        adjacency[fst - 1][snd - 1] = adjacency[snd - 1][fst - 1] = 1;
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            fout << adjacency[i][j] << " ";
        }
        fout << "\n";
    }

    fin.close();
    fout.close();
    return 0;
}
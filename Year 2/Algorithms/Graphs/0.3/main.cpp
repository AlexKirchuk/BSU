#include <fstream>
#include <vector>

int main()
{
    std::ifstream fin("input.txt");
    std::ofstream fout("output.txt");

    int n, m;
    fin >> n >> m;

    std::vector<std::vector<int>> adjacency(n);
    for (int i = 0; i < m; i++)
    {
        int fst, snd;
        fin >> fst >> snd;
        adjacency[fst - 1].push_back(snd);
        adjacency[snd - 1].push_back(fst);
    }

    for (int i = 0; i < n; i++)
    {
        fout << adjacency[i].size() << " ";
        for (int j = 0; j < adjacency[i].size(); j++)
        {
            fout << adjacency[i][j] << " ";
        }
        fout << "\n";
    }

    fin.close();
    fout.close();
    return 0;
}
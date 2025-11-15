#include <fstream>
#include <vector>

int main()
{
    std::ifstream fin("input.txt");
    std::ofstream fout("output.txt");

    int n;
    fin >> n;

    std::vector<int> canonical(n, 0);
    for (int i = 0; i < n - 1; i++)
    {
        int fst, snd;
        fin >> fst >> snd;
        canonical[snd - 1] = fst;
    }

    for (int i = 0; i < n; i++)
    {
        fout << canonical[i] << " ";
    }

    fin.close();
    fout.close();
    return 0;
}
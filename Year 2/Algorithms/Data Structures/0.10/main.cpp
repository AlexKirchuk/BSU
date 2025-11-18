#include <fstream>
#include <vector>

int main()
{
    std::ifstream fin("input.txt");
    std::ofstream fout("output.txt");

    int m, c, n;
    fin >> m >> c >> n;

    std::vector<int> hash(m, -1);

    for (int i = 0; i < n; i++)
    {
        int x, attempt = 0;
        fin >> x;
        while (true)
        {
            int index = ((x % m) + c * attempt) % m;
            if (hash[index] == -1)
            {
                hash[index] = x;
                break;
            }
            else if (hash[index] == x)
            {
                break;
            }
            attempt++;
        }
    }

    for (int i = 0; i < m; i++)
    {
        fout << hash[i] << " ";
    }
    return 0;
}
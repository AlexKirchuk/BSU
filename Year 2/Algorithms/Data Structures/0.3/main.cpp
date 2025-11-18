#include <fstream>

int main()
{
    std::ifstream fin("input.txt");
    std::ofstream fout("output.txt");

    long long n, i = 0;
    fin >> n;

    while (n)
    {
        if (n % 2)
        {
            fout << i << "\n";
        }
        i++;
        n /= 2;
    }
    return 0;
}
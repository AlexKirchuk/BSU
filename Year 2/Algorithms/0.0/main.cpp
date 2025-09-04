#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

int main()
{
    std::ifstream fin;
    std::ofstream fout;

    fin.open("input.txt");
    fout.open("output.txt");

    std::vector<__int64>V;
    
    while (!fin.eof()) {
        __int64 val;
        fin >> val;
        V.push_back(val);
    }
    fin.close();

    std::sort(V.begin(), V.end());
    
    __int64 sum = 0;

    for (int i = 0; i < V.size(); i++)
    {
        if (i + 1 == V.size())
            sum += V[i];
        else if (V[i] == V[i + 1])
            continue;
        else
            sum += V[i];
    }
    fout << sum;
    std::cout << sum;
}

#include <iostream>
#include <fstream>
#include <string>

int main()
{
    std::ifstream fin;
    std::ofstream fout;

    fin.open("input.txt");
    fout.open("output.txt");

    long arrCount, * arr, queryCount, * query;
    std::string str, temp;

    std::getline(fin, str);
    arrCount = stoi(str);
    arr = new long[arrCount];
    std::getline(fin, str);
    for (long i = 0; i < arrCount; i++)
    {
        temp.clear();
        temp.append(str);
        temp.erase(1);
        arr[i] = stoi(temp);
        str.erase(0, 2);
    }

    std::getline(fin, str);
    queryCount = stoi(str);
    query = new long[queryCount];
    std::getline(fin, str);
    for (long i = 0; i < queryCount; i++)
    {
        temp.clear();
        temp.append(str);
        temp.erase(1);
        query[i] = stoi(temp);
        str.erase(0, 2);
    }
    fin.close();

    long b, l, r;
    for (long i = 0; i < queryCount; i++)
    {
        b = 0;
        l = -1;
        r = -1;

        for (long j = 0; j < arrCount; j++)
        {
            if (b != 1 and query[i] == arr[j])
            {
                b = 1;
                l = j;
            }
            else if (r != -1 and query[i] > arr[j])
            {
                r = j;
                continue;
            }
            else if (i == queryCount - 1 and r == -1)
            {
                fout << b << " " << l << " " << r << std::endl;
                std::cout << b << " " << l << " " << r << std::endl;
                break;
            }
            else
            {
                fout << b << " " << l << " " << r << std::endl;
                std::cout << b << " " << l << " " << r << std::endl;
                break;
            }
        }
    }

    delete[] arr;
    delete[] query;
}

#include <employee.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

int main(int argc, char* argv[])
{
    if (argc < 4)
    {
        std::cout << "Argc is less than 4" << std::endl;
        return 1;
    }

    char* binFile = argv[1];
    char* reportFile = argv[2];
    double payment = atof(argv[3]);

    std::ifstream fin(binFile, std::ios::binary);
    std::ofstream fout(reportFile);

    if (!fin)
    {
        std::cout << "Error: cannot open file " << binFile << std::endl;
        return 1;
    }

    fout << "Report based on file \"" << binFile << "\"" << std::endl;
    fout << "=========================================" << std::endl;
    fout << "Num\tName\tHours\tSalary" << std::endl;

    std::vector<employee> employees;
    employee emp;
    while (fin.read(reinterpret_cast<char*>(&emp), sizeof(emp)))
    {
        employees.push_back(emp);
    }

    std::sort(employees.begin(), employees.end(),
        [](const employee& a, const employee& b)
        {
            return a.hours > b.hours;
        });

    for (const auto& emp : employees)
    {
        fout << emp.num << "\t"
            << emp.name << "\t"
            << emp.hours << "\t"
            << emp.hours * payment << std::endl;
    }

    fin.close();
    fout.close();
    return 0;
}
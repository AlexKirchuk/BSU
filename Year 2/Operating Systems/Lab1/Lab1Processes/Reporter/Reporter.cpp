#include <iostream>
#include <fstream>

struct employee
{
    int num;
    char name[10];
    double hours;
};

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

    employee emp;
    while (fin.read(reinterpret_cast<char*>(&emp), sizeof(emp)))
    {
        double salary = emp.hours * payment;
        fout << emp.num << "\t" << emp.name << "\t" << emp.hours << "\t" << salary << std::endl;
    }

    fin.close();
    fout.close();
    return 0;
}

#include <employee.h>
#include <iostream>
#include <fstream>

int main(int argc, char* argv[])
{
    if (argc < 3)
    {
        std::cout << "Argc is less than 3" << std::endl;
        return 1;
    }

    char* filename = argv[1];
    int count = atoi(argv[2]);

    std::ofstream fout(filename, std::ios::binary);
    if (!fout)
    {
        std::cout << "Error: cannot open file " << filename << std::endl;
        return 1;
    }

    employee emp;
    for (int i = 0; i < count; i++)
    {
        std::cout << "Employee #" << (i + 1) << std::endl;
        std::cout << "Number: ";
        std::cin >> emp.num;
        std::cout << "Name: ";
        std::cin >> emp.name;
        std::cout << "Hours: ";
        std::cin >> emp.hours;
        fout.write(reinterpret_cast<char*>(&emp), sizeof(emp));
    }

    fout.close();
    return 0;
}
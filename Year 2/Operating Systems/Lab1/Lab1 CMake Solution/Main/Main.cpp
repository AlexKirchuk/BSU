#include <employee.h>
#include <string>
#include <iostream>
#include <fstream>

int main()
{
    std::string binFile, reportFile;
    int count;
    double payment;

    // Creator.exe
    std::cout << "Enter binary file name: ";
    std::cin >> binFile;
    std::cout << "Enter number of employees: ";
    std::cin >> count;

    std::string cmdCreator = buildCreatorCmd(binFile, count);

    if (!runProcess(cmdCreator))
    {
        std::cout << "Error: cannot start Creator.exe" << std::endl;
        return 1;
    }

    std::ifstream fin(binFile, std::ios::binary);
    if (!fin)
    {
        std::cout << "Error: cannot open binary file" << std::endl;
        return 1;
    }

    try
    {
        auto employees = readEmployees(binFile);
        std::cout << std::endl <<"Binary file content:" << std::endl;
        for (const auto& e : employees)
        {
            std::cout << e.num << " " << e.name << " " << e.hours << std::endl;
        }
    }
    catch (const std::exception& ex)
    {
        std::cout << ex.what() << std::endl;
        return 1;
    }

    // Reporter.exe
    std::cout << std::endl << "Enter report file name: ";
    std::cin >> reportFile;
    std::cout << "Enter hourly payment: ";
    std::cin >> payment;

    auto cmdReporter = buildReporterCmd(binFile, reportFile, payment);
    if (!runProcess(cmdReporter))
    {
        std::cout << "Error: cannot start Reporter.exe" << std::endl;
    }

    std::ifstream finReport(reportFile);
    if (!finReport)
    {
        std::cout << "Error: cannot open report file" << std::endl;
        return 1;
    }

    std::cout << std::endl << "Report:" << std::endl;
    std::string line;
    while (std::getline(finReport, line))
    {
        std::cout << line << std::endl;
    }
    finReport.close();

    return 0;
}

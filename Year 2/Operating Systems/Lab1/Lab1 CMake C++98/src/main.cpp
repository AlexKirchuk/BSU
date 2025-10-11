/*
Lab #1.
Topic: "Creating Processes."

Problem: Write a console program, Main, and two utilities, Creator and Reporter, that perform the following actions.
The Creator utility creates a binary file whose name and number of records are received via the command line.
The file's records are entered from the console and have the following structure:

struct employee
{
int num; // employee ID number
char name[10]; // employee name
double hours; // number of hours worked
};

The Reporter utility creates a text file containing an ordered list of employees
with their accrued wages. The report is generated based on the binary file created
by the Creator program.
1. The utility receives the following data via the command line:
1.1. Name of the source binary file.
1.2. Report file name.
1.3. Hourly wage.
2. The report contains the following lines:
2.1. Header: Report on file "source binary file name".
2.2. Line: Employee number, employee name, hours, salary.
2.3. List of employees by row. Each row contains information from the
corresponding binary file record, and the last column of the row contains the accrued salary = number of hours worked * hourly wage.

The Main program performs the following actions:
1. Requests the name of the binary file and the number of records in this file from the console.
2. Launches the Creator utility, passing the name
of the binary file being created and the number of records in this file via the command line.
3. Waits for the Creator utility to complete.
4. Outputs the contents of the created binary file to the console.
5. Requests from the console:
a. Report file name.
b. Hourly rate.
6. Launches the Reporter utility, passing the following via the command line:
a. Source binary file name.
b. Report file name.
c. Hourly rate.
7. Waits for the Reporter utility to complete.
8. Outputs the report to the console.
9. Exits.
Note: To wait for the Creator and Reporter processes to complete,
use the function:
DWORD WaitForSingleObject(
HANDLE hHandle, // object handle
DWORD dwMilliseconds // wait interval in milliseconds
);
where the second parameter is set to INFINITE, for example
WaitForSingleObject(hCreator, INFINITE);
where hCreator is the handle to the Creator process.

Lab1 is made on C++98 CMake, Google Unit Tests
*/

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
        std::cout << std::endl << "Binary file content:" << std::endl;
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
#include <windows.h>
#include <iostream>
#include <fstream>
#include <string>

struct employee
{
    int num;
    char name[10];
    double hours;
};

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

    std::string cmdCreator = "Creator.exe " + binFile + " " + std::to_string(count);

    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(STARTUPINFO));
    si.cb = sizeof(STARTUPINFO);

    if (!CreateProcess(NULL, const_cast<char*>(cmdCreator.c_str()),
        NULL, NULL, FALSE, CREATE_NEW_CONSOLE,
        NULL, NULL, &si, &pi))
    {
        std::cout << "Error: cannot start Creator.exe" << std::endl;
        return 1;
    }

    WaitForSingleObject(pi.hProcess, INFINITE);
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    std::ifstream fin(binFile, std::ios::binary);
    if (!fin)
    {
        std::cout << "Error: cannot open binary file" << std::endl;
        return 1;
    }

    employee emp;
    std::cout << std::endl << "Binary file content:" << std::endl;
    while (fin.read(reinterpret_cast<char*>(&emp), sizeof(emp)))
    {
        std::cout << emp.num << " " << emp.name << " " << emp.hours << std::endl;
    }
    fin.close();

    // Reporter.exe
    std::cout << std::endl << "Enter report file name: ";
    std::cin >> reportFile;
    std::cout << "Enter hourly payment: ";
    std::cin >> payment;

    std::string cmdReporter = "Reporter.exe " + binFile + " " + reportFile + " " + std::to_string(payment);

    STARTUPINFO si2;
    PROCESS_INFORMATION pi2;
    ZeroMemory(&si2, sizeof(STARTUPINFO));
    si2.cb = sizeof(STARTUPINFO);

    if (!CreateProcess(NULL, const_cast<char*>(cmdReporter.c_str()),
        NULL, NULL, FALSE, CREATE_NEW_CONSOLE,
        NULL, NULL, &si2, &pi2))
    {
        std::cout << "Error: cannot start Reporter.exe" << std::endl;
        return 1;
    }

    WaitForSingleObject(pi2.hProcess, INFINITE);
    CloseHandle(pi2.hProcess);
    CloseHandle(pi2.hThread);

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

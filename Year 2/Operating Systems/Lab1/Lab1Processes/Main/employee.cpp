#include "employee.h"
#include <windows.h>
#include <fstream>
#include <stdexcept>

std::vector<employee> readEmployees(const std::string& filename)
{
    std::ifstream fin(filename, std::ios::binary);
    if (!fin) throw std::runtime_error("Cannot open file: " + filename);

    std::vector<employee> employees;
    employee emp;
    while (fin.read(reinterpret_cast<char*>(&emp), sizeof(emp)))
    {
        employees.push_back(emp);
    }
    return employees;
}

std::string buildCreatorCmd(const std::string& binFile, int count)
{
    return "Creator.exe " + binFile + " " + std::to_string(count);
}

std::string buildReporterCmd(const std::string& binFile, const std::string& reportFile, double payment)
{
    return "Reporter.exe " + binFile + " " + reportFile + " " + std::to_string(payment);
}

bool runProcess(const std::string& cmdLine)
{
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(STARTUPINFO));
    si.cb = sizeof(STARTUPINFO);

    if (!CreateProcess(NULL, const_cast<char*>(cmdLine.c_str()),
        NULL, NULL, FALSE, CREATE_NEW_CONSOLE,
        NULL, NULL, &si, &pi))
    {
        return false;
    }

    WaitForSingleObject(pi.hProcess, INFINITE);
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
    return true;
}

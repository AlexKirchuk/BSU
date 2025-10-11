#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <string>
#include <vector>

struct employee
{
    int num;
    char name[10];
    double hours;
};

std::vector<employee> readEmployees(const std::string& filename);

std::string buildCreatorCmd(const std::string& binFile, int count);
std::string buildReporterCmd(const std::string& binFile, const std::string& reportFile, double payment);

bool runProcess(const std::string& cmdLine);

#endif
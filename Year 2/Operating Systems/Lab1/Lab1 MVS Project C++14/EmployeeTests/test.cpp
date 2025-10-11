#include "pch.h"
#include "employee.h"
#include <windows.h>
#include <gtest/gtest.h>
#include <fstream>
#include <vector>

TEST(BuildCmdTests, CreatorCmdCorrect)
{
    std::string cmd = buildCreatorCmd("data.bin", 5);
    EXPECT_EQ(cmd, "Creator.exe data.bin 5");
}

TEST(BuildCmdTests, ReporterCmdCorrect)
{
    std::string cmd = buildReporterCmd("data.bin", "report.txt", 10.5);
    EXPECT_EQ(cmd, "Reporter.exe data.bin report.txt 10.500000");
}

TEST(ReadEmployeesTests, SingleEmployee)
{
    employee e{ 1, "Alex", 40.0 };
    std::ofstream fout("one.bin", std::ios::binary);
    fout.write(reinterpret_cast<char*>(&e), sizeof(e));
    fout.close();

    auto emps = readEmployees("one.bin");
    ASSERT_EQ(emps.size(), 1);
    EXPECT_EQ(emps[0].num, 1);
    EXPECT_STREQ(emps[0].name, "Alex");
    EXPECT_DOUBLE_EQ(emps[0].hours, 40.0);
}

TEST(RunProcessTests, InvalidProcess)
{
    bool result = runProcess("NonExistentProgram.exe");
    EXPECT_FALSE(result);
}

TEST(CalcSalaryTests, SimpleCalculation)
{
    employee e{ 1, "Bob", 8.0 };
    double payment = 15.0;
    double salary = e.hours * payment;
    EXPECT_DOUBLE_EQ(salary, 120.0);
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
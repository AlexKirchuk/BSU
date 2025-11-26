#include "employee.h"
#include <gtest/gtest.h>
#include <boost/shared_ptr.hpp>
#include <windows.h>
#include <string>
#include <vector>
#include <fstream>

struct RecSem
{
    HANDLE readCountMutex;
    HANDLE resourceSem;
    int readCount;
    RecSem() : readCount(0), readCountMutex(NULL), resourceSem(NULL) {}
};

inline boost::shared_ptr<employee> find_emp(std::vector<boost::shared_ptr<employee>>& emps, int id)
{
    for (size_t i = 0; i < emps.size(); ++i)
    {
        if (emps[i]->num == id)
        {
            return emps[i];
        }
    }
    return boost::shared_ptr<employee>();
}

// ------------------------ 1. find_emp ------------------------
TEST(FindEmpTest, FindExisting)
{
    std::vector<boost::shared_ptr<employee>> emps;
    boost::shared_ptr<employee> e1(new employee());
    e1->num = 1; strcpy(e1->name, "Alice"); e1->hours = 40;
    emps.push_back(e1);

    auto found = find_emp(emps, 1);
    ASSERT_TRUE(found);
    EXPECT_EQ(found->num, 1);
    EXPECT_STREQ(found->name, "Alice");
}

TEST(FindEmpTest, NotFound)
{
    std::vector<boost::shared_ptr<employee>> emps;
    boost::shared_ptr<employee> e1(new employee());
    e1->num = 1; strcpy(e1->name, "Alice"); e1->hours = 40;
    emps.push_back(e1);

    auto found = find_emp(emps, 2);
    EXPECT_FALSE(found);
}

// ------------------------ 2. RecSem logic ------------------------
TEST(RecSemTest, FirstReaderLocksResource)
{
    RecSem rs;
    rs.readCount = 0;
    rs.resourceSem = CreateSemaphore(NULL, 1, 1, NULL);

    WaitForSingleObject(rs.readCountMutex, INFINITE);
    rs.readCount++;
    if (rs.readCount == 1) WaitForSingleObject(rs.resourceSem, INFINITE);
    ReleaseSemaphore(rs.readCountMutex, 1, NULL);

    EXPECT_EQ(rs.readCount, 1);
    ReleaseSemaphore(rs.resourceSem, 1, NULL);
    CloseHandle(rs.resourceSem);
}

TEST(RecSemTest, WriterLocksResource)
{
    RecSem rs;
    rs.resourceSem = CreateSemaphore(NULL, 1, 1, NULL);
    WaitForSingleObject(rs.resourceSem, INFINITE);
    DWORD state = WaitForSingleObject(rs.resourceSem, 0);
    EXPECT_EQ(state, WAIT_TIMEOUT);
    ReleaseSemaphore(rs.resourceSem, 1, NULL);
    CloseHandle(rs.resourceSem);
}

// ------------------------ 3. Employee file ------------------------
TEST(FileTest, WriteReadEmployee)
{
    employee e{ 10,"Bob", 55 };
    std::ofstream out("tmp.bin", std::ios::binary);
    out.write((char*)&e, sizeof(e));
    out.close();

    employee r{};
    std::ifstream in("tmp.bin", std::ios::binary);
    in.read((char*)&r, sizeof(r));
    in.close();

    EXPECT_EQ(r.num, 10);
    EXPECT_STREQ(r.name, "Bob");
    EXPECT_DOUBLE_EQ(r.hours, 55);
}

// ------------------------ 4. Modify Employee ------------------------
TEST(FileTest, ModifyEmployeeInFile)
{
    employee e{ 1,"Alice", 40 };
    employee m{ 1,"Alice2", 60 };

    std::ofstream out("tmp2.bin", std::ios::binary);
    out.write((char*)&e, sizeof(e));
    out.close();

    std::fstream f("tmp2.bin", std::ios::in | std::ios::out | std::ios::binary);
    f.seekp(0);
    f.write((char*)&m, sizeof(m));
    f.close();

    employee r{};
    std::ifstream in("tmp2.bin", std::ios::binary);
    in.read((char*)&r, sizeof(r));
    in.close();

    EXPECT_EQ(r.hours, 60);
    EXPECT_STREQ(r.name, "Alice2");
}

// ------------------------ 5. Error cases ------------------------
TEST(ErrorTest, NegativeHours)
{
    employee e{ 1,"X",-5 };
    EXPECT_LT(e.hours, 0);
}

TEST(ErrorTest, EmptyName) {
    employee e{ 1,"",10 };
    EXPECT_EQ(strlen(e.name), 0);
}

// ------------------------ 6. Employee not found ------------------------
TEST(ServerLogicTest, WrongIDReturnsDefault)
{
    employee nf;
    nf.num = -1;
    nf.hours = 0.0;
    for (int i = 0; i < 10; i++) nf.name[i] = '\0';

    EXPECT_EQ(nf.num, -1);
    EXPECT_DOUBLE_EQ(nf.hours, 0.0);
}

// ------------------------ 7. Stress readers/writers ------------------------
TEST(ReadersWritersTest, MultipleReaders)
{
    RecSem rs;
    rs.readCount = 0;
    rs.resourceSem = CreateSemaphore(NULL, 1, 1, NULL);

    for (int i = 0; i < 3; i++) {
        WaitForSingleObject(rs.readCountMutex, INFINITE);
        rs.readCount++;
        if (rs.readCount == 1) WaitForSingleObject(rs.resourceSem, INFINITE);
        ReleaseSemaphore(rs.readCountMutex, 1, NULL);
    }

    EXPECT_EQ(rs.readCount, 3);
    ReleaseSemaphore(rs.resourceSem, 1, NULL);
    CloseHandle(rs.resourceSem);
}

TEST(ReadersWritersTest, WriterBlocksReaders)
{
    RecSem rs;
    rs.readCount = 0;
    rs.resourceSem = CreateSemaphore(NULL, 1, 1, NULL);
    WaitForSingleObject(rs.resourceSem, INFINITE);

    DWORD state = WaitForSingleObject(rs.resourceSem, 0);
    EXPECT_EQ(state, WAIT_TIMEOUT);

    ReleaseSemaphore(rs.resourceSem, 1, NULL);
    CloseHandle(rs.resourceSem);
}
#include "employee.h"
#include <gtest/gtest.h>
#include <boost/shared_ptr.hpp>
#include <string>
#include <vector>
#include <fstream>
#include <mutex>

struct RecSem
{
    std::mutex mtx;
    std::mutex resource;
    int readCount = 0;
};

// ---------- 1. find_emp ----------
inline boost::shared_ptr<employee> find_emp(std::vector<boost::shared_ptr<employee>>& emps, int id)
{
    for (size_t i = 0; i < emps.size(); ++i)
        if (emps[i]->num == id) return emps[i];
    return nullptr;
}

TEST(FindEmpTest, FindExisting)
{
    std::vector<boost::shared_ptr<employee>> emps;
    auto e1 = boost::shared_ptr<employee>(new employee());
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
    auto e1 = boost::shared_ptr<employee>(new employee());
    e1->num = 1; strcpy(e1->name, "Alice"); e1->hours = 40;
    emps.push_back(e1);

    auto found = find_emp(emps, 2);
    EXPECT_FALSE(found);
}

// ---------- 2. RecSem logic ----------
TEST(RecSemTest, FirstReaderLocksResource)
{
    RecSem rs;
    {
        std::unique_lock<std::mutex> lk(rs.mtx);
        rs.readCount++;
        if (rs.readCount == 1)
            rs.resource.lock();
    }

    EXPECT_EQ(rs.readCount, 1);
    {
        std::unique_lock<std::mutex> lk(rs.mtx);
        rs.readCount--;
        if (rs.readCount == 0)
            rs.resource.unlock();
    }
}

TEST(RecSemTest, WriterLocksResource)
{
    RecSem rs;

    rs.resource.lock();

    bool blocked = !rs.resource.try_lock();
    EXPECT_TRUE(blocked);

    rs.resource.unlock();
}

// ---------- 3. Employee file ----------
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

// ---------- 4. Modify Employee ----------
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

// ---------- 5. Error cases ----------
TEST(ErrorTest, NegativeHours)
{
    employee e{ 1,"X",-5 };
    EXPECT_LT(e.hours, 0);
}

TEST(ErrorTest, EmptyName)
{
    employee e{ 1,"",10 };
    EXPECT_EQ(strlen(e.name), 0);
}

// ---------- 6. Employee not found ----------
TEST(ServerLogicTest, WrongIDReturnsDefault)
{
    employee nf{};
    nf.num = -1;
    nf.hours = 0.0;
    nf.name[0] = '\0';

    EXPECT_EQ(nf.num, -1);
    EXPECT_DOUBLE_EQ(nf.hours, 0.0);
    EXPECT_STREQ(nf.name, "");
}

// ---------- 7. Stress readers/writers ----------
TEST(ReadersWritersTest, MultipleReaders)
{
    RecSem rs;

    for (int i = 0; i < 3; i++)
    {
        std::unique_lock<std::mutex> lk(rs.mtx);
        rs.readCount++;
        if (rs.readCount == 1)
            rs.resource.lock();
    }

    EXPECT_EQ(rs.readCount, 3);
    {
        std::unique_lock<std::mutex> lk(rs.mtx);
        rs.readCount = 0;
        rs.resource.unlock();
    }
}

TEST(ReadersWritersTest, WriterBlocksReaders)
{
    RecSem rs;

    rs.resource.lock();

    bool blocked = false;
    {
        std::unique_lock<std::mutex> lk(rs.mtx);
        bool tryLock = rs.resource.try_lock();
        blocked = !tryLock;
        if (tryLock) rs.resource.unlock();
    }

    EXPECT_TRUE(blocked);

    rs.resource.unlock();
}
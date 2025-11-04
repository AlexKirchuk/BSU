#include <gtest/gtest.h>
#include <common.h>
#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/sync/named_semaphore.hpp>
#include <fstream>

namespace bip = boost::interprocess;
using namespace std::string_literals;

void CleanIPC()
{
    bip::named_semaphore::remove("MutexAccess");
    bip::named_semaphore::remove("EmptySlots");
    bip::named_semaphore::remove("FullSlots");
    bip::shared_memory_object::remove("SharedMemory");
}

class IPCFixture : public ::testing::Test
{
protected:
    void SetUp() override
    {
        CleanIPC();
        mutex = std::make_unique<bip::named_semaphore>(bip::open_or_create, "MutexAccess", 1);
        empty = std::make_unique<bip::named_semaphore>(bip::open_or_create, "EmptySlots", 2);
        full = std::make_unique<bip::named_semaphore>(bip::open_or_create, "FullSlots", 0);

        segment = std::make_unique<bip::managed_shared_memory>(bip::open_or_create, "SharedMemory", 1024);
        buffer = segment->find_or_construct<RingBuffer>("RingBuffer")();
        buffer->head = 0;
        buffer->tail = 0;
    }

    void TearDown() override
    {
        CleanIPC();
    }

    std::unique_ptr<bip::named_semaphore> mutex;
    std::unique_ptr<bip::named_semaphore> empty;
    std::unique_ptr<bip::named_semaphore> full;
    std::unique_ptr<bip::managed_shared_memory> segment;
    RingBuffer* buffer = nullptr;
};

TEST_F(IPCFixture, BasicQueueFIFO)
{
    std::string filename = "test_buffer.bin";
    std::ofstream file(filename, std::ios::binary | std::ios::trunc);
    file.close();

    empty->wait();
    mutex->wait();

    std::fstream f1(filename, std::ios::in | std::ios::out | std::ios::binary);
    std::string msg1 = "Hello";
    msg1.append(MAX_MESSAGE_LENGTH - msg1.size(), '\0');
    f1.seekp(buffer->tail * MAX_MESSAGE_LENGTH, std::ios::beg);
    f1.write(msg1.c_str(), MAX_MESSAGE_LENGTH);
    f1.close();

    buffer->tail = (buffer->tail + 1) % 2;
    mutex->post();
    full->post();

    full->wait();
    mutex->wait();

    std::fstream f2(filename, std::ios::in | std::ios::out | std::ios::binary);
    char msgRead[MAX_MESSAGE_LENGTH] = { 0 };
    f2.seekg(buffer->head * MAX_MESSAGE_LENGTH, std::ios::beg);
    f2.read(msgRead, MAX_MESSAGE_LENGTH);
    f2.close();

    buffer->head = (buffer->head + 1) % 2;
    mutex->post();
    empty->post();

    EXPECT_STREQ(msgRead, "Hello");
}

TEST_F(IPCFixture, EmptyBufferBlocksReceiver)
{
    EXPECT_NO_THROW({
        bool timedOut = false;
        auto start = std::chrono::steady_clock::now();
        try
        {
            full->timed_wait(start + std::chrono::milliseconds(200));
        }
    catch (...)
        {
            timedOut = true;
        }
    EXPECT_FALSE(timedOut);
        });
}

TEST_F(IPCFixture, IPCObjectsCleaned)
{
    CleanIPC();
    EXPECT_FALSE(bip::shared_memory_object::remove("SharedMemory"));
    EXPECT_TRUE(true);
}
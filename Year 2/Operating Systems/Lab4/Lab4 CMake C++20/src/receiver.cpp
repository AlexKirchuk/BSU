#include <common.h>
#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/sync/named_mutex.hpp>
#include <boost/interprocess/sync/named_semaphore.hpp>
#include <boost/interprocess/offset_ptr.hpp>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>

namespace bip = boost::interprocess;

int main()
{
    try
    {
        std::string filename;
        std::cout << "Enter filename: ";
        std::cin >> filename;

        int capacity;
        std::cout << "Enter number of messages in queue: ";
        std::cin >> capacity;

        int numSenders;
        std::cout << "Enter number of senders: ";
        std::cin >> numSenders;

        bip::named_mutex mutex(bip::open_or_create, ipc_names::MUTEX_NAME.c_str());
        bip::named_semaphore empty(bip::open_or_create, ipc_names::EMPTY_NAME.c_str(), capacity);
        bip::named_semaphore full(bip::open_or_create, ipc_names::FULL_NAME.c_str(), 0);

        std::ofstream file(filename.c_str(), std::ios::binary);
        if (!file)
        { throw std::runtime_error("Failed to create file"); }
        file.close();

        bip::managed_shared_memory segment(bip::open_or_create, ipc_names::SHMEM_NAME.c_str(), 1024);
        
        bip::offset_ptr<RingBuffer> buffer(segment.find_or_construct<RingBuffer>("RingBuffer")());
        buffer->head = 0;
        buffer->tail = 0;

        for (int i = 0; i < numSenders; ++i)
        {
            std::string cmd = "start sender.exe " + std::to_string(i) + " "
                + std::to_string(capacity) + " " + filename;
            std::system(cmd.c_str());
        }

        std::cout << "All senders ready" << std::endl;

        while (true)
        {
            std::cout << "Enter command (read/exit): ";
            std::string cmd;
            std::getline(std::cin, cmd);
            if (cmd == "exit")
            { break; }
            if (cmd == "read")
            {
                full.wait();
                mutex.lock();

                std::fstream file(filename.c_str(), std::ios::in | std::ios::out | std::ios::binary);
                file.seekg(buffer->head * MAX_MESSAGE_LENGTH, std::ios::beg);
                char msg[MAX_MESSAGE_LENGTH] = { 0 };
                file.read(msg, MAX_MESSAGE_LENGTH);
                std::cout << "Received: " << msg << std::endl;

                file.seekp(buffer->head * MAX_MESSAGE_LENGTH, std::ios::beg);
                std::string emptyMsg(MAX_MESSAGE_LENGTH, '\0');
                file.write(emptyMsg.c_str(), MAX_MESSAGE_LENGTH);
                file.close();

                buffer->head = (buffer->head + 1) % capacity;

                mutex.unlock();
                empty.post();
            }
        }
        bip::named_mutex::remove(ipc_names::MUTEX_NAME.c_str());
        bip::named_semaphore::remove(ipc_names::EMPTY_NAME.c_str());
        bip::named_semaphore::remove(ipc_names::FULL_NAME.c_str());
        bip::shared_memory_object::remove(ipc_names::SHMEM_NAME.c_str());
    }
    catch (const std::exception& e)
    {
        std::cout << "Exception: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}
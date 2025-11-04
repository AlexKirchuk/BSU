#include <common.h>
#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/sync/named_mutex.hpp>
#include <boost/interprocess/sync/named_semaphore.hpp>
#include <iostream>
#include <fstream>
#include <string>

namespace bip = boost::interprocess;

int main(int argc, char* argv[])
{
    try
    {
        if (argc < 4)
        { throw std::runtime_error("Not enough arguments"); }

        int senderId = std::stoi(argv[1]);
        int capacity = std::stoi(argv[2]);
        std::string filename = argv[3];

        auto mutex = open_mutex();
        auto empty = open_empty();
        auto full = open_full();
        bip::managed_shared_memory segment(bip::open_only, ipc_names::SHMEM_NAME.c_str());
        
        RingBuffer* buffer = segment.find<RingBuffer>("RingBuffer").first;
        if (!buffer) { throw std::runtime_error("Shared buffer not found"); }

        while (true)
        {
            std::cout << "Enter command (send/exit): ";
            std::string cmd;
            std::cin >> cmd;
            if (cmd == "exit")
            { break; }
            if (cmd == "send")
            {
                std::string msg;
                std::cout << "Enter message: ";
                std::cin >> msg;
                if (msg.size() >= MAX_MESSAGE_LENGTH)
                { msg = msg.substr(0, MAX_MESSAGE_LENGTH - 1); }

                empty.wait();
                mutex.lock();

                std::fstream file(filename.c_str(), std::ios::in | std::ios::out | std::ios::binary);
                
                file.seekp(buffer->tail * MAX_MESSAGE_LENGTH, std::ios::beg);
                std::string padded = msg;
                padded.append(MAX_MESSAGE_LENGTH - padded.size(), '\0');
                file.write(padded.c_str(), MAX_MESSAGE_LENGTH);
                file.close();

                buffer->tail = (buffer->tail + 1) % capacity;

                mutex.unlock();
                full.post();
            }
        }
    }
    catch (const std::exception& e)
    {
        std::cout << "Exception: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}
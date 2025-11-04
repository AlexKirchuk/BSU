/*
Lab #4

Topic: “Process Synchronization”.

Problem: Write a program for transferring messages between processes through
a shared file. The program includes one Receiver process and several Sender processes.
Sender processes send messages to the Receiver process.
Requirements for the implementation of the Receiver process. The Receiver process must
perform the following actions:
1. Enter from the console the name of the binary file and the number of records in the binary file,
which will be used for message transfer.
2. Create a binary file for messages. The maximum message length is 20
characters.
3. Enter from the console the number of Sender processes.
4. Start the specified number of Sender processes. Pass the file name for messages to each Sender process
via the command line.
5. Wait for a ready signal from all Sender processes.
6. Cyclically perform the following actions on command from the console:
read a message from the binary file or
terminate its work.
Note. The Receiver process goes into a waiting state for a new message if the command to read a message from an empty binary file is called.
Requirements for the implementation of the Sender process. The Sender process must
perform the following actions:
1. Open the file for message transfer. Get the file name from the command line.
2. Send a ready signal to the Receiver process.
3. Cyclically perform the following actions on command from the console:
send a message to the Receiver process or
terminate its work.
The message text is entered from the console. The message length is less than 20 characters.
Note. The Sender process goes into a waiting state if the command to write a message to a binary file filled with messages is called.
Additional requirements: Message transfer through the binary file
should be organized as a circular FIFO queue. I.e. The Receiver process
must read messages in the order in which they were sent by the Sender processes.
Simplified version of the laboratory work. Solve the given problem
for one Receiver process and one Sender process. In this case, only one message
can be transmitted between the processes simultaneously.

Lab4 is made on C++20 CMake, Google Unit Tests
*/

#include <common.h>
#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/sync/named_mutex.hpp>
#include <boost/interprocess/sync/named_semaphore.hpp>
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
        
        RingBuffer* buffer = segment.find_or_construct<RingBuffer>("RingBuffer")();
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
            std::cin >> cmd;
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
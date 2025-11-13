#include <common.h>
#include <windows.h>
#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>

int main(int argc, char* argv[])
{
    try
    {
        if (argc < 4)
        { throw std::runtime_error("Not enough arguments"); }

        int senderId = std::atoi(argv[1]);
        int capacity = std::atoi(argv[2]);
        std::string filename = argv[3];

        HANDLE hMutex = OpenSemaphore(SEMAPHORE_ALL_ACCESS, FALSE, "MutexAccess");
        if (!hMutex)
        { throw std::runtime_error("Failed to open mutex"); }

        HANDLE hEmpty = OpenSemaphore(SEMAPHORE_ALL_ACCESS, FALSE, "EmptySlots");
        if (!hEmpty)
        { throw std::runtime_error("Failed to open empty semaphore"); }

        HANDLE hFull = OpenSemaphore(SEMAPHORE_ALL_ACCESS, FALSE, "FullSlots");
        if (!hFull)
        { throw std::runtime_error("Failed to open full semaphore"); }

        std::string evName = "SenderReady" + std::to_string(senderId);
        HANDLE hReady = OpenEvent(EVENT_ALL_ACCESS, FALSE, evName.c_str());
        if (!hReady)
        { throw std::runtime_error("Failed to open sender ready event"); }
        SetEvent(hReady);

        HANDLE hMap = OpenFileMapping(FILE_MAP_ALL_ACCESS, FALSE, "GlobalRingBuffer");
        if (!hMap)
        { throw std::runtime_error("Failed to open shared memory"); }

        RingBuffer* buffer = static_cast<RingBuffer*>(MapViewOfFile(hMap, FILE_MAP_ALL_ACCESS, 0, 0, sizeof(RingBuffer)));
        if (!buffer)
        { throw std::runtime_error("Failed to map shared memory"); }

        while (true)
        {
            std::cout << "Enter command (send/exit): ";
            std::string cmd;
            std::getline(std::cin, cmd);
            if (cmd == "exit")
            { break; }
            if (cmd == "send")
            {
                std::string msg;
                std::cout << "Enter message: ";
                std::getline(std::cin, msg);
                if (msg.size() >= MAX_MESSAGE_LENGTH)
                { msg = msg.substr(0, MAX_MESSAGE_LENGTH - 1); }

                WaitForSingleObject(hEmpty, INFINITE);
                WaitForSingleObject(hMutex, INFINITE);

                std::fstream file(filename.c_str(), std::ios::in | std::ios::out | std::ios::binary);
                if (!file)
                { throw std::runtime_error("Failed to open file"); }

                file.seekp(buffer->tail * MAX_MESSAGE_LENGTH, std::ios::beg);
                std::string padded = msg;
                padded.append(MAX_MESSAGE_LENGTH - padded.size(), '\0');
                file.write(padded.c_str(), MAX_MESSAGE_LENGTH);
                file.close();

                buffer->tail = (buffer->tail + 1) % capacity;

                ReleaseSemaphore(hMutex, 1, NULL);
                ReleaseSemaphore(hFull, 1, NULL);
            }
        }
        UnmapViewOfFile(buffer);
        CloseHandle(hMap);
        CloseHandle(hMutex);
        CloseHandle(hEmpty);
        CloseHandle(hFull);
    }
    catch (const std::exception& e)
    {
        std::cout << "Exception: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}
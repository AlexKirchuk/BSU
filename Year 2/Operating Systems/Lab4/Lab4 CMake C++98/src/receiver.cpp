#include <boost/shared_array.hpp>
#include <common.h>
#include <windows.h>
#include <iostream>
#include <vector>
#include <string>

int main()
{
    try
    {
        std::string filename;
        std::cout << "Enter filename: ";
        std::cin >> filename;

        int numMessages;
        std::cout << "Enter number of messages in queue: ";
        std::cin >> numMessages;

        int numSenders;
        std::cout << "Enter number of senders: ";
        std::cin >> numSenders;

        HANDLE hMutex = CreateSemaphore(NULL, 1, 1, "MutexAccess");
        if (hMutex == NULL) { throw std::runtime_error("Failed to create mutex semaphore"); }

        HANDLE hEmpty = CreateSemaphore(NULL, numMessages, numMessages, "EmptySlots");
        if (hEmpty == NULL) { throw std::runtime_error("Failed to create empty semaphore"); }

        HANDLE hFull = CreateSemaphore(NULL, 0, numMessages, "FullSlots");
        if (hFull == NULL) { throw std::runtime_error("Failed to create full semaphore"); }

        std::vector<HANDLE> senderReadyEvents;
        for (int i = 0; i < numSenders; ++i)
        {
            std::string evName = "SenderReady" + std::to_string(i);
            HANDLE hEvent = CreateEvent(NULL, TRUE, FALSE, evName.c_str());
            if (hEvent == NULL) { throw std::runtime_error("Failed to create sender ready event"); }
            senderReadyEvents.push_back(hEvent);
        }

        STARTUPINFO si = { sizeof(STARTUPINFO) };
        PROCESS_INFORMATION pi;

        for (int i = 0; i < numSenders; ++i)
        {
            std::string cmd = "sender.exe " + std::to_string(i) + " " + std::to_string(numMessages);

            STARTUPINFO si = { sizeof(STARTUPINFO) };
            PROCESS_INFORMATION pi;

            if (!CreateProcess(NULL, const_cast<char*>(cmd.c_str()),
                NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi))
            { throw std::runtime_error("Failed to start sender process"); }

            CloseHandle(pi.hProcess);
            CloseHandle(pi.hThread);
        }

        for (int i = 0; i < numSenders; ++i) { WaitForSingleObject(senderReadyEvents[i], INFINITE); }
        std::cout << "All senders ready" << std::endl;

        RingBuffer buffer;
        buffer.capacity = numMessages;
        buffer.head = 0;
        buffer.tail = 0;
        buffer.messages = boost::shared_array<std::string>(new std::string[numMessages]);

        while (true)
        {
            std::cout << "Enter command (read/exit): ";
            std::string cmd;
            std::cin >> cmd;
            if (cmd == "exit") break;
            if (cmd == "read") {
                if (WaitForSingleObject(hFull, INFINITE) != WAIT_OBJECT_0) { continue; }
                if (WaitForSingleObject(hMutex, INFINITE) != WAIT_OBJECT_0) { continue; }

                std::string msg = buffer.messages[buffer.head];
                std::cout << "Received: " << msg << std::endl;

                buffer.head = (buffer.head + 1) % buffer.capacity;

                ReleaseSemaphore(hMutex, 1, NULL);
                ReleaseSemaphore(hEmpty, 1, NULL);
            }
        }

        CloseHandle(hMutex);
        CloseHandle(hEmpty);
        CloseHandle(hFull);
        for (int i = 0; i < numSenders; ++i) { CloseHandle(senderReadyEvents[i]); }
    }
    catch (const std::exception& e)
    {
        std::cout << "Exception: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}
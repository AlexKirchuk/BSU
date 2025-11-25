#include "employee.h"
#include <boost/shared_ptr.hpp>
#include <windows.h>
#include <iostream>
#include <fstream>
#include <string>

int main()
{
    std::string serverName = "localhost";

    HANDLE hMutex = OpenSemaphore(SEMAPHORE_ALL_ACCESS, FALSE, "MutexAccess");
    if (!hMutex)
    {
        throw std::runtime_error("Failed to open mutex");
    }

    std::string pipeName = "\\\\" + serverName + "\\pipe\\employee_pipe";
    char choice;

    while (true)
    {
        std::cout << "Choose operation: (r)ead, (m)odify, (e)xit: ";
        std::cin >> choice;

        if (choice == 'r' || choice == 'm')
        {
            int id;
            std::cout << "Enter employee ID: ";
            std::cin >> id;

            DWORD w = WaitForSingleObject(hMutex, INFINITE);
            if (w != WAIT_OBJECT_0)
            {
                std::cerr << "WaitForSingleObject(MutexAccess) failed: " << GetLastError() << std::endl;
                continue;
            }

            HANDLE hPipe = CreateFile(
                pipeName.c_str(),
                GENERIC_READ | GENERIC_WRITE,
                0,
                NULL,
                OPEN_EXISTING,
                0,
                NULL
            );

            if (hPipe == INVALID_HANDLE_VALUE)
            {
                std::cerr << "Cannot connect to pipe. Error: " << GetLastError() << "\n";
                ReleaseSemaphore(hMutex, 1, NULL);
                continue;
            }

            DWORD bytesWritten;
            char op = choice;
            if (!WriteFile(hPipe, &op, sizeof(op), &bytesWritten, NULL) || bytesWritten != sizeof(op))
            {
                std::cerr << "WriteFile(op) failed. Error: " << GetLastError() << "\n";
                CloseHandle(hPipe);
                ReleaseSemaphore(hMutex, 1, NULL);
                continue;
            }

            if (!WriteFile(hPipe, &id, sizeof(id), &bytesWritten, NULL) || bytesWritten != sizeof(id))
            {
                std::cerr << "WriteFile(id) failed. Error: " << GetLastError() << "\n";
                CloseHandle(hPipe);
                ReleaseSemaphore(hMutex, 1, NULL);
                continue;
            }

            ReleaseSemaphore(hMutex, 1, NULL);

            employee emp;
            ZeroMemory(&emp, sizeof(emp));
            DWORD bytesRead;
            if (!ReadFile(hPipe, reinterpret_cast<char*>(&emp), sizeof(emp), &bytesRead, NULL) || bytesRead != sizeof(emp))
            {
                std::cerr << "ReadFile(employee) failed. Error: " << GetLastError() << "\n";
                CloseHandle(hPipe);
                continue;
            }

            if (emp.num == -1)
            {
                std::cout << "Employee with ID " << id << " not found on server.\n";
                CloseHandle(hPipe);
                continue;
            }

            emp.name[9] = '\0';
            std::cout << "Employee received: ID = " << emp.num << ", Name = " << emp.name << ", Hours = " << emp.hours << "\n";

            if (choice == 'r')
            {
                std::cout << "Press Enter to finish reading...";
                std::string dummy;
                std::getline(std::cin, dummy);
                std::getline(std::cin, dummy);

                char finish = 'f';
                DWORD bw = 0;
                if (!WriteFile(hPipe, &finish, sizeof(finish), &bw, NULL) || bw != sizeof(finish))
                {
                    std::cerr << "WriteFile(finish) failed. Error: " << GetLastError() << "\n";
                }
            }
            else
            {
                std::cout << "Enter new name: ";
                std::cin >> emp.name;

                int len = strlen(emp.name);
                for (int i = len; i < 10; ++i)
                {
                    emp.name[i] = '\0';
                }

                std::cout << "Enter new hours: ";
                std::cin >> emp.hours;

                DWORD bw = 0;
                if (!WriteFile(hPipe, reinterpret_cast<char*>(&emp), sizeof(emp), &bw, NULL) || bw != sizeof(emp))
                {
                    std::cerr << "WriteFile(modified) failed. Error: " << GetLastError() << "\n";
                    CloseHandle(hPipe);
                    continue;
                }

                char finish = 'f';
                if (!WriteFile(hPipe, &finish, sizeof(finish), &bw, NULL) || bw != sizeof(finish))
                {
                    std::cerr << "WriteFile(finish) failed. Error: " << GetLastError() << "\n";
                }

                std::cout << "Modification sent.\n";
            }

            CloseHandle(hPipe);
        }
        else if (choice == 'e')
        {
            char op = 'e';

            WaitForSingleObject(hMutex, INFINITE);

            HANDLE hPipe = CreateFile(
                pipeName.c_str(),
                GENERIC_READ | GENERIC_WRITE,
                0,
                NULL,
                OPEN_EXISTING,
                0,
                NULL
            );

            if (hPipe != INVALID_HANDLE_VALUE)
            {
                DWORD bw;
                WriteFile(hPipe, &op, sizeof(op), &bw, NULL);
                CloseHandle(hPipe);
            }

            ReleaseSemaphore(hMutex, 1, NULL);
            break;
        }
    }

    std::ofstream logFile("client_log.txt", std::ios::app | std::ios::out);
    if (logFile)
    {
        logFile << "Client session finished successfully.\n";
        logFile.close();
    }

    std::ifstream readLog("client_log.txt");
    if (readLog)
    {
        std::string line;
        while (std::getline(readLog, line))
        {
            std::cout << line << "\n";
        }
        readLog.close();
    }

    return 0;
}
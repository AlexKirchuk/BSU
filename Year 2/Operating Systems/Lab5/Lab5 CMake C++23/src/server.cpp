#include "employee.h"
#include <memory>
#include <windows.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stdexcept>
#include <thread>
#include <mutex>
#include <cstring>

struct RecSem
{
    std::mutex readCountMtx;
    std::mutex resourceMtx;
    int readCount;
    RecSem() : readCount(0) {}
};

struct HandlerParam
{
    HANDLE hPipe;
    std::vector< std::shared_ptr<employee> >* pEmployees;
    std::vector<RecSem>* pRecSems;
    std::string fileName;
    int nEmployees;
};

static std::shared_ptr<employee> find_emp(std::vector< std::shared_ptr<employee> >& emps, int id)
{
    for (size_t i = 0; i < emps.size(); ++i)
    {
        if (emps[i]->num == id)
            return emps[i];
    }
    return std::shared_ptr<employee>();
}

void ClientHandler(HandlerParam* param)
{
    HANDLE hPipe = param->hPipe;
    std::vector< std::shared_ptr<employee> >& employees = *param->pEmployees;
    std::vector<RecSem>& recs = *param->pRecSems;
    int nEmployees = param->nEmployees;
    std::string fileName = param->fileName;

    while (true)
    {
        char op = 0;
        DWORD bytesRead = 0;
        BOOL ok = ReadFile(hPipe, &op, sizeof(op), &bytesRead, NULL);
        if (!ok || bytesRead == 0) break;

        if (op == 'e')
        {
            std::cout << "Client exited.\n";
            break;
        }
        if (op != 'r' && op != 'm') break;

        int id = 0;
        ok = ReadFile(hPipe, &id, sizeof(id), &bytesRead, NULL);
        if (!ok || bytesRead != sizeof(id)) break;

        int index = -1;
        std::shared_ptr<employee> empPtr;
        for (int i = 0; i < nEmployees; ++i)
        {
            if (employees[i]->num == id)
            {
                empPtr = employees[i];
                index = i;
                break;
            }
        }

        if (!empPtr)
        {
            employee nf;
            nf.num = -1;
            for (int j = 0; j < 10; ++j) nf.name[j] = '\0';
            nf.hours = 0.0;
            DWORD bw = 0;
            WriteFile(hPipe, reinterpret_cast<char*>(&nf), sizeof(nf), &bw, NULL);
            continue;
        }

        RecSem& rs = recs[index];

        if (op == 'r')
        {
            {
                std::lock_guard<std::mutex> lk(rs.readCountMtx);
                rs.readCount++;
                if (rs.readCount == 1)
                {
                    rs.resourceMtx.lock();
                }
            }

            employee outEmp;
            outEmp.num = empPtr->num;
            for (int k = 0; k < 10; ++k) outEmp.name[k] = empPtr->name[k];
            outEmp.hours = empPtr->hours;

            DWORD bw = 0;
            BOOL wok = WriteFile(hPipe, reinterpret_cast<char*>(&outEmp), sizeof(outEmp), &bw, NULL);
            if (!wok || bw != sizeof(outEmp))
            {
                {
                    std::lock_guard<std::mutex> lk(rs.readCountMtx);
                    rs.readCount--;
                    if (rs.readCount == 0)
                    {
                        rs.resourceMtx.unlock();
                    }
                }
                break;
            }

            char finish = 0;
            DWORD br = 0;
            BOOL fok = ReadFile(hPipe, &finish, sizeof(finish), &br, NULL);
            if (!fok || br == 0 || finish != 'f')
            {
                {
                    std::lock_guard<std::mutex> lk(rs.readCountMtx);
                    rs.readCount--;
                    if (rs.readCount == 0)
                    {
                        rs.resourceMtx.unlock();
                    }
                }
                if (!fok) break;
                continue;
            }

            {
                std::lock_guard<std::mutex> lk(rs.readCountMtx);
                rs.readCount--;
                if (rs.readCount == 0)
                {
                    rs.resourceMtx.unlock();
                }
            }
        }
        else if (op == 'm')
        {
            rs.resourceMtx.lock();

            employee outEmp;
            outEmp.num = empPtr->num;
            for (int k = 0; k < 10; ++k) outEmp.name[k] = empPtr->name[k];
            outEmp.hours = empPtr->hours;

            DWORD bw = 0;
            BOOL wok = WriteFile(hPipe, reinterpret_cast<char*>(&outEmp), sizeof(outEmp), &bw, NULL);
            if (!wok || bw != sizeof(outEmp))
            {
                rs.resourceMtx.unlock();
                break;
            }

            employee modified;
            std::memset(&modified, 0, sizeof(modified));
            DWORD br = 0;
            BOOL rok = ReadFile(hPipe, reinterpret_cast<char*>(&modified), sizeof(modified), &br, NULL);
            if (!rok || br != sizeof(modified))
            {
                rs.resourceMtx.unlock();
                break;
            }

            empPtr->hours = modified.hours;
            for (int k = 0; k < 10; ++k) empPtr->name[k] = modified.name[k];

            std::ofstream out(fileName.c_str(), std::ios::binary | std::ios::in | std::ios::out);
            if (out)
            {
                std::streampos pos = static_cast<std::streampos>(index) * static_cast<std::streampos>(sizeof(employee));
                out.seekp(pos, std::ios::beg);
                out.write(reinterpret_cast<char*>(empPtr.get()), sizeof(employee));
                out.close();
            }

            char finish = 0;
            DWORD brf = 0;
            BOOL fok = ReadFile(hPipe, &finish, sizeof(finish), &brf, NULL);
            rs.resourceMtx.unlock();
            if (!fok)
            {
                break;
            }
        }
    }

    FlushFileBuffers(hPipe);
    DisconnectNamedPipe(hPipe);
    CloseHandle(hPipe);

    delete param;
}

int main()
{
    try
    {
        std::string fileName;
        std::cout << "Enter binary file name: ";
        std::cin >> fileName;

        int nEmployees = 0;
        std::cout << "Enter number of employees: ";
        std::cin >> nEmployees;
        if (nEmployees <= 0)
        {
            std::cerr << "Number of employees must be > 0\n";
            return 1;
        }

        std::vector<std::shared_ptr<employee>> employees;
        employees.reserve(nEmployees);

        for (int i = 0; i < nEmployees; ++i)
        {
            std::shared_ptr<employee> p(new employee);
            std::cout << "Enter ID, name, hours: ";
            std::cin >> p->num >> p->name >> p->hours;
            int len = static_cast<int>(std::strlen(p->name));
            for (int j = len; j < 10; ++j) p->name[j] = '\0';
            employees.push_back(p);
        }

        {
            std::ofstream out(fileName.c_str(), std::ios::binary | std::ios::out);
            if (!out)
            {
                std::cerr << "Cannot create file\n";
                return 1;
            }
            for (int i = 0; i < nEmployees; ++i)
            {
                out.write(reinterpret_cast<char*>(employees[i].get()), sizeof(employee));
            }
            out.close();
        }

        std::cout << "Initial file contents:\n";
        for (int i = 0; i < nEmployees; ++i)
        {
            employee* e = employees[i].get();
            std::cout << "ID: " << e->num << ", Name: " << e->name << ", Hours: " << e->hours << std::endl;
        }

        HANDLE hGlobalMutex = CreateSemaphore(NULL, 1, 1, "MutexAccess");
        if (!hGlobalMutex)
        {
            std::cerr << "CreateSemaphore(MutexAccess) failed: " << GetLastError() << std::endl;
            return 1;
        }

        std::vector<RecSem> recs(nEmployees);
        for (int i = 0; i < nEmployees; ++i)
        {
            recs[i].readCount = 0;
        }

        int numClients = 0;
        std::cout << "Enter number of clients: ";
        std::cin >> numClients;
        if (numClients <= 0)
        {
            std::cerr << "Number of clients must be > 0\n";
            return 1;
        }

        std::vector<HANDLE> clientProcs;
        clientProcs.reserve(numClients);

        for (int i = 0; i < numClients; ++i)
        {
            STARTUPINFO si;
            PROCESS_INFORMATION pi;
            ZeroMemory(&si, sizeof(si));
            si.cb = sizeof(si);
            ZeroMemory(&pi, sizeof(pi));

            const char* cmdC = "client.exe";
            char cmdLine[256];
            std::strcpy(cmdLine, cmdC);

            BOOL ok = CreateProcess(NULL, cmdLine, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi);
            if (!ok)
            {
                std::cerr << "CreateProcess failed: " << GetLastError() << std::endl;
            }
            else
            {
                clientProcs.push_back(pi.hProcess);
                CloseHandle(pi.hThread);
            }
        }

        std::cout << "Launched " << clientProcs.size() << " clients.\n";

        while (true)
        {
            int running = -1;
            for (size_t i = 0; i < clientProcs.size(); ++i)
            {
                if (clientProcs[i] == NULL) continue;
                DWORD s = WaitForSingleObject(clientProcs[i], 0);
                if (s == WAIT_TIMEOUT) running++;
                else
                {
                    CloseHandle(clientProcs[i]);
                    clientProcs[i] = NULL;
                }
            }
            if (running == 0) break;

            HANDLE hPipe = CreateNamedPipe(
                "\\\\.\\pipe\\employee_pipe",
                PIPE_ACCESS_DUPLEX,
                PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT,
                PIPE_UNLIMITED_INSTANCES,
                512,
                512,
                0,
                NULL
            );

            if (hPipe == INVALID_HANDLE_VALUE)
            {
                std::cerr << "CreateNamedPipe failed: " << GetLastError() << std::endl;
                Sleep(100);
                continue;
            }

            BOOL connected;
            if (ConnectNamedPipe(hPipe, NULL)) connected = TRUE;
            else connected = (GetLastError() == ERROR_PIPE_CONNECTED);
            if (!connected)
            {
                CloseHandle(hPipe);
                continue;
            }

            HandlerParam* hp = new HandlerParam;
            hp->hPipe = hPipe;
            hp->pEmployees = &employees;
            hp->pRecSems = &recs;
            hp->fileName = fileName;
            hp->nEmployees = nEmployees;

            try
            {
                std::thread t(ClientHandler, hp);
                t.detach();
            }
            catch (...)
            {
                DisconnectNamedPipe(hPipe);
                CloseHandle(hPipe);
                delete hp;
                continue;
            }
        }

        for (size_t i = 0; i < clientProcs.size(); ++i)
        {
            if (clientProcs[i] != NULL)
            {
                WaitForSingleObject(clientProcs[i], INFINITE);
                CloseHandle(clientProcs[i]);
            }
        }

        std::cout << "All clients finished. Final records:\n";
        for (int i = 0; i < nEmployees; ++i)
        {
            employee* e = employees[i].get();
            std::cout << "ID: " << e->num << ", Name: " << e->name << ", Hours: " << e->hours << std::endl;
        }

        std::ofstream out(fileName.c_str(), std::ios::binary | std::ios::out);
        if (out)
        {
            for (int i = 0; i < nEmployees; ++i)
            {
                out.write(reinterpret_cast<char*>(employees[i].get()), sizeof(employee));
            }
            out.close();
        }

        CloseHandle(hGlobalMutex);
        std::cout << "Server finished. Press Enter to exit.\n";
        std::cin.get(); std::cin.get();
    }
    catch (const std::exception& ex)
    {
        std::cerr << "Exception: " << ex.what() << std::endl;
        return 1;
    }
    return 0;
}
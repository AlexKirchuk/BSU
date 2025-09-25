#include <average.h>
#include <windows.h>
#include <iostream>

extern HANDLE hConsoleMutex;

DWORD WINAPI average_thread(LPVOID param)
{
    Data* data = static_cast<Data*>(param);
    double sum = 0;

    for (int i = 0; i < data->size; i++)
    {
        sum += data->arr[i];
        Sleep(12);
    }

    data->average = sum / data->size;

    WaitForSingleObject(hConsoleMutex, INFINITE);
    std::cout << "Average: " << data->average << std::endl;
    ReleaseMutex(hConsoleMutex);

    return 0;
}

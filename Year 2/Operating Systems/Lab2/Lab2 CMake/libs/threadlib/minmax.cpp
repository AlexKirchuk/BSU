#include <minmax.h>
#include <windows.h>
#include <iostream>

extern HANDLE hConsoleMutex;

DWORD WINAPI min_max_thread(LPVOID param)
{
    Data* data = static_cast<Data*>(param);
    int min = data->arr[0];
    int max = data->arr[0];

    for (int i = 0; i < data->size; i++)
    {
        if (data->arr[i] < min) min = data->arr[i];
        Sleep(7);
        if (data->arr[i] > max) max = data->arr[i];
        Sleep(7);
    }

    data->min = min;
    data->max = max;

    WaitForSingleObject(hConsoleMutex, INFINITE);
    std::cout << "Minimum: " << min << std::endl << "Maximum: " << max << std::endl;
    ReleaseMutex(hConsoleMutex);
    
    return 0;
}

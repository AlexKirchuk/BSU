#include <boost/shared_ptr.hpp>
#include <minmax.h>
#include <windows.h>
#include <iostream>

extern HANDLE hConsoleMutex;

DWORD WINAPI min_max_thread(LPVOID param)
{
    const int TIME_TO_SLEEP = 7;
    boost::shared_ptr<Data>* pdata = static_cast<boost::shared_ptr<Data>*>(param);
    boost::shared_ptr<Data> data = *pdata;
    delete pdata; // necessary measure

    int min = data->arr[0];
    int max = data->arr[0];

    for (int i = 0; i < data->size; i++)
    {
        if (data->arr[i] < min) min = data->arr[i];
        Sleep(TIME_TO_SLEEP);
        if (data->arr[i] > max) max = data->arr[i];
        Sleep(TIME_TO_SLEEP);
    }

    data->min = min;
    data->max = max;

    WaitForSingleObject(hConsoleMutex, INFINITE);
    std::cout << "Minimum: " << min << std::endl << "Maximum: " << max << std::endl;
    ReleaseMutex(hConsoleMutex);
    
    return 0;
}
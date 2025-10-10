#include <boost/shared_ptr.hpp>
#include <average.h>
#include <windows.h>
#include <iostream>

extern HANDLE hConsoleMutex;

DWORD WINAPI average_thread(LPVOID param)
{
    const int TIME_TO_SLEEP = 12;
    boost::shared_ptr<Data>* pdata = static_cast<boost::shared_ptr<Data>*>(param);
    boost::shared_ptr<Data> data = *pdata;
    delete pdata; // necessary measure

    double sum = 0;

    for (int i = 0; i < data->size; i++)
    {
        sum += data->arr[i];
        Sleep(TIME_TO_SLEEP);
    }

    data->average = sum / data->size;

    WaitForSingleObject(hConsoleMutex, INFINITE);
    std::cout << "Average: " << data->average << std::endl;
    ReleaseMutex(hConsoleMutex);

    return 0;
}
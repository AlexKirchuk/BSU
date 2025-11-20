#include <boost/shared_ptr.hpp>
#include <data.h>
#include <minmax.h>
#include <average.h>
#include <iostream>

HANDLE hConsoleMutex = CreateMutex(NULL, FALSE, NULL);

DWORD WINAPI main_thread(LPVOID)
{
    int n;
    std::cout << "Enter array size: ";
    std::cin >> n;

    boost::shared_ptr<Data> data(new Data(n));

    std::cout << "Enter array elements: ";
    for (int i = 0; i < n; ++i)
    {
        int val;
        std::cin >> val;
        data->push(val);
    }

    HANDLE hMinMax = CreateThread(NULL, 0, min_max_thread, new boost::shared_ptr<Data>(data), 0, NULL);
    HANDLE hAverage = CreateThread(NULL, 0, average_thread, new boost::shared_ptr<Data>(data), 0, NULL);

    WaitForSingleObject(hMinMax, INFINITE);
    WaitForSingleObject(hAverage, INFINITE);

    CloseHandle(hMinMax);
    CloseHandle(hAverage);

    for (int i = 0; i < n; ++i)
    {
        if (data->arr[i] == data->min || data->arr[i] == data->max)
            data->arr[i] = static_cast<int>(data->average);
    }

    std::cout << "Modified array: ";
    for (int i = 0; i < n; ++i)
        std::cout << data->arr[i] << " ";
    std::cout << std::endl;

    return 0;
}

int main()
{
    HANDLE hMain = CreateThread(NULL, 0, main_thread, NULL, 0, NULL);
    WaitForSingleObject(hMain, INFINITE);
    CloseHandle(hMain);
    CloseHandle(hConsoleMutex);
	return 0;
}
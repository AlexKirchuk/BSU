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

    int* arr = new int[n];
    std::cout << "Enter array elements: ";
    for (int i = 0; i < n; i++) std::cin >> arr[i];

    Data data;
    data.arr = arr;
    data.size = n;

    HANDLE hMinMax = CreateThread(NULL, 0, min_max_thread, &data, 0, NULL);
    HANDLE hAverage = CreateThread(NULL, 0, average_thread, &data, 0, NULL);

    WaitForSingleObject(hMinMax, INFINITE);
    WaitForSingleObject(hAverage, INFINITE);

    CloseHandle(hMinMax);
    CloseHandle(hAverage);

    for (int i = 0; i < n; i++)
    {
        if (arr[i] == data.min || arr[i] == data.max)
            arr[i] = static_cast<int>(data.average);
    }

    std::cout << "Modified array: ";
    for (int i = 0; i < n; i++)
        std::cout << arr[i] << " ";
    std::cout << std::endl;

    delete[] arr;
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
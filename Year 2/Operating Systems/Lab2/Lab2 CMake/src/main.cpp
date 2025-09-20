#include <data.h>
#include <minmax.h>
#include <iostream>

int main()
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

    WaitForSingleObject(hMinMax, INFINITE);

    CloseHandle(hMinMax);
    
    delete[] arr;

	return 0;
}
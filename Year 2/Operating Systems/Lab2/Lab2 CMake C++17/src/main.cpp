#include <data.h>
#include <minmax.h>
#include <average.h>
#include <iostream>
#include <thread>
#include <mutex>

std::mutex console_mutex;

int main()
{
    int n;
    std::cout << "Enter array size: ";
    std::cin >> n;

    Data data;
    data.arr.resize(n);

    std::cout << "Enter array elements: ";
    for (int i = 0; i < n; i++)
        std::cin >> data.arr[i];
    
    std::thread t1(min_max_thread, std::ref(data));
    std::thread t2(average_thread, std::ref(data));

    t1.join();
    t2.join();

    for (int& value : data.arr)
    {
        if (value == data.min || value == data.max)
            value = static_cast<int>(data.average);
    }

    std::cout << "Modified array: ";
    for (int value : data.arr)
        std::cout << value << " ";
    std::cout << std::endl;

    return 0;
}
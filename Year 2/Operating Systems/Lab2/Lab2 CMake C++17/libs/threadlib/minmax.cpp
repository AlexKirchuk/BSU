#include <minmax.h>
#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>

extern std::mutex console_mutex;

void min_max_thread(Data& data)
{
    const int TIME_TO_SLEEP = 7;
    int min = data.arr[0];
    int max = data.arr[0];

    for (int value : data.arr)
    {
        if (value < min) min = value;
        std::this_thread::sleep_for(std::chrono::milliseconds(TIME_TO_SLEEP));
        if (value > max) max = value;
        std::this_thread::sleep_for(std::chrono::milliseconds(TIME_TO_SLEEP));
    }

    data.min = min;
    data.max = max;

    std::lock_guard<std::mutex> lock(console_mutex);
    std::cout << "Minimum: " << min << std::endl << "Maximum: " << max << std::endl;
}
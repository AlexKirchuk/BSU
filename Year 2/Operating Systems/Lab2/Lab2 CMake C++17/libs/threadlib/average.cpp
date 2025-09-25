#include "average.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>

extern std::mutex console_mutex;

void average_thread(Data& data)
{
    double sum = 0;
    for (int value : data.arr)
    {
        sum += value;
        std::this_thread::sleep_for(std::chrono::milliseconds(12));
    }
    data.average = sum / data.arr.size();

    std::lock_guard<std::mutex> lock(console_mutex);
    std::cout << "Average: " << data.average << std::endl;
}

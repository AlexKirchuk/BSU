/*
Lab #2
Topic: "Creating Threads."

Problem: Write a program for a console process consisting of three threads: main,
min_max, and average.
The main thread must perform the following actions:
1. Create an array of integers, the size and elements of which are entered from the console.
2. Create the min_max and average threads.
3. Wait for the min_max and average threads to complete.
4. Replace the maximum and minimum elements of the array with the average value of the elements.
Print the results to the console.
5. Terminate.
The min_max thread must perform the following actions:
1. Find the minimum and maximum elements of the array and print them to the console. After
each element comparison, sleep for 7 milliseconds.
2. Terminate.
The average thread should perform the following actions:
1. Find the arithmetic mean of the array elements and print it to the console.
After each summation operation, sleep for 12 milliseconds.
2. Terminate its work.
Notes:
1. To wait for the min_max and average threads to complete, use the function:
DWORD WaitForSingleObject(
HANDLE hHandle, // object handle
DWORD dwMilliseconds // sleep interval in milliseconds
);
where the second parameter is set to INFINITE. For example,
WaitForSingleObject(hAverage, INFINITE); // wait for the thread to complete
Here, hAverage is the handle of the average thread.
2. To sleep, use the function:
VOID Sleep(
DWORD dwMilliseconds // milliseconds
);
For example,
Sleep(12); // sleep for 12 milliseconds

Lab2 is made on C++17 CMake, Doctest Unit Tests
*/

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
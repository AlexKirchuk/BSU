/*
Lab #3.
Topic: "Thread Synchronization Using Bottom Sections and Events.
Deadlock Handling."

Problem: Write a program for a console process that consists of a main thread and a
thread marker for multiple instances.
The main thread must perform the following actions:
1. Allocate memory for an array of integers, the size of which is entered from the console.
2. Initialize the array elements to zero.
3. Request the number of thread markers to start.
4. Start a thread marker of a specified number of instances. As a parameter,
pass each instance of the thread marker its sequence number when it starts.
5. Signal the start of the marker for all threads.
6. Perform the following actions in a loop:
6.1. Wait until all thread markers signal that they cannot continue their work. 6.2. Print the array array to the console.
6.3. Request the thread marker's sequence number from the console; it will signal the completion of its work.
6.4. Send the thread marker, whose number was obtained from institution 6.3, a signal to
complete its work.
6.5. Wait for the thread marker to complete its work; a signal to
complete work in construction 6.4 was sent.
6.6. Print the array array to the console.
6.7. Send a signal for the remaining threads of the marker to continue their work.
7. Complete its work after all thread markers have completed their work.
The marker thread must perform the following actions:
1. Start work upon a signal from the main thread.
2. Initialize the generation of a random number sequence. To do this,
use the srand function, which passes its
sequence number as an argument. 3. Run cyclically, performing the following actions in each loop:
3.1. Generate a random number using the rand function.
3.2. Divide this number modulo the array dimension.
3.3. If the array element whose index calculates the division result results in
one of the following actions:
3.3.1. Sleep for 5 milliseconds.
3.3.2. Set the element whose index has been calculated to its own ordered number.
3.3.3. Sleep for 5 milliseconds.
3.3.4. Continue execution of loop 3.
3.4. On failure:
3.4.1. Print this information to the console:
- its ordered number;
- the number of marked elements;
- the index of the array element that cannot be marked.
3.4.2. Signal the main thread that it is unable to continue its work.
3.4.3. Wait for a response signal to continue or complete work on the main thread.

4. If a signal to complete work is received, configure the following actions:
4.1. Fill all array elements it marked with zeros.
4.2. Complete the work.
5. If a signal to continue work is received, continue execution of the loop.
step 3.

Lab3 is made on C++11 CMake, Catch2 Unit Tests
*/

#include <array.h>
#include <marker.h>
#include <iostream>
#include <vector>
#include <memory>
#include <thread>
#include <mutex>
#include <condition_variable>

int main()
{
    std::mutex startMtx;
    std::condition_variable startCv;
    bool startFlag = false;

    int sizeArr = 0;
    std::cout << "Enter array size: ";
    std::cin >> sizeArr;

    auto arr = std::make_shared<Array>(sizeArr);

    int markerCount = 0;
    std::cout << "Enter number of marker threads: ";
    std::cin >> markerCount;

    std::vector<std::shared_ptr<MarkerData>> markers(markerCount);
    std::vector<std::thread> threads(markerCount);

    for (int i = 0; i < markerCount; ++i)
    {
        markers[i] = std::make_shared<MarkerData>();
        markers[i]->id = i + 1;
        markers[i]->terminate = false;
        markers[i]->active = true;
        markers[i]->sharedArray = arr;
        markers[i]->blocked = false;

        threads[i] = std::thread(MarkerProc, markers[i],
            std::ref(startMtx),
            std::ref(startCv),
            std::ref(startFlag));
    }

    {
        std::lock_guard<std::mutex> lock(startMtx);
        startFlag = true;
    }
    startCv.notify_all();

    while (true)
    {
        for (auto& m : markers)
        {
            std::unique_lock<std::mutex> lock(m->mtx);
            m->cv.wait(lock, [&] { return m->blocked || !m->active; });
        }

        std::cout << std::endl << "All marker threads are blocked!" << std::endl;
        arr->print();

        int num;
        std::cout << "Enter marker number to terminate: ";
        std::cin >> num;

        if (num < 1 || num > markerCount || !markers[num - 1]->active)
        {
            std::cout << "Invalid choice!" << std::endl;
            continue;
        }

        markers[num - 1]->terminate = true;
        {
            std::lock_guard<std::mutex> lock(markers[num - 1]->mtx);
            markers[num - 1]->blocked = false;
        }
        markers[num - 1]->cv.notify_one();

        threads[num - 1].join();
        arr->print();

        for (auto& m : markers)
        {
            if (m->active)
            {
                std::lock_guard<std::mutex> lock(m->mtx);
                m->blocked = false;
            }
            m->cv.notify_one();
        }

        bool allDone = true;
        for (auto& m : markers)
            if (m->active) allDone = false;

        if (allDone) break;
    }

    std::cout << std::endl << "All marker threads have finished." << std::endl;
    arr->print();

    return 0;
}
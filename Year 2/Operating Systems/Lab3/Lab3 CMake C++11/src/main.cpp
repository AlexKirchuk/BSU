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
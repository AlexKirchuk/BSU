#include <marker.h>
#include <iostream>
#include <chrono>
#include <random>

void MarkerProc(std::shared_ptr<MarkerData> data,
    std::mutex& startMtx,
    std::condition_variable& startCv,
    bool& startFlag)
{
    {
        std::unique_lock<std::mutex> lock(startMtx);
        startCv.wait(lock, [&startFlag] { return startFlag; });
    }

    const int TIME_TO_SLEEP = 5;
    const int MIN_TIME_TO_SLEEP = 1;
    std::uniform_int_distribution<int> dist(0, data->sharedArray->getSize() - 1);
    std::mt19937 rng(data->id);

    while (true)
    {
        int index = dist(rng);
        bool marked = false;

        if (data->sharedArray->get(index) == 0)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(TIME_TO_SLEEP));
            data->sharedArray->set(index, data->id);
            std::this_thread::sleep_for(std::chrono::milliseconds(TIME_TO_SLEEP));
            marked = true;
        }

        if (marked)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(MIN_TIME_TO_SLEEP));
            continue;
        }
        else
        {
            int count = 0;
            for (int i = 0; i < data->sharedArray->getSize(); ++i)
                if (data->sharedArray->get(i) == data->id)
                    ++count;

            {
                std::lock_guard<std::mutex> lock(data->coutMtx);
                std::cout << "Marker #" << data->id
                    << " (marked elements: " << count << ")"
                    << " is blocked at index " << index << std::endl;
            }

            {
                std::lock_guard<std::mutex> lock(data->mtx);
                data->blocked = true;
            }
            data->cv.notify_one();

            std::unique_lock<std::mutex> lock(data->mtx);
            data->cv.wait(lock, [&] { return !data->blocked || data->terminate; });

            if (data->terminate)
            {
                data->sharedArray->clearValue(data->id);
                std::cout << "Marker #" << data->id << " has finished." << std::endl;
                data->active = false;
                return;
            }
        }
    }
}

std::mutex MarkerData::coutMtx;
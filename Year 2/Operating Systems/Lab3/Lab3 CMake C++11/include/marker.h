#ifndef MARKER_H
#define MARKER_H

#include <array.h>
#include <memory>
#include <thread>
#include <mutex>
#include <condition_variable>

struct MarkerData
{
    int id;
    bool terminate;
    bool active;
    std::shared_ptr<Array> sharedArray;
    std::mutex mtx;
    std::condition_variable cv;
    bool blocked;

    static std::mutex coutMtx;
};

void MarkerProc(std::shared_ptr<MarkerData> data,
    std::mutex& startMtx,
    std::condition_variable& startCv,
    bool& startFlag);

#endif
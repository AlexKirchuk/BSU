#include <windows.h>
#include <array.h>
#include <marker.h>
#include <iostream>

HANDLE startEvent;
MarkerData* markers = 0;
int markerCount = 0;

int main()
{
    int sizeArr = 0;
    std::cout << "Enter array size: ";
    std::cin >> sizeArr;

    Array arr(sizeArr);

    std::cout << "Enter amount of marker threads: ";
    std::cin >> markerCount;

    markers = new MarkerData[markerCount];
    startEvent = CreateEvent(0, TRUE, FALSE, 0);

    for (int i = 0; i < markerCount; ++i)
    {
        markers[i].id = i + 1;
        markers[i].blockedEvent = CreateEvent(0, TRUE, FALSE, 0);
        markers[i].controlEvent = CreateEvent(0, FALSE, FALSE, 0);
        markers[i].terminate = false;
        markers[i].active = true;
        markers[i].sharedArray = &arr;

        markers[i].threadHandle = CreateThread(
            0, 0, MarkerProc, static_cast<LPVOID>(&markers[i]), 0, 0
        );
    }

    SetEvent(startEvent);

    while (true)
    {
        int activeCount = 0;
        for (int i = 0; i < markerCount; ++i)
            if (markers[i].active)
                ++activeCount;

        if (activeCount == 0)
            break;

        HANDLE* activeEvents = new HANDLE[activeCount];
        int idx = 0;
        for (int i = 0; i < markerCount; ++i)
            if (markers[i].active)
                activeEvents[idx++] = markers[i].blockedEvent;

        WaitForMultipleObjects(activeCount, activeEvents, TRUE, INFINITE);
        delete[] activeEvents;

        std::cout << std::endl << "All threads are blocked!" << std::endl;
        arr.print();

        int num;
        std::cout << "Enter thread number for finishing: ";
        std::cin >> num;

        if (num < 1 || num > markerCount || !markers[num - 1].active)
        {
            std::cout << "Error!" << std::endl;
            continue;
        }

        markers[num - 1].terminate = true;
        SetEvent(markers[num - 1].controlEvent);
        WaitForSingleObject(markers[num - 1].threadHandle, INFINITE);

        arr.print();

        for (int i = 0; i < markerCount; ++i)
        {
            if (markers[i].active)
            {
                ResetEvent(markers[i].blockedEvent);
                SetEvent(markers[i].controlEvent);
            }
        }
    }

    std::cout << std::endl << "All threads finished." << std::endl;
    arr.print();

    for (int i = 0; i < markerCount; ++i) {
        CloseHandle(markers[i].blockedEvent);
        CloseHandle(markers[i].controlEvent);
        CloseHandle(markers[i].threadHandle);
    }

    CloseHandle(startEvent);
    delete[] markers;

    std::cout << "End.";
    return 0;
}

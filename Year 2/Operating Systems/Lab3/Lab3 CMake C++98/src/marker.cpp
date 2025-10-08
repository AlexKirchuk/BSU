#include <stdlib.h>
#include <marker.h>
#include <iostream>

extern HANDLE startEvent;
extern CRITICAL_SECTION coutCS;

DWORD WINAPI MarkerProc(LPVOID param)
{
    const int TIME_TO_SLEEP = 5;
    const int MIN_TIME_TO_SLEEP = 1;
    MarkerData* data = static_cast<MarkerData*>(param);
    boost::shared_ptr<Array> arr = data->sharedArray;

    WaitForSingleObject(startEvent, INFINITE);
    srand(data->id);

    while (true)
    {
        int index = rand() % arr->getSize();
        bool marked = false;

        if (arr->get(index) == 0)
        {
            Sleep(TIME_TO_SLEEP);
            arr->set(index, data->id);
            Sleep(TIME_TO_SLEEP);
            marked = true;
        }

        if (marked)
        {
            Sleep(MIN_TIME_TO_SLEEP);
            continue;
        }
        else
        {
            int count = 0;
            for (int i = 0; i < arr->getSize(); ++i)
                if (arr->get(i) == data->id)
                    ++count;

            EnterCriticalSection(&coutCS);
            std::cout << "Marker #" << data->id
                << " (marked elements: " << count << ")"
                << " is blocked at index " << index << std::endl;
            LeaveCriticalSection(&coutCS);

            SetEvent(data->blockedEvent);
            WaitForSingleObject(data->controlEvent, INFINITE);

            if (data->terminate)
            {
                arr->clearValue(data->id);
                std::cout << "Marker #" << data->id << " has finished." << std::endl;
                data->active = false;
                return 0;
            }
        }
    }

    return 0;
}
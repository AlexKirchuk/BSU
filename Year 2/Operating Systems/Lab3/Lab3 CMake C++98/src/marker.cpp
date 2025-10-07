#include <stdlib.h>
#include <marker.h>
#include <iostream>

extern HANDLE startEvent;

DWORD WINAPI MarkerProc(LPVOID param)
{
    MarkerData* data = static_cast<MarkerData*>(param);
    Array* arr = data->sharedArray;

    WaitForSingleObject(startEvent, INFINITE);
    srand(static_cast<int>(data->id));

    while (true)
    {
        int index = rand() % arr->getSize();
        bool marked = false;

        if (arr->get(index) == 0)
        {
            Sleep(5);
            arr->set(index, data->id);
            Sleep(5);
            marked = true;
        }

        if (marked)
        {
            Sleep(1);
            continue;
        }
        else
        {
            int count = 0;
            for (int i = 0; i < arr->getSize(); ++i)
                if (arr->get(i) == data->id)
                    ++count;

            std::cout << "Marker #" << data->id
                << ", elements marked: " << count
                << " can't mark index " << index << std::endl;

            SetEvent(data->blockedEvent);
            WaitForSingleObject(data->controlEvent, INFINITE);

            if (data->terminate)
            {
                arr->clearValue(data->id);
                std::cout << "Marker #" << data->id << " finishes." << std::endl;
                data->active = false;
                return 0;
            }
        }
    }

    return 0;
}
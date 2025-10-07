#ifndef MARKER_H
#define MARKER_H

#include <windows.h>
#include <array.h>

struct MarkerData
{
    int id;
    HANDLE blockedEvent;
    HANDLE controlEvent;
    HANDLE threadHandle;
    bool terminate;
    bool active;
    Array* sharedArray;
};

DWORD WINAPI MarkerProc(LPVOID param);

#endif
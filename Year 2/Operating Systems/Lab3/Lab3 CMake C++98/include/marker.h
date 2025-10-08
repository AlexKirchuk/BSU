#ifndef MARKER_H
#define MARKER_H

#include <boost/shared_ptr.hpp>
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
    boost::shared_ptr<Array> sharedArray;
};

DWORD WINAPI MarkerProc(LPVOID param);

#endif
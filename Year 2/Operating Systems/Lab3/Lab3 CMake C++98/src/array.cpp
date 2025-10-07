#include <array.h>

Array::Array(int n) : size(n)
{
    data = new int[n];
    for (int i = 0; i < n; ++i)
        data[i] = 0;
    InitializeCriticalSection(&cs);
}

Array::~Array()
{
    DeleteCriticalSection(&cs);
    delete[] data;
}

int Array::getSize()
{ return size; }

int Array::get(int index)
{
    EnterCriticalSection(&cs);
    int val = data[index];
    LeaveCriticalSection(&cs);
    return val;
}

void Array::set(int index, int value)
{
    EnterCriticalSection(&cs);
    data[index] = value;
    LeaveCriticalSection(&cs);
}

void Array::clearValue(int value)
{
    EnterCriticalSection(&cs);
    for (int i = 0; i < size; ++i)
        if (data[i] == value)
            data[i] = 0;
    LeaveCriticalSection(&cs);
}

void Array::print()
{
    EnterCriticalSection(&cs);
    std::cout << "Array: ";
    for (int i = 0; i < size; ++i)
        std::cout << data[i] << " ";
    std::cout << std::endl;
    LeaveCriticalSection(&cs);
}
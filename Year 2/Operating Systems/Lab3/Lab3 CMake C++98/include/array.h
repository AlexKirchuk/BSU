#ifndef ARRAY_H
#define ARRAY_H

#include <windows.h>
#include <iostream>

class Array {
private:
    int* data;
    int size;
    CRITICAL_SECTION cs;

public:
    Array(int n);
    ~Array();

    int getSize();
    int get(int index);
    void set(int index, int value);
    void clearValue(int value);
    void print();
};

#endif
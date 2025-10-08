#ifndef ARRAY_H
#define ARRAY_H

#include <iostream>
#include <vector>
#include <mutex>

class Array
{
private:
    std::vector<int> data;
    std::mutex mtx;

public:
    explicit Array(int n);
    
    int getSize();
    int get(int index);
    void set(int index, int value);
    void clearValue(int value);
    void print();
};

#endif
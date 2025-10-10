#ifndef DATA_H
#define DATA_H

#include <boost/scoped_array.hpp>

struct Data
{
    boost::scoped_array<int> arr;
    int size;
    int min;
    int max;
    double average;

    explicit Data(int n = 0);
    void push(int value);

    // Copying is prohibited
private:
    Data(const Data&);
    Data& operator=(const Data&);
};

#endif
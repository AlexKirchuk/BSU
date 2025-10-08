#include <array.h>

Array::Array(int n) : data(n, 0) {}

int Array::getSize()
{
    return data.size();
}

int Array::get(int index)
{
    std::lock_guard<std::mutex> lock(mtx);
    return data[index];
}

void Array::set(int index, int value)
{
    std::lock_guard<std::mutex> lock(mtx);
    data[index] = value;
}

void Array::clearValue(int value)
{
    std::lock_guard<std::mutex> lock(mtx);
    for (auto& v : data)
        if (v == value)
            v = 0;
}

void Array::print()
{
    std::lock_guard<std::mutex> lock(mtx);
    std::cout << "Array: ";
    for (auto v : data)
        std::cout << v << " ";
    std::cout << std::endl;
}
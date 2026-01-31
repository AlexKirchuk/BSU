#include "my_array.h"

MyArray::MyArray() : arr(nullptr)
{
    size = 1;
    arr = new int[size];
    arr[0] = 0;
}

MyArray::MyArray(const int size) : arr(nullptr)
{
    this->size = size;
    arr = new int[size];
    for (int i = 0; i < size; i++)
    {
        arr[i] = 0;
    }
}

MyArray::MyArray(const MyArray& other)
{
    this->size = other.size;
    this->arr = new int[other.size];
    for (int i = 0; i < other.size; i++)
    {
        this->arr[i] = other.arr[i];
    }
}

MyArray::~MyArray()
{
    std::cout << std::endl << "(Destructor called for MyArray class)" << std::endl;
    delete[] arr;
}

void MyArray::shellSort() const
{
    int k;
    for (int i = size / 2; i > 0; i /= 2)
    {
        for (int j = i; j < size; j++)
        {
            const int tmp = arr[j];
            for (k = j; k >= i; k -= i)
            {
                if (tmp < arr[k - i])
                    arr[k] = arr[k - i];
                else
                    break;
            }
            arr[k] = tmp;
        }
    }
}

int& MyArray::operator[](const int index) const
{
    return arr[index];
}

std::istream& operator>>(std::istream& in, const MyArray& arr)
{
    std::cout << "Enter elements: " << std::endl;
    for (int i = 0; i < arr.size; i++)
    {
        in >> arr.arr[i];
    }
    return in;
}

std::ostream& operator<<(std::ostream& out, const MyArray& arr)
{
    for (int i = 0; i < arr.size; i++)
    {
        out << arr.arr[i] << " ";
    }
    out << std::endl;
    return out;
}
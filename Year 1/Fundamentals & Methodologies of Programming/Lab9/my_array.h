#ifndef LAB9_MYARRAY_H
#define LAB9_MYARRAY_H

#include <iostream>

class MyArray {
    int size;
    int* arr;
public:
    MyArray();
    explicit MyArray(int size);
    MyArray(const MyArray& other);
    ~MyArray();
    void shellSort() const;
    int& operator[](int index) const;
    friend std::istream& operator>>(std::istream& in, const MyArray& arr);
    friend std::ostream& operator<<(std::ostream& out, const  MyArray& arr);
};

#endif //LAB9_MYARRAY_H
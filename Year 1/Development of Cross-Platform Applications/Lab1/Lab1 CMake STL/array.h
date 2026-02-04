#ifndef LAB1_CMAKE_STL_ARRAY_H
#define LAB1_CMAKE_STL_ARRAY_H

#include <iostream>
#include <vector>

class Array {
    std::vector<int>v;
public:
    Array();
    explicit Array(const std::vector<int>& v);
    ~Array();
    static void printTasks();
    void isArithmetic() const;
    void isGeometric() const;
    void uniqueSort();
    void intersect(const Array& v1) const;
    void unique();
    friend std::istream& operator>>(std::istream& in, Array& v);
    friend std::ostream& operator<<(std::ostream& out, const Array& v);
};

#endif //LAB1_CMAKE_STL_ARRAY_H
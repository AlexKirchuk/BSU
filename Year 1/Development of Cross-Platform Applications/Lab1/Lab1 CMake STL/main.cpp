#include "number.h"
#include "array.h"
#include "matrix.h"
#include <iostream>

int main()
{
    // Number
    Number::printTasks();
    Number num1, num21, num3, num4;

    std::cout << "1. ";
    std::cin >> num1;
    num1.sumCube();

    std::cout << "2. No input required ";
    Number::pairOf5();

    std::cout << "2.1. ";
    std::cin >> num21;
    num21.dividers();

    std::cout << "3. ";
    std::cin >> num3;
    num3.pairProd();

    std::cout << "4. ";
    std::cin >> num4;
    num4.kaprekar();

    // Array
    Array::printTasks();
    Array a1, a2, a3, a31, a4;

    std::cout << "1. ";
    std::cin >> a1;
    a1.isArithmetic();
    a1.isGeometric();

    std::cout << "2. ";
    std::cin >> a2;
    a2.uniqueSort();

    std::cout << "3. ";
    std::cin >> a3 >> a31;
    a3.intersect(a31);

    std::cout << "4. ";
    std::cin >> a4;
    a4.unique();

    // Matrix
    Matrix::printTasks();
    Matrix ma1, ma2;

    std::cout << "1. ";
    std::cin >> ma1;
    std::cout << ma1;
    ma1.pos();

    std::cout << "2. ";
    std::cin >> ma2;
    std::cout << ma2;
    ma2.smooth();

    return 0;
}
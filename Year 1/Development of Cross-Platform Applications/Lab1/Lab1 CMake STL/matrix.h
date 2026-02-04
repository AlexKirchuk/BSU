#ifndef LAB1_CMAKE_STL_MATRIX_H
#define LAB1_CMAKE_STL_MATRIX_H

#include <iostream>
#include <vector>

class Matrix {
    std::vector<std::vector<double>>ma;
public:
    Matrix();
    explicit Matrix(const std::vector<std::vector<double>>& ma);
    ~Matrix();
    static void printTasks();
    void pos() const;
    void smooth();
    friend std::istream& operator>>(std::istream& in, Matrix& ma);
    friend std::ostream& operator<<(std::ostream& out, const  Matrix& ma);
};

#endif //LAB1_CMAKE_STL_MATRIX_H
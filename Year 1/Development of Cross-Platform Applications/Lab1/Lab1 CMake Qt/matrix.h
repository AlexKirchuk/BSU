#ifndef LAB1_CMAKE_STL_MATRIX_H
#define LAB1_CMAKE_STL_MATRIX_H

#include <QTextStream>
#include <QVector>

class Matrix {
    QVector<QVector<double>>ma;
public:
    Matrix();
    explicit Matrix(const QVector<QVector<double>>& ma);
    ~Matrix();
    static void printTasks();
    void pos() const;
    void smooth();
    friend QTextStream& operator>>(QTextStream& in, Matrix& ma);
    friend QTextStream& operator<<(QTextStream& out, const  Matrix& ma);
};

#endif //LAB1_CMAKE_STL_MATRIX_H
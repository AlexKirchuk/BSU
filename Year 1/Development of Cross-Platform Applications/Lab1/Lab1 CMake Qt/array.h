#ifndef LAB1_CMAKE_STL_ARRAY_H
#define LAB1_CMAKE_STL_ARRAY_H

#include <QTextStream>
#include <QVector>

class Array {
    QVector<int>v;
public:
    Array();
    explicit Array(const QVector<int>& v);
    ~Array();
    static void printTasks();
    void isArithmetic() const;
    void isGeometric() const;
    void uniqueSort();
    void intersect(const Array& v1) const;
    void unique();
    friend QTextStream& operator>>(QTextStream& in, Array& v);
    friend QTextStream& operator<<(QTextStream& out, const Array& v);
};

#endif //LAB1_CMAKE_STL_ARRAY_H
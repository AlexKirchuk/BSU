#include "number.h"
#include "array.h"
#include "matrix.h"
#include <QCoreApplication>
#include <QDebug>

int main(int argc, char* argv[])
{
    QCoreApplication a(argc, argv);
    QTextStream in(stdin);

    // Number
    Number::printTasks();
    Number num1, num21, num3, num4;

    qDebug() << "1. ";
    in >> num1;
    num1.sumCube();

    qDebug() << "2. No input required ";
    Number::pairOf5();

    qDebug() << "2.1. ";
    in >> num21;
    num21.dividers();

    qDebug() << "3. ";
    in >> num3;
    num3.pairProd();

    qDebug() << "4. ";
    in >> num4;
    num4.kaprekar();

    // Array
    Array::printTasks();
    Array a1, a2, a3, a31, a4;

    qDebug() << "1. ";
    in >> a1;
    a1.isArithmetic();
    a1.isGeometric();

    qDebug() << "2. ";
    in >> a2;
    a2.uniqueSort();

    qDebug() << "3. ";
    in >> a3 >> a31;
    a3.intersect(a31);

    qDebug() << "4. ";
    in >> a4;
    a4.unique();

    // Matrix
    Matrix::printTasks();
    Matrix ma1, ma2;

    qDebug() << "1. ";
    in >> ma1;
    ma1.pos();

    qDebug() << "2. ";
    in >> ma2;
    ma2.smooth();

    return QCoreApplication::exec();
}
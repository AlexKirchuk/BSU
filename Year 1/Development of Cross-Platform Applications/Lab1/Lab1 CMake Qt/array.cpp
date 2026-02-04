#include "array.h"
#include <QDebug>

Array::Array() = default;

Array::Array(const QVector<int>& v)
{
    this->v = v;
}

Array::~Array() = default;

void Array::printTasks()
{
    qDebug() << Qt::endl;
    qDebug() << "Task conditions:" << Qt::endl;
    qDebug() << "1. Check whether the elements of an integer sequence A = (ai), i = 1..n, n <= 100, form an arithmetic or geometric progression. If yes, output the difference (denominator) of the progression; if no, output a message." << Qt::endl;
    qDebug() << "2. Transform the sequence A = (ai), i = 1..n, n <= 100, by placing all numbers whose digit sum is even first, then the others, preserving the order." << Qt::endl;
    qDebug() << "3. Given two non-decreasing arrays X = (xi), i = 1..n, n <= 10, and Y = (yi), i = 1..m, m <= 10. Find their 'intersection', i.e., an array Z containing their common elements, where the multiplicity of each element in array Z equals the minimum of its multiplicities in arrays X and Y. The number of operations should be of the order m + n." << Qt::endl;
    qDebug() << "4. Given an integer sequence A = (ai), i = 1..n, n <= 100. Find the number of distinct numbers among the elements of this array. (The number of operations should be of the order n*n)." << Qt::endl;
}

void Array::isArithmetic() const
{
    bool ar = true;
    const int d = v[1] - v[0];
    for (int i = 0; i < v.size() - 1; i++)
    {
        if (v[i + 1] - v[i] != d)
        {
            ar = false;
            break;
        }
    }
    if (ar && v.size() != 1 && v.size() != 2 && d != 0)
    {
        qDebug() << "The sequence is an arithmetic progression" << Qt::endl;
        qDebug() << "Common difference d = " << d << Qt::endl;
    }
    else if (d != 0) qDebug() << "The sequence is not an arithmetic progression" << Qt::endl;
}

void Array::isGeometric() const
{
    bool geom = true;
    const double q = static_cast<double>(v[1]) / v[0];
    for (int i = 0; i < v.size() - 1; i++)
    {
        if (static_cast<double>(v[i + 1]) / v[i] != q)
        {
            geom = false;
            break;
        }
    }
    if (geom && v.size() != 1 && v.size() != 2 && q != 1 && q != 0)
    {
        qDebug() << "The sequence is a geometric progression" << Qt::endl;
        qDebug() << "Common ratio q = " << q << Qt::endl;
    }
    else if (q != 1) qDebug() << "The sequence is not a geometric progression" << Qt::endl;
    else qDebug() << "The sequence is stationary" << Qt::endl;
}

void Array::uniqueSort()
{
    int sumJ = 0, sumJMinusOne = 0;
    for (int i = 0; i < v.size(); i++)
        for (int j = 1; j < v.size(); j++)
        {
            int vj = v[j];
            while (vj > 0)
            {
                vj += vj % 10;
                vj /= 10;
            }
            int VJMinusOne = v[j - 1];
            while (VJMinusOne > 0)
            {
                sumJMinusOne += VJMinusOne % 10;
                VJMinusOne /= 10;
            }
            if (sumJ % 2 == 0 && sumJMinusOne % 2 != 0)
            {
                const int temp = v[j - 1];
                v[j - 1] = v[j];
                v[j] = temp;
            }
            sumJ = 0;
            sumJMinusOne = 0;
        }
    qDebug() << "Reordered array:";
    for (const int obj : v)
    {
        qDebug() << obj << " ";
    }
    qDebug() << Qt::endl;
}

void Array::intersect(const Array& v1) const
{
    QVector<int>v2;
    int minCount;
    for (int i = 0, j = 0; i < v.size() and j < v1.v.size(); )
    {
        if (v[i] < v1.v[j])
        {
            i++;
            continue;
        }
        if (v[i] > v1.v[j])
        {
            j++;
            continue;
        }
        int countV = 0;
        int countV1 = 0;
        int value = v[i];
        while (i < v.size() && v[i] == value)
        {
            countV++;
            i++;
        }
        while (j < v1.v.size() && v1.v[j] == value)
        {
            countV1++;
            j++;
        }
        if (countV > countV1) minCount = countV1;
        else minCount = countV;
        for (int k = 0; k < minCount; k++)
        {
            v2.push_back(value);
        }
    }
    qDebug() << "Intersection:";
    if (v2.empty()) qDebug() << "Empty set";
    for (const int obj : v2)
    {
        qDebug() << obj << " ";
    }
    qDebug() << Qt::endl;
}

void Array::unique()
{
    v.push_back(-1);
    int count = 0;
    for (int i = 0; i < v.size() - 1; )
    {
        while (v[i] == v[i + 1] && i < v.size() - 2) i++;
        count++;
        i++;
    }
    v.pop_back();
    qDebug() << "Number of distinct elements: " << count << Qt::endl;
}

QTextStream& operator>>(QTextStream& in, Array& v)
{
    int temp, size;
    qDebug() << "Enter number of elements: ";
    in >> size;
    qDebug() << "Enter the array elements: " << Qt::endl;
    for (int i = 0; i < size; i++)
    {
        in >> temp;
        v.v.push_back(temp);
    }
    return in;
}

QTextStream& operator<<(QTextStream& out, const Array& v)
{
    for (const int obj : v.v)
    {
        out << obj;
    }
    return out;
}
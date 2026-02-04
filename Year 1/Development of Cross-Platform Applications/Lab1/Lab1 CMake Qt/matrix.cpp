#include "matrix.h"
#include <QDebug>

Matrix::Matrix() = default;

Matrix::Matrix(const QVector<QVector<double>>& ma)
{
    this->ma = ma;
}

Matrix::~Matrix() = default;

void Matrix::printTasks()
{
    qDebug() << Qt::endl;
    qDebug() << "Task conditions:" << Qt::endl;
    qDebug() << "1. Find the row numbers of matrix A = (aij), i = 1..n, j = 1..m, n, m <= 150, that contain the maximum number of positive elements." << Qt::endl;
    qDebug() << "2. Neighbors of element aij in a matrix are defined as elements akg, where i - 1 < k < i + 1, j - 1 < g < j + 1, (k, g) != (i, j). The matrix smoothing operation produces a new matrix of the same size, where each element is obtained as the arithmetic mean of the available neighbors of the corresponding element in the original matrix. Construct the result of smoothing a given real matrix." << Qt::endl;
}

void Matrix::pos() const
{
    QVector<int>count;
    int max = 0;
    for (int i = 0; i < ma.size(); i++)
    {
        count.push_back(0);
    }
    for (int i = 0; i < ma.size(); i++)
    {
        for (int j = 0; j < ma[i].size(); j++)
        {
            if (ma[i][j] > 0)
            {
                count[i]++;
            }
        }
        if (count[i] > max)
        {
            max = count[i];
        }
    }
    if (max > 0)
    {
        qDebug() << "Maximum number of positive elements: " << max << Qt::endl;
        qDebug() << "Row indices with maximum positives: ";
        for (int i = 0; i < ma.size(); i++)
        {
            if (count[i] == max) qDebug() << i + 1 << ' ';
        }
        qDebug() << Qt::endl;
    }
    else qDebug() << "All matrix elements are non-positive." << Qt::endl;
}

void Matrix::smooth()
{
    QVector<QVector<double>> maCopy = ma;
    double sum = 0;
    int count = 0;
    for (int i = 0; i < ma.size(); i++)
    {
        for (int j = 0; j < ma[i].size(); j++)
        {
            for (int k = i - 1; k <= i + 1; k++)
            {
                for (int h = j - 1; h <= j + 1; h++)
                {
                    if (k >= 0 && k < ma.size() && h >= 0 && h < ma[i].size() && !(k == i && h == j))
                    {
                        sum += ma[k][h];
                        count++;
                    }
                }
            }
            maCopy[i][j] = sum / count;
            sum = 0;
            count = 0;
        }
    }
    ma = maCopy;

    qDebug() << Qt::endl << "Smooth matrix: " << Qt::endl;
    for (const auto & v : ma)
    {
        for (const double obj : v)
        {
            qDebug() << obj << " ";
        }
        qDebug() << Qt::endl;
    }
}

QTextStream& operator>>(QTextStream& in, Matrix& ma)
{
    int temp, rows, cols;
    QVector<double>vTemp;
    qDebug() << "Enter number of rows: ";
    in >> rows;
    qDebug() << "Enter number of columns: ";
    in >> cols;
    qDebug() << "Enter the matrix elements " << Qt::endl;
    for (int i = 0; i < rows; i++)
    {
        vTemp.clear();
        for (int j = 0; j < cols; j++)
        {
            in >> temp;
            vTemp.push_back(temp);
        }
        ma.ma.push_back(vTemp);
    }
    return in;
}

QTextStream& operator<<(QTextStream& out, const Matrix& ma)
{
    for (const auto & v : ma.ma)
    {
        for (const double obj : v)
        {
            out << obj << " ";
        }
        qDebug() << Qt::endl;
    }
    return out;
}
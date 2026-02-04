#include "matrix.h"

Matrix::Matrix() = default;

Matrix::Matrix(const std::vector<std::vector<double>>& ma)
{
    this->ma = ma;
}

Matrix::~Matrix() = default;

void Matrix::printTasks()
{
    std::cout << std::endl;
    std::cout << "Task conditions:" << std::endl;
    std::cout << "1. Find the row numbers of matrix A = (aij), i = 1..n, j = 1..m, n, m <= 150, that contain the maximum number of positive elements." << std::endl;
    std::cout << "2. Neighbors of element aij in a matrix are defined as elements akg, where i - 1 < k < i + 1, j - 1 < g < j + 1, (k, g) != (i, j). The matrix smoothing operation produces a new matrix of the same size, where each element is obtained as the arithmetic mean of the available neighbors of the corresponding element in the original matrix. Construct the result of smoothing a given real matrix." << std::endl;
}

void Matrix::pos() const
{
    std::vector<int>count;
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
        std::cout << "Maximum number of positive elements: " << max << std::endl;
        std::cout << "Row indices with maximum positives: ";
        for (int i = 0; i < ma.size(); i++)
        {
            if (count[i] == max) std::cout << i + 1 << ' ';
        }
        std::cout << std::endl;
    }
    else std::cout << "All matrix elements are non-positive." << std::endl;
}

void Matrix::smooth()
{
    std::vector<std::vector<double>> maCopy = ma;
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

    std::cout << std::endl << "Smooth matrix: " << std::endl;
    for (const auto & v : ma)
    {
        for (const double obj : v)
        {
            std::cout << obj << " ";
        }
        std::cout << std::endl;
    }
}

std::istream& operator>>(std::istream& in, Matrix& ma)
{
    int temp, rows, cols;
    std::vector<double>vTemp;
    std::cout << "Enter number of rows: ";
    in >> rows;
    std::cout << "Enter number of columns: ";
    in >> cols;
    std::cout << "Enter the matrix elements " << std::endl;
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

std::ostream& operator<<(std::ostream& out, const Matrix& ma)
{
    for (const auto & v : ma.ma)
    {
        for (const double obj : v)
        {
            out << obj << " ";
        }
        std::cout << std::endl;
    }
    return out;
}
#include <iostream>
#include <iomanip>
#include <fstream>
#include <limits>
#include <vector>
#include <cmath>
#include <cstring>
#include <cerrno>

std::vector<double> gaussian(int n, std::vector<std::vector<double>> a, std::vector<double> f, double& det)
{
    det = 1.;
    std::vector<int> perm(n);
    for (int i = 0; i < n; i++)
    {
        perm[i] = i;
    }
    std::vector<std::vector<double>> b(n);
    for (int i = 0; i < n; i++)
    {
        std::vector<double> row(n);
        b[i] = row;
    }
    std::vector<double> g(n);

    for (int k = 0; k < n - 1; k++)
    {
        double max = -std::numeric_limits<double>::infinity(), p = k, q = k;

        for (int i = k; i < n; i++)
        {
            for (int j = k; j < n; j++)
            {
                if (max < std::abs(a[i][j]))
                {
                    max = std::abs(a[i][j]);
                    p = i;
                    q = j;
                }
            }
        }

        if (p != k)
        {
            std::swap(a[k], a[p]);
            std::swap(f[k], f[p]);
            det *= -1;
        }

        if (q != k)
        {
            for (int i = 0; i < n; i++)
            {
                std::swap(a[i][k], a[i][q]);
            }
            for (int i = 0; i < k; i++)
            {
                std::swap(b[i][k], b[i][q]);
            }
            std::swap(perm[k], perm[q]);
            det *= -1;
        }

        if (std::abs(a[k][k]) < 1e-15)
        {
            det = 0;
            return std::vector<double>(n, 0.0);
        }

        for (int j = k + 1; j < n; j++)
        {
            b[k][j] =  a[k][j] / a[k][k];
        }
        g[k] = f[k] / a[k][k];

        for (int i = k + 1; i < n; i++)
        {
            double fact = a[i][k];

            for (int j = k + 1; j < n; j++)
            {
                a[i][j] = a[i][j] - fact * b[k][j];
            }
            f[i] = f[i] - fact * g[k];
        }
    }

    for (int i = 0; i < n; i++)
    {
        det *= a[i][i];
    }

    std::vector<double> x(n);

    g[n - 1] = f[n - 1] / a[n - 1][n - 1];
    x[n - 1] = g[n - 1];

    for (int k = n - 2; k >= 0; k--)
    {
        double sum = 0;
        for (int j = k + 1; j < n; j++)
        {
            sum += b[k][j] * x[j];
        }
        x[k] = g[k] - sum;
    }

    std::vector<double> result(n);
    for (int i = 0; i < n; i++)
    {
        result[perm[i]] = x[i];
    }
    return result;
}

std::vector<std::vector<double>> inverse(int n, const std::vector<std::vector<double>>& matrix)
{
    std::vector<std::vector<double>> inv(n, std::vector<double>(n, 0.0));
    for (int j = 0; j < n; j++)
    {
        std::vector<double> e(n, 0.0);
        e[j] = 1.0;
        double d;
        std::vector<double> x = gaussian(n, matrix, e, d);
        for (int i = 0; i < n; i++)
        {
            inv[i][j] = x[i];
        }
    }
    return inv;
}

double normMatrix(int n, const std::vector<std::vector<double>>& m)
{
    double norm = 0.0;
    for (int i = 0; i < n; i++)
    {
        double rowSum = 0.0;
        for (int j = 0; j < n; j++)
        {
            rowSum += std::abs(m[i][j]);
        }
        if (rowSum > norm)
        {
            norm = rowSum;
        }
    }
    return norm;
}

double normVector(int n, const std::vector<double>& v)
{
    double norm = 0.0;
    for (int i = 0; i < n; i++)
    {
        if (std::abs(v[i]) > norm)
        {
            norm = std::abs(v[i]);
        }
    }
    return norm;
}

double conditionNumber(int n,
    const std::vector<std::vector<double>>& a,
    const std::vector<std::vector<double>>& inv)
{
    double normA = normMatrix(n, a);
    double normInv = normMatrix(n, inv);
    return normA * normInv;
}

std::vector<std::vector<double>> multiply(int n,
    const std::vector<std::vector<double>>& A,
    const std::vector<std::vector<double>>& B)
{
    std::vector<std::vector<double>> C(n, std::vector<double>(n, 0.0));
    for (int i = 0; i < n; i++)
    {
        for (int k = 0; k < n; k++)
        {
            double aik = A[i][k];
            if (aik == 0.0) continue;
            for (int j = 0; j < n; j++)
            {
                C[i][j] += aik * B[k][j];
            }
        }
    }
    return C;
}

std::vector<std::vector<double>> residualMatrix(
    int n,
    const std::vector<std::vector<double>>& A,
    const std::vector<std::vector<double>>& inv)
{
    auto prod = multiply(n, inv, A);
    for (int i = 0; i < n; i++)
    {
        prod[i][i] -= 1.0;
    }
    return prod;
}

std::vector<double> residualVector(int n,
    const std::vector<std::vector<double>>& A,
    const std::vector<double>& x,
    const std::vector<double>& b)
{
    std::vector<double> r(n, 0.0);
    for (int i = 0; i < n; i++)
    {
        double s = 0.0;
        for (int j = 0; j < n; j++)
        {
            s += A[i][j] * x[j];
        }
        r[i] = s - b[i];
    }
    return r;
}

void printVector(int n, const std::vector<double>& vector, std::ofstream& fout)
{
    for (int i = 0; i < n; i++)
    {
        fout << std::scientific << std::setw(16) << vector[i] << std::endl;
    }
    fout << std::endl;
}

void printMatrix(int n, const std::vector<std::vector<double>>& matrix, std::ofstream& fout)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            fout << std::scientific << std::setw(16) << matrix[i][j] << " ";
        }
        fout << std::endl;
    }
    fout << std::endl;
}

int main()
{
    std::ifstream fin("Input.txt");
    if (!fin.is_open())
    {
        std::cerr << "Error: " << std::strerror(errno) << std::endl;
        return 1;
    }

    std::ofstream fout("Output.txt");

    int n;
    fin >> n;

    std::vector<std::vector<double>> a(n);
    for (int i = 0; i < n; i++)
    {
        std::vector<double> row(n);
        a[i] = row;
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            fin >> a[i][j];
        }
    }

    std::vector<double> f(n);
    for (int i = 0; i < n; i++)
    {
        fin >> f[i];
    }

    fin.close();

    double det;

    auto sol = gaussian(n, a, f, det);
    fout << "Gaussian Method:" << std::endl;
    printVector(n, sol, fout);
    
    fout << std::defaultfloat << "Determinant: " << det << std::endl << std::endl;
    
    auto inv = inverse(n, a);
    fout << "Inverse Matrix:" << std::endl;
    printMatrix(n, inv, fout);

    double cond = conditionNumber(n, a, inv);
    fout << std::defaultfloat << "Condition number (first norm): " << cond << std::endl << std::endl;

    auto R = residualMatrix(n, a, inv);
    fout << "Residual matrix R = A^{-1} * A - E:" << std::endl;
    printMatrix(n, R, fout);

    double normR = normMatrix(n, R);
    fout << std::defaultfloat << "Residual matrix norm ||R||_1: " << normR << std::endl << std::endl;

    auto r = residualVector(n, a, sol, f);
    fout << "Residual vector r = A * x - b:" << std::endl;
    printVector(n, r, fout);

    double normRVector = normVector(n, r);
    fout << std::defaultfloat << "Residual vector norm ||r||_1: " << normRVector << std::endl << std::endl;

    fout.close();
    return 0;
}
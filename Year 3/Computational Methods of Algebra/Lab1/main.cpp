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

std::vector<std::vector<double>> inverseGaussian(int n, const std::vector<std::vector<double>>& matrix)
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

bool isTridiagonal(int n, const std::vector<std::vector<double>>& a)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (std::abs(i - j) > 1 && std::abs(a[i][j]) > 1e-15)
            {
                return false;
            }
        }
    }
    return true;
}

std::vector<double> tridiagonalSolveLeft(
    int n,
    const std::vector<std::vector<double>>& A,
    const std::vector<double>& f,
    bool& ok)
{
    ok = true;
    std::vector<double> xi(n, 0.0), eta(n, 0.0), y(n, 0.0);

    if (n == 1)
    {
        if (std::abs(A[0][0]) < 1e-15)
        {
            ok = false;
            return y;
        }
        y[0] = f[0] / A[0][0];
        return y;
    }

    if (std::abs(A[n - 1][n - 1]) < 1e-15)
    {
        ok = false;
        return y;
    }

    double a_nm1 = -A[n - 1][n - 2];
    xi[n - 1] = a_nm1 / A[n - 1][n - 1];
    eta[n - 1] = f[n - 1] / A[n - 1][n - 1];

    for (int i = n - 2; i >= 1; i--)
    {
        double c_i = A[i][i];
        double a_i = -A[i][i - 1];
        double b_i = -A[i][i + 1];

        double d_i = c_i - xi[i + 1] * b_i;
        if (std::abs(d_i) < 1e-15)
        {
            ok = false;
            return y;
        }

        xi[i] = a_i / d_i;
        eta[i] = (f[i] + b_i * eta[i + 1]) / d_i;
    }

    double c_0 = A[0][0];
    double b_0 = -A[0][1];
    double d_0 = c_0 - xi[1] * b_0;
    if (std::abs(d_0) < 1e-15)
    {
        ok = false;
        return y;
    }
    eta[0] = (f[0] + b_0 * eta[1]) / d_0;
    
    y[0] = eta[0];
    for (int i = 0; i < n - 1; i++)
    {
        y[i + 1] = xi[i + 1] * y[i] + eta[i + 1];
    }

    return y;
}

double determinantTridiagonal(int n, const std::vector<std::vector<double>>& A)
{
    if (n == 1)
    {
        return A[0][0];
    }

    std::vector<double> D(n + 1, 0.0);
    D[0] = 1.0;
    D[1] = A[0][0];

    for (int m = 2; m <= n; m++)
    {
        double c = A[m - 1][m - 1];
        double a = A[m - 1][m - 2];
        double b = (m - 2 >= 0) ? A[m - 2][m - 1] : 0.0;
        D[m] = c * D[m - 1] - a * b * D[m - 2];
    }

    return D[n];
}

std::vector<std::vector<double>> inverseTridiagonal(
    int n,
    const std::vector<std::vector<double>>& A,
    bool& ok)
{
    ok = true;
    std::vector<std::vector<double>> inv(n, std::vector<double>(n, 0.0));

    for (int j = 0; j < n; j++)
    {
        std::vector<double> e(n, 0.0);
        e[j] = 1.0;

        bool localOk = true;
        std::vector<double> x = tridiagonalSolveLeft(n, A, e, localOk);

        if (!localOk)
        {
            ok = false;
            return inv;
        }

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
    fout << "========================================" << std::endl;
    fout << "Gaussian Method:" << std::endl;
    fout << "========================================" << std::endl;
    printVector(n, sol, fout);
    
    fout << std::defaultfloat << "Determinant: " << det << std::endl << std::endl;
    
    auto inv = inverseGaussian(n, a);
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

    if (isTridiagonal(n, a))
    {
        fout << "========================================" << std::endl;
        fout << "Left Sweep Method (Tridiagonal):" << std::endl;
        fout << "========================================" << std::endl;

        bool ok = true;
        auto yLeft = tridiagonalSolveLeft(n, a, f, ok);

        if (!ok)
        {
            fout << "Left sweep failed: zero pivot encountered." << std::endl;
        }
        else
        {
            fout << "Solution y (left sweep):" << std::endl;
            printVector(n, yLeft, fout);

            double detTri = determinantTridiagonal(n, a);
            fout << std::defaultfloat << "Determinant (tridiagonal formula): " << detTri << std::endl << std::endl;

            bool invOk = true;
            auto invTri = inverseTridiagonal(n, a, invOk);

            if (!invOk)
            {
                fout << "Inverse via left sweep failed: zero pivot." << std::endl;
            }
            else
            {
                fout << "Inverse Matrix (via left sweep):" << std::endl;
                printMatrix(n, invTri, fout);

                double condTri = conditionNumber(n, a, invTri);
                fout << std::defaultfloat << "Condition number (left sweep, first norm): " << condTri << std::endl << std::endl;

                auto RTri = residualMatrix(n, a, invTri);
                fout << "Residual matrix R = A^{-1} * A - E (left sweep):" << std::endl;
                printMatrix(n, RTri, fout);

                double normRTri = normMatrix(n, RTri);
                fout << std::defaultfloat << "Residual matrix norm ||R||_1: " << normRTri << std::endl << std::endl;

                auto rTri = residualVector(n, a, yLeft, f);
                fout << "Residual vector r = A * y - b (left sweep):" << std::endl;
                printVector(n, rTri, fout);

                double normRVectorTri = normVector(n, rTri);
                fout << std::defaultfloat << "Residual vector norm ||r||_1: " << normRVectorTri << std::endl << std::endl;
            }
        }
    }
    else
    {
        fout << "========================================" << std::endl;
        fout << "Left Sweep Method skipped: matrix is not tridiagonal." << std::endl;
        fout << "========================================" << std::endl;
    }

    fout.close();
    return 0;
}
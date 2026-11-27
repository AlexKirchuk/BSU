#include <iostream>
#include <iomanip>
#include <fstream>
#include <limits>
#include <vector>
#include <cmath>
#include <cstring>
#include <cerrno>

double normVectorI(int n, const std::vector<double>& v)
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

double dotProduct(int n, const std::vector<double>& u, const std::vector<double>& v)
{
    double res = 0.0;
    for (int i = 0; i < n; i++)
    {
        res += u[i] * v[i];
    }
    return res;
}

std::vector<std::vector<double>> transposeMatrix(int n, const std::vector<std::vector<double>>& A)
{
    std::vector<std::vector<double>> T(n, std::vector<double>(n, 0.0));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            T[i][j] = A[j][i];
        }
    }
    return T;
}

std::vector<std::vector<double>> multiplyMatrices(
    int n,
    const std::vector<std::vector<double>>& A,
    const std::vector<std::vector<double>>& B)
{
    std::vector<std::vector<double>> C(n, std::vector<double>(n, 0.0));
    for (int i = 0; i < n; i++)
    {
        for (int k = 0; k < n; k++)
        {
            double aik = A[i][k];
            if (aik == 0.0)
            {
                continue;
            }
            for (int j = 0; j < n; j++)
            {
                C[i][j] += aik * B[k][j];
            }
        }
    }
    return C;
}

std::vector<double> multiplyMatrixVector(
    int n,
    const std::vector<std::vector<double>>& A,
    const std::vector<double>& x)
{
    std::vector<double> y(n, 0.0);
    for (int i = 0; i < n; i++)
    {
        double sum = 0.0;
        for (int j = 0; j < n; j++)
        {
            sum += A[i][j] * x[j];
        }
        y[i] = sum;
    }
    return y;
}

std::vector<double> normalizeByLastCoord(int n, const std::vector<double>& v)
{
    std::vector<double> res = v;
    double last = res[n - 1];
    if (std::abs(last) > 1e-15)
    {
        for (int i = 0; i < n; i++)
        {
            res[i] /= last;
        }
    }
    return res;
}

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
            b[k][j] = a[k][j] / a[k][k];
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

std::vector<double> krylovPolyCoeffs(
    int n,
    const std::vector<std::vector<double>>& M,
    std::vector<std::vector<double>>& krylovVectors)
{
    krylovVectors.assign(n + 1, std::vector<double>(n, 0.0));
    krylovVectors[0][0] = 1.0;

    for (int k = 1; k <= n; k++)
    {
        krylovVectors[k] = multiplyMatrixVector(n, M, krylovVectors[k - 1]);
    }

    std::vector<std::vector<double>> sys(n, std::vector<double>(n, 0.0));
    for (int row = 0; row < n; row++)
    {
        for (int col = 0; col < n; col++)
        {
            sys[row][col] = krylovVectors[n - 1 - col][row];
        }
    }

    double det = 0.0;
    return gaussian(n, sys, krylovVectors[n], det);
}

double evalCharPoly(int n, const std::vector<double>& p, double lambda)
{
    double val = std::pow(lambda, n);
    double power = 1.0;
    for (int k = n - 1; k >= 0; k--)
    {
        val -= p[k] * power;
        power *= lambda;
    }
    return val;
}

double nonDiagonalSqSum(int n, const std::vector<std::vector<double>>& A)
{
    double t = 0.0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (i != j)
            {
                t += A[i][j] * A[i][j];
            }
        }
    }
    return t;
}

void jacobiEigen(
    int n,
    const std::vector<std::vector<double>>& M,
    double eps,
    std::vector<double>& lambdas,
    std::vector<std::vector<double>>& vectors,
    int& iterations,
    bool& ok)
{
    ok = true;
    iterations = 0;
    std::vector<std::vector<double>> A = M;
    std::vector<std::vector<double>> U(n, std::vector<double>(n, 0.0));
    for (int i = 0; i < n; i++)
    {
        U[i][i] = 1.0;
    }

    int maxIter = 10000;
    bool converged = false;

    for (int iter = 0; iter < maxIter; iter++)
    {
        double tVal = nonDiagonalSqSum(n, A);
        if (tVal <= eps)
        {
            converged = true;
            break;
        }

        iterations = iter + 1;

        int p = 0;
        int q = 1;
        double maxVal = 0.0;
        for (int i = 0; i < n; i++)
        {
            for (int j = i + 1; j < n; j++)
            {
                if (std::abs(A[i][j]) > maxVal)
                {
                    maxVal = std::abs(A[i][j]);
                    p = i;
                    q = j;
                }
            }
        }

        if (maxVal < 1e-16)
        {
            converged = true;
            break;
        }

        double c = 0.0;
        double s = 0.0;
        double diffDiag = A[p][p] - A[q][q];
        if (std::abs(diffDiag) < 1e-15)
        {
            c = std::sqrt(0.5);
            s = (A[p][q] >= 0.0) ? std::sqrt(0.5) : -std::sqrt(0.5);
        }
        else
        {
            double tg2phi = (2.0 * A[p][q]) / diffDiag;
            double cos2phi = 1.0 / std::sqrt(1.0 + tg2phi * tg2phi);
            c = std::sqrt(0.5 * (1.0 + cos2phi));
            double sinAbs = std::sqrt(0.5 * (1.0 - cos2phi));
            double signArg = A[p][q] * diffDiag;
            s = (signArg >= 0.0) ? sinAbs : -sinAbs;
        }

        std::vector<std::vector<double>> B = A;
        for (int l = 0; l < n; l++)
        {
            B[l][p] = A[l][p] * c + A[l][q] * s;
            B[l][q] = -A[l][p] * s + A[l][q] * c;
        }

        std::vector<std::vector<double>> A_next = B;
        for (int l = 0; l < n; l++)
        {
            A_next[p][l] = B[p][l] * c + B[q][l] * s;
            A_next[q][l] = -B[p][l] * s + B[q][l] * c;
        }
        A_next[p][q] = 0.0;
        A_next[q][p] = 0.0;
        A = A_next;

        for (int l = 0; l < n; l++)
        {
            double up = U[l][p];
            double uq = U[l][q];
            U[l][p] = up * c + uq * s;
            U[l][q] = -up * s + uq * c;
        }
    }

    if (!converged && nonDiagonalSqSum(n, A) > eps)
    {
        ok = false;
    }

    lambdas.assign(n, 0.0);
    vectors.assign(n, std::vector<double>(n, 0.0));
    for (int i = 0; i < n; i++)
    {
        lambdas[i] = A[i][i];
        std::vector<double> col(n, 0.0);
        for (int j = 0; j < n; j++)
        {
            col[j] = U[j][i];
        }
        vectors[i] = normalizeByLastCoord(n, col);
    }
}

void danilevskyMethod(
    int n,
    const std::vector<std::vector<double>>& M,
    std::vector<double>& polyCoeffs,
    std::vector<std::vector<double>>& S_total,
    bool& ok)
{
    ok = true;
    std::vector<std::vector<double>> A = M;
    S_total.assign(n, std::vector<double>(n, 0.0));
    for (int i = 0; i < n; i++)
    {
        S_total[i][i] = 1.0;
    }

    for (int step = 0; step < n - 1; step++)
    {
        int k = n - 1 - step;
        if (std::abs(A[k][k - 1]) < 1e-15)
        {
            int swapIdx = -1;
            for (int j = k - 2; j >= 0; j--)
            {
                if (std::abs(A[k][j]) > 1e-15)
                {
                    swapIdx = j;
                    break;
                }
            }
            if (swapIdx == -1)
            {
                ok = false;
                return;
            }
            for (int row = 0; row < n; row++)
            {
                std::swap(A[row][k - 1], A[row][swapIdx]);
            }
            for (int col = 0; col < n; col++)
            {
                std::swap(A[k - 1][col], A[swapIdx][col]);
            }
            for (int row = 0; row < n; row++)
            {
                std::swap(S_total[row][k - 1], S_total[row][swapIdx]);
            }
        }

        double pivot = A[k][k - 1];
        std::vector<std::vector<double>> M_mat(n, std::vector<double>(n, 0.0));
        std::vector<std::vector<double>> M_inv(n, std::vector<double>(n, 0.0));
        for (int i = 0; i < n; i++)
        {
            M_mat[i][i] = 1.0;
            M_inv[i][i] = 1.0;
        }
        for (int j = 0; j < n; j++)
        {
            if (j == k - 1)
            {
                M_mat[k - 1][j] = 1.0 / pivot;
            }
            else
            {
                M_mat[k - 1][j] = -A[k][j] / pivot;
            }
            M_inv[k - 1][j] = A[k][j];
        }

        std::vector<std::vector<double>> temp = multiplyMatrices(n, A, M_mat);
        A = multiplyMatrices(n, M_inv, temp);
        S_total = multiplyMatrices(n, S_total, M_mat);
    }

    polyCoeffs.assign(n, 0.0);
    for (int j = 0; j < n; j++)
    {
        polyCoeffs[j] = A[0][j];
    }
}

std::vector<double> danilevskyEigenvector(
    int n,
    const std::vector<std::vector<double>>& S_total,
    double lambda)
{
    std::vector<double> y(n, 0.0);
    double power = 1.0;
    for (int i = n - 1; i >= 0; i--)
    {
        y[i] = power;
        power *= lambda;
    }
    std::vector<double> x = multiplyMatrixVector(n, S_total, y);
    return normalizeByLastCoord(n, x);
}

void powerMethodMinEigen(
    int n,
    const std::vector<std::vector<double>>& M,
    double eps,
    double& lambdaMin,
    std::vector<double>& vecMin,
    int& iterations,
    bool& ok)
{
    ok = true;
    iterations = 0;
    lambdaMin = 0.0;

    std::vector<double> z(n, 1.0);
    double normZ0 = normVectorI(n, z);
    for (int i = 0; i < n; i++)
    {
        z[i] /= normZ0;
    }

    double prevLambda = 0.0;
    int maxIter = 10000;
    bool converged = false;

    for (int iter = 0; iter < maxIter; iter++)
    {
        iterations = iter + 1;
        double det = 0.0;
        std::vector<double> y = gaussian(n, M, z, det);
        if (std::abs(det) < 1e-15)
        {
            ok = false;
            return;
        }

        double denom = dotProduct(n, y, y);
        if (std::abs(denom) < 1e-15)
        {
            ok = false;
            return;
        }
        double currLambda = dotProduct(n, y, z) / denom;

        double normY = normVectorI(n, y);
        if (normY < 1e-15)
        {
            ok = false;
            return;
        }
        for (int i = 0; i < n; i++)
        {
            z[i] = y[i] / normY;
        }

        if (iter > 0 && std::abs(currLambda - prevLambda) <= eps)
        {
            lambdaMin = currLambda;
            converged = true;
            break;
        }

        prevLambda = currLambda;
        lambdaMin = currLambda;
    }

    if (!converged)
    {
        ok = false;
    }

    vecMin = normalizeByLastCoord(n, z);
}

std::vector<double> residualEigenVector(
    int n,
    const std::vector<std::vector<double>>& M,
    double lambda,
    const std::vector<double>& x)
{
    std::vector<double> Mx = multiplyMatrixVector(n, M, x);
    std::vector<double> r(n, 0.0);
    for (int i = 0; i < n; i++)
    {
        r[i] = Mx[i] - lambda * x[i];
    }
    return r;
}

void printVector(int n, const std::vector<double>& v, std::ofstream& fout)
{
    for (int i = 0; i < n; i++)
    {
        fout << std::scientific << std::setprecision(8) << std::setw(18) << v[i] << std::endl;
    }
    fout << std::endl;
}

void printMatrix(int n, const std::vector<std::vector<double>>& mat, std::ofstream& fout)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            fout << std::scientific << std::setprecision(8) << std::setw(18) << mat[i][j] << " ";
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
    if (!fout.is_open())
    {
        std::cerr << "Error opening Output.txt: " << std::strerror(errno) << std::endl;
        return 1;
    }

    int n = 0;
    fin >> n;

    std::vector<std::vector<double>> A(n, std::vector<double>(n, 0.0));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            fin >> A[i][j];
        }
    }
    fin.close();

    std::vector<std::vector<double>> AT = transposeMatrix(n, A);
    std::vector<std::vector<double>> M = multiplyMatrices(n, AT, A);

    fout << "========================================" << std::endl;
    fout << "Matrix M = A^T * A:" << std::endl;
    fout << "========================================" << std::endl;
    printMatrix(n, M, fout);

    std::vector<std::vector<double>> krylovC;
    std::vector<double> pKrylov = krylovPolyCoeffs(n, M, krylovC);

    fout << "========================================" << std::endl;
    fout << "1. Krylov Method (p_1 .. p_n):" << std::endl;
    fout << "========================================" << std::endl;
    for (int i = 0; i < n; i++)
    {
        fout << "p_" << (i + 1) << " = " << std::scientific << std::setprecision(10) << pKrylov[i] << std::endl;
    }
    fout << std::endl;

    double eps = 1e-5;
    std::vector<double> lambdasJacobi;
    std::vector<std::vector<double>> vecsJacobi;
    int jacobiIters = 0;
    bool jacobiOk = false;
    jacobiEigen(n, M, eps, lambdasJacobi, vecsJacobi, jacobiIters, jacobiOk);

    fout << "========================================" << std::endl;
    fout << "2. Jacobi Rotation Method (eps = 1e-5):" << std::endl;
    fout << "========================================" << std::endl;
    fout << "Converged: " << (jacobiOk ? "yes" : "no") << ", iterations: " << jacobiIters << std::endl << std::endl;
    for (int i = 0; i < n; i++)
    {
        fout << "lambda_" << (i + 1) << " = " << std::scientific << std::setprecision(10) << lambdasJacobi[i] << std::endl;
        fout << "x_" << (i + 1) << " (normalized by last coord):" << std::endl;
        printVector(n, vecsJacobi[i], fout);
    }

    std::vector<double> pDanilevsky;
    std::vector<std::vector<double>> S_dan;
    bool danOk = false;
    danilevskyMethod(n, M, pDanilevsky, S_dan, danOk);

    fout << "========================================" << std::endl;
    fout << "3. Danilevsky Method (using lambda_i from Jacobi):" << std::endl;
    fout << "========================================" << std::endl;
    if (!danOk)
    {
        fout << "Danilevsky reduction failed." << std::endl << std::endl;
    }
    else
    {
        fout << "Danilevsky poly coeffs p_1 .. p_n:" << std::endl;
        for (int i = 0; i < n; i++)
        {
            fout << "p_" << (i + 1) << " = " << std::scientific << std::setprecision(10) << pDanilevsky[i] << std::endl;
        }
        fout << std::endl;

        for (int i = 0; i < n; i++)
        {
            std::vector<double> xDan = danilevskyEigenvector(n, S_dan, lambdasJacobi[i]);
            std::vector<double> diffVec(n, 0.0);
            for (int j = 0; j < n; j++)
            {
                diffVec[j] = xDan[j] - vecsJacobi[i][j];
            }
            fout << "x_dan_" << (i + 1) << " (for lambda_" << (i + 1) << "):" << std::endl;
            printVector(n, xDan, fout);
            fout << "||x_dan_" << (i + 1) << " - x_jac_" << (i + 1) << "||_I = "
                << std::scientific << std::setprecision(6) << normVectorI(n, diffVec) << std::endl << std::endl;
        }
    }

    double lambdaMinPower = 0.0;
    std::vector<double> vecMinPower;
    int powerIters = 0;
    bool powerOk = false;
    powerMethodMinEigen(n, M, eps, lambdaMinPower, vecMinPower, powerIters, powerOk);

    fout << "========================================" << std::endl;
    fout << "4. Power Method for Minimal Eigenvalue (eps = 1e-5):" << std::endl;
    fout << "========================================" << std::endl;
    fout << "Converged: " << (powerOk ? "yes" : "no") << ", iterations: " << powerIters << std::endl;
    fout << "lambda_min = " << std::scientific << std::setprecision(10) << lambdaMinPower << std::endl;
    fout << "x_min (normalized by last coord):" << std::endl;
    printVector(n, vecMinPower, fout);

    fout << "========================================" << std::endl;
    fout << "Residuals phi_i = P_n(lambda_i) and r_i = M*x_i - lambda_i*x_i:" << std::endl;
    fout << "========================================" << std::endl;
    for (int i = 0; i < n; i++)
    {
        double phi = evalCharPoly(n, pKrylov, lambdasJacobi[i]);
        std::vector<double> rVec = residualEigenVector(n, M, lambdasJacobi[i], vecsJacobi[i]);
        fout << "i = " << (i + 1) << ": lambda_" << (i + 1) << " = "
            << std::scientific << std::setprecision(10) << lambdasJacobi[i] << std::endl;
        fout << "  phi_" << (i + 1) << " = P_n(lambda_" << (i + 1) << ") = " << phi << std::endl;
        fout << "  ||r_" << (i + 1) << "||_I = " << normVectorI(n, rVec) << std::endl;
        fout << "  r_" << (i + 1) << ":" << std::endl;
        printVector(n, rVec, fout);
    }

    std::vector<double> rMin = residualEigenVector(n, M, lambdaMinPower, vecMinPower);
    fout << "Power method minimal eigenvalue residual:" << std::endl;
    fout << "  phi_min = P_n(lambda_min) = " << std::scientific << std::setprecision(10)
        << evalCharPoly(n, pKrylov, lambdaMinPower) << std::endl;
    fout << "  ||r_min||_I = " << normVectorI(n, rMin) << std::endl;
    fout << "  r_min:" << std::endl;
    printVector(n, rMin, fout);

    fout.close();
    return 0;
}
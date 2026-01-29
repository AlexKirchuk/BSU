#include <iostream>
#include <iomanip>
#include <ctime>
using namespace std;

// ===================== TASK 1 FUNCTIONS =====================
void randIntMatrix(int matr[150][150], const int n, const int m)
{
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            matr[i][j] = rand() % 10 - rand() % 10;
}

void printIntMatrix(int matr[150][150], int n, int m)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
            cout << setw(4) << matr[i][j];
        cout << endl;
    }
}

void task1()
{
    int n, m;
    int matrix[150][150];
    int count[150]{};
    int maxPos = 0;

    do
    {
        cout << "Enter number of rows n (0 < n <= 150): ";
        cin >> n;
    } while (n <= 0 || n > 150);

    do
    {
        cout << "Enter number of columns m (0 < m <= 150): ";
        cin >> m;
    } while (m <= 0 || m > 150);

    randIntMatrix(matrix, n, m);
    printIntMatrix(matrix, n, m);

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
            if (matrix[i][j] > 0) count[i]++;
        if (count[i] > maxPos) maxPos = count[i];
    }

    if (maxPos > 0)
    {
        cout << "Maximum number of positive elements: " << maxPos << endl;
        cout << "Row indices with maximum positives: ";
        for (int i = 0; i < n; i++)
            if (count[i] == maxPos) cout << i + 1 << " ";
        cout << endl;
    }
    else
        cout << "All matrix elements are non-positive." << endl;
}

// ===================== TASK 2 FUNCTIONS =====================
int inputN(int& n)
{
    do
    {
        cout << "Enter number of rows (0 < n <= 100): ";
        cin >> n;
    } while (n <= 0 || n > 100);
    return n;
}

int inputM(int& m)
{
    do
    {
        cout << "Enter number of columns (0 < m <= 100): ";
        cin >> m;
    } while (m <= 0 || m > 100);
    return m;
}

void randomDoubleMatrix(double** matr, int n, int m)
{
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            matr[i][j] = rand() % 100;
}

void printDoubleMatrix(double** matr, int n, int m)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
            cout << setw(9) << matr[i][j];
        cout << endl;
    }
    cout << endl;
}

double** smoothMatrix(double** matr, const int n, const int m)
{
    double** result = new double*[n];
    for (int i = 0; i < n; i++)
        result[i] = new double[m];

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            double sum = 0;
            int cnt = 0;
            for (int k = i - 1; k <= i + 1; k++)
                for (int g = j - 1; g <= j + 1; g++)
                    if (k >= 0 && k < n && g >= 0 && g < m && !(k == i && g == j))
                    {
                        sum += matr[k][g];
                        cnt++;
                    }
            result[i][j] = sum / cnt;
        }
    }
    return result;
}

void task2()
{
    int n, m;
    inputN(n);
    inputM(m);

    double** matrix = new double*[n];
    for (int i = 0; i < n; i++)
        matrix[i] = new double[m];

    randomDoubleMatrix(matrix, n, m);
    printDoubleMatrix(matrix, n, m);

    double** smoothed = smoothMatrix(matrix, n, m);
    printDoubleMatrix(smoothed, n, m);

    for (int i = 0; i < n; i++)
    {
        delete[] matrix[i];
        delete[] smoothed[i];
    }
    delete[] matrix;
    delete[] smoothed;
}

// ============================ MAIN ============================
int main()
{
    srand(time(nullptr));

    cout << "--- Task 1 ---" << endl;
    task1();

    cout << endl << "--- Task 2 ---" << endl;
    task2();

    return 0;
}
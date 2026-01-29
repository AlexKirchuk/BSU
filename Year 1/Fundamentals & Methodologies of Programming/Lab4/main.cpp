#include <iostream>
#include <iomanip>
#include <cmath>
#include <ctime>
using namespace std;

// ========================= TASK 1 =========================
// Check whether a sequence is arithmetic or geometric

void checkArithmetic(const double* arr, const int n)
{
    bool isArithmetic = true;
    const double d = arr[1] - arr[0];

    for (int i = 0; i < n - 1; i++)
    {
        if (arr[i + 1] - arr[i] != d)
        {
            isArithmetic = false;
            break;
        }
    }

    if (isArithmetic && n > 2 && d != 0)
    {
        cout << "The sequence is an arithmetic progression" << endl;
        cout << "Common difference d = " << d << endl;
    }
    else if (d != 0)
    {
        cout << "The sequence is not an arithmetic progression" << endl;
    }
}

void checkGeometric(const double* arr, const int n)
{
    bool isGeometric = true;
    const double q = arr[1] / arr[0];

    for (int i = 0; i < n - 1; i++)
    {
        if (arr[i + 1] / arr[i] != q)
        {
            isGeometric = false;
            break;
        }
    }

    if (isGeometric && n > 2 && q != 1 && q != 0)
    {
        cout << "The sequence is a geometric progression" << endl;
        cout << "Common ratio q = " << q << endl;
    }
    else if (q != 1)
    {
        cout << "The sequence is not a geometric progression" << endl;
    }
    else
    {
        cout << "The sequence is stationary" << endl;
    }
}

void task1()
{
    int n;
    double arr[100]{};

    do
    {
        cout << "Enter the number of elements (0 < n <= 100): ";
        cin >> n;
    } while (n <= 0 || n > 100);

    cout << "Enter the sequence elements:" << endl;
    for (int i = 0; i < n; i++) cin >> arr[i];

    checkArithmetic(arr, n);
    checkGeometric(arr, n);

    if (n == 1)
        cout << "The sequence has one element: " << arr[0] << endl;
    if (n == 2)
        cout << "The sequence has two elements: " << arr[0] << " and " << arr[1] << endl;
}

// ========================= TASK 2 =========================
// Reorder by even digit sum

int digitSum(int x)
{
    int s = 0;
    while (x > 0)
    {
        s += x % 10;
        x /= 10;
    }
    return s;
}

void sortByDigitSum(int arr[], const int n)
{
    for (int i = 0; i < n; i++)
        for (int j = 1; j < n; j++)
            if (digitSum(arr[j]) % 2 == 0 && digitSum(arr[j - 1]) % 2 != 0)
                swap(arr[j], arr[j - 1]);
}

void task2()
{
    int n;
    do
    {
        cout << "Enter number of elements (0 < n <= 100): ";
        cin >> n;
    } while (n <= 0 || n > 100);

    const auto arr = new int[n];
    srand(time(nullptr));

    for (int i = 0; i < n; i++) arr[i] = rand() % 100;

    cout << "Original array:" << endl;
    for (int i = 0; i < n; i++) cout << arr[i] << " ";
    cout << endl;

    sortByDigitSum(arr, n);

    cout << "Reordered array:" << endl;
    for (int i = 0; i < n; i++) cout << arr[i] << " ";
    cout << endl;

    delete[] arr;
}

// ========================= TASK 3 =========================
// Intersection of two non-decreasing arrays

void inputSortedArray(double* arr, const int size)
{
    cout << "Enter elements of a non-decreasing array:" << endl;
    cin >> arr[0];
    for (int i = 1; i < size; i++)
    {
        do
        {
            cin >> arr[i];
        } while (arr[i] < arr[i - 1]);
    }
}

void printArray(const double* arr, const int size)
{
    for (int i = 0; i < size; i++) cout << arr[i] << " ";
    cout << endl;
}

void task3()
{
    int n, m;
    double x[10]{}, y[10]{}, z[10]{};
    int p = 0;

    do { cout << "Enter size of first array (<=10): "; cin >> n; } while (n <= 0 || n > 10);
    inputSortedArray(x, n);

    do { cout << "Enter size of second array (<=10): "; cin >> m; } while (m <= 0 || m > 10);
    inputSortedArray(y, m);

    for (int i = 0, j = 0; i < n && j < m; )
    {
        if (x[i] < y[j]) i++;
        else if (x[i] > y[j]) j++;
        else
        {
            const double value = x[i];
            int cx = 0, cy = 0;
            while (i < n && x[i] == value) { cx++; i++; }
            while (j < m && y[j] == value) { cy++; j++; }
            int minc = min(cx, cy);
            for (int k = 0; k < minc; k++) z[p++] = value;
        }
    }

    cout << "Intersection:" << endl;
    if (p == 0) cout << "Empty set" << endl;
    else printArray(z, p);
}

// ========================= TASK 4 =========================
// Count distinct elements

void bubbleSort(int* arr, int n)
{
    for (int i = 0; i < n; i++)
        for (int j = n - 1; j > i; j--)
            if (arr[j - 1] > arr[j]) swap(arr[j - 1], arr[j]);
}

void task4()
{
    int n;
    do
    {
        cout << "Enter number of elements (0 < n <= 100): ";
        cin >> n;
    } while (n <= 0 || n > 100);

    const auto arr = new int[n];
    srand(time(nullptr));

    for (int i = 0; i < n; i++) arr[i] = rand() % 100;

    for (int i = 0; i < n; i++) cout << arr[i] << " ";
    cout << endl;

    bubbleSort(arr, n);

    int count = 0;
    for (int i = 0; i < n; i++)
    {
        while (i < n - 1 && arr[i] == arr[i + 1]) i++;
        count++;
    }

    cout << "Number of distinct elements: " << count << endl;
    delete[] arr;
}

// ========================= MAIN MENU =========================

int main()
{
    int choice;
    cout << "Lab 4 Tasks Menu" << endl;
    cout << "1 - Arithmetic / Geometric progression check" << endl;
    cout << "2 - Reorder by even digit sum" << endl;
    cout << "3 - Intersection of two arrays" << endl;
    cout << "4 - Count distinct elements" << endl;
    cout << "Choose a task: ";
    cin >> choice;

    switch (choice)
    {
    case 1: task1(); break;
    case 2: task2(); break;
    case 3: task3(); break;
    case 4: task4(); break;
    default: cout << "Invalid choice" << endl;
    }
    return 0;
}
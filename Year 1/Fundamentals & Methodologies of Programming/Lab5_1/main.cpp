#include <iostream>
#include <iomanip>
#include <ctime>
using namespace std;

void printArr(int arr[], const int n)
{
    for (int i = 0; i < n; i++)
    {
        cout << setw(4) << arr[i];
    }
}

void shellSort(int arr[], const int size)
{
    int k;
    for (int i = size / 2; i > 0; i /= 2)
    {
        for (int j = i; j < size; j++)
        {
            const int tmp = arr[j];
            for (k = j; k >= i; k -= i)
            {
                if (tmp < arr[k - i])
                    arr[k] = arr[k - i];
                else
                    break;
            }
            arr[k] = tmp;
        }
    }
}

int main()
{
    srand(time(nullptr));
    int n;
    cout << "Enter the number of elements: ";
    cin >> n;
    int arr[100]{};
    for (int i = 0; i < n; i++)
    {
        arr[i] = rand() % 100;
    }
    printArr(arr, n);
    shellSort(arr, n);
    cout << endl;
    printArr(arr, n);
    return 0;
}
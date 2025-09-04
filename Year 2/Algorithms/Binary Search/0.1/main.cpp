#include <iostream>

int main()
{
    long arrCount, * arr, queryCount, * query;

    std::cin >> arrCount;
    arr = new long[arrCount];
    for (int i = 0; i < arrCount; i++)
    {
        std::cin >> arr[i];
    }

    std::cin >> queryCount;
    query = new long[queryCount];
    for (int i = 0; i < queryCount; i++)
    {
        std::cin >> query[i];
    }

    long b, l, r;
    for (long i = 0; i < queryCount; i++)
    {
        b = 0;
        l = -1;
        r = -1;

        for (long j = 0; j < arrCount; j++)
        {
            if ((b != 1 and query[i] == arr[j]))
            {
                b = 1;
            }
            if (l == -1 and query[i] <= arr[j])
            {
                l = j;
            }
            if (r == -1 and query[i] < arr[j])
            {
                r = j;
            }
            if (r != -1)
            {
                std::cout << b << " " << l << " " << r << std::endl;
                break;
            }
            if (j == arrCount - 1 and l == -1)
            {
                l = arrCount;
                r = arrCount;
                std::cout << b << " " << l << " " << r << std::endl;
            }
            else if (j == arrCount - 1 and r == -1)
            {
                r = arrCount;
                std::cout << b << " " << l << " " << r << std::endl;
            }
        }
    }

    delete[] arr;
    delete[] query;
}

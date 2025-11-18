#include <iostream>

int main()
{
    long arrCount, * arr, queryCount, * query;

    std::cin >> arrCount;
    arr = new long[arrCount];
    for (long i = 0; i < arrCount; i++)
    {
        std::cin >> arr[i];
    }

    std::cin >> queryCount;
    query = new long[queryCount];
    for (long i = 0; i < queryCount; i++)
    {
        std::cin >> query[i];
    }

    long b, l, r, left, right, mid;

    for (long i = 0; i < queryCount; i++) {

        left = 0;
        right = arrCount;
        while (left < right) {
            mid = (left + right) / 2;
            if (arr[mid] < query[i])
                left = mid + 1;
            else
                right = mid;
        }
        l = left;

        left = 0;
        right = arrCount;
        while (left < right) {
            mid = (left + right) / 2;
            if (arr[mid] <= query[i])
                left = mid + 1;
            else
                right = mid;
        }
        r = left;

        if (l < arrCount && arr[l] == query[i])
            b = 1;
        else
            b = 0;

        std::cout << b << " " << l << " " << r << std::endl;
    }

    delete[] arr;
    delete[] query;
}
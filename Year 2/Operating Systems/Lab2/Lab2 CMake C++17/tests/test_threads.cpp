#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest.h>
#include "data.h"
#include "minmax.h"
#include "average.h"
#include <windows.h>

HANDLE hConsoleMutex = CreateMutex(NULL, FALSE, NULL);

TEST_CASE("TestMinMax")
{
    int arr[5] = { 5, 3, 9, 1, 7 };
    Data data;
    data.arr = arr;
    data.size = 5;

    min_max_thread(&data);

    CHECK(data.min == 1);
    CHECK(data.max == 9);
}

TEST_CASE("TestAverage")
{
    int arr[5] = { 5, 3, 9, 1, 7 };
    Data data;
    data.arr = arr;
    data.size = 5;

    average_thread(&data);

    CHECK(data.average == doctest::Approx(5.0));
}

TEST_CASE("TestReplaceMinMaxWithAverage")
{
    int arr[5] = { 5, 3, 9, 1, 7 };
    Data data;
    data.arr = arr;
    data.size = 5;

    min_max_thread(&data);
    average_thread(&data);

    for (int i = 0; i < data.size; i++) {
        if (arr[i] == data.min || arr[i] == data.max)
            arr[i] = static_cast<int>(data.average);
    }

    int expected[5] = { 5, 3, 5, 5, 7 };
    for (int i = 0; i < data.size; i++)
        CHECK(arr[i] == expected[i]);
}
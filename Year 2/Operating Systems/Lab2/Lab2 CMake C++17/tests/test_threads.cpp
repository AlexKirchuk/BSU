#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest.h>
#include "data.h"
#include "minmax.h"
#include "average.h"
#include <mutex>

std::mutex console_mutex;

TEST_CASE("TestMinMax")
{
    Data data;
    data.arr = { 5, 3, 9, 1, 7 };

    min_max_thread(data);

    CHECK(data.min == 1);
    CHECK(data.max == 9);
}

TEST_CASE("TestAverage")
{
    Data data;
    data.arr = { 5, 3, 9, 1, 7 };

    average_thread(data);

    CHECK(data.average == doctest::Approx(5.0));
}

TEST_CASE("TestReplaceMinMaxWithAverage")
{
    Data data;
    data.arr = { 5, 3, 9, 1, 7 };

    min_max_thread(data);
    average_thread(data);

    for (int& value : data.arr)
    {
        if (value == data.min || value == data.max)
            value = static_cast<int>(data.average);
    }

    std::vector<int> expected = { 5, 3, 5, 5, 7 };
    CHECK(data.arr == expected);
}

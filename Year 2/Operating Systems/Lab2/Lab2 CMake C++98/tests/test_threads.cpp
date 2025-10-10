#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest.h>
#include <boost/shared_ptr.hpp>
#include <data.h>
#include <minmax.h>
#include <average.h>
#include <windows.h>
#include <iostream>

HANDLE hConsoleMutex = CreateMutex(NULL, FALSE, NULL);

boost::shared_ptr<Data> make_data(const int* values, int n)
{
    boost::shared_ptr<Data> data(new Data(n));
    for (int i = 0; i < n; ++i)
        data->push(values[i]);
    return data;
}

template<typename ThreadFunc>
void run_thread(ThreadFunc func, boost::shared_ptr<Data> data)
{ func(new boost::shared_ptr<Data>(data)); }

TEST_CASE("TestMinMax")
{
    int values[5] = { 5, 3, 9, 1, 7 };
    boost::shared_ptr<Data> data = make_data(values, 5);

    run_thread(min_max_thread, data);

    CHECK(data->min == 1);
    CHECK(data->max == 9);
}

TEST_CASE("TestAverage")
{
    int values[5] = { 5, 3, 9, 1, 7 };
    boost::shared_ptr<Data> data = make_data(values, 5);

    run_thread(average_thread, data);

    CHECK(data->average == doctest::Approx(5.0));
}

TEST_CASE("TestReplaceMinMaxWithAverage")
{
    int values[5] = { 5, 3, 9, 1, 7 };
    boost::shared_ptr<Data> data = make_data(values, 5);

    run_thread(min_max_thread, data);
    run_thread(average_thread, data);

    for (int i = 0; i < data->size; ++i)
    {
        if (data->arr[i] == data->min || data->arr[i] == data->max)
            data->arr[i] = static_cast<int>(data->average);
    }

    int expected[5] = { 5, 3, 5, 5, 7 };
    for (int i = 0; i < data->size; ++i)
        CHECK(data->arr[i] == expected[i]);
}
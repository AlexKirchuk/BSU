#define BOOST_TEST_MODULE Lab3Tests
#include <boost/test/included/unit_test.hpp>
#include <boost/shared_ptr.hpp>
#include <windows.h>
#include <array.h>
#include <marker.h>

HANDLE startEvent;
CRITICAL_SECTION coutCS;

struct ThreadData
{
    Array* arr;
    int index;
    int value;
};

BOOST_AUTO_TEST_CASE(BasicOperations)
{
    Array arr(5);
    BOOST_CHECK_EQUAL(arr.getSize(), 5);

    arr.set(2, 42);
    BOOST_CHECK_EQUAL(arr.get(2), 42);

    arr.set(0, -7);
    BOOST_CHECK_EQUAL(arr.get(0), -7);
}

BOOST_AUTO_TEST_CASE(ClearValue)
{
    Array arr(4);
    arr.set(1, 10);
    arr.set(3, 10);
    arr.clearValue(10);

    BOOST_CHECK_EQUAL(arr.get(1), 0);
    BOOST_CHECK_EQUAL(arr.get(3), 0);
    BOOST_CHECK_EQUAL(arr.get(0), 0);
    BOOST_CHECK_EQUAL(arr.get(2), 0);
}

DWORD WINAPI ThreadFunc(LPVOID param)
{
    ThreadData* data = static_cast<ThreadData*>(param);
    data->arr->set(data->index, data->value);
    return 0;
}

BOOST_AUTO_TEST_CASE(MultiThreadedSet)
{
    Array arr(10);
    ThreadData td[5];

    HANDLE threads[5];
    for (int i = 0; i < 5; i++)
    {
        td[i].arr = &arr;
        td[i].index = i;
        td[i].value = (i + 1) * 10;
        threads[i] = CreateThread(0, 0, ThreadFunc, &td[i], 0, 0);
    }

    WaitForMultipleObjects(5, threads, TRUE, INFINITE);

    for (int i = 0; i < 5; i++)
    {
        BOOST_CHECK_EQUAL(arr.get(i), (i + 1) * 10);
        CloseHandle(threads[i]);
    }
}

BOOST_AUTO_TEST_CASE(InitialZero)
{
    Array arr(7);
    for (int i = 0; i < 7; i++)
        BOOST_CHECK_EQUAL(arr.get(i), 0);
}

BOOST_AUTO_TEST_CASE(MarkerDataInit)
{
    boost::shared_ptr<Array> arr = boost::make_shared<Array>(5);

    MarkerData marker;
    marker.id = 1;
    marker.sharedArray = arr;
    marker.terminate = false;
    marker.active = true;

    BOOST_CHECK_EQUAL(marker.id, 1);
    BOOST_CHECK(marker.sharedArray != nullptr);
    BOOST_CHECK(!marker.terminate);
    BOOST_CHECK(marker.active);
}
#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <array.h>
#include <marker.h>
#include <thread>
#include <memory>
#include <vector>
#include <chrono>

TEST_CASE("Array basic operations")
{
    Array arr(5);
    REQUIRE(arr.getSize() == 5);

    arr.set(2, 42);
    REQUIRE(arr.get(2) == 42);

    arr.set(0, -7);
    REQUIRE(arr.get(0) == -7);
}

TEST_CASE("Array clearValue")
{
    Array arr(4);
    arr.set(1, 10);
    arr.set(3, 10);
    arr.clearValue(10);

    REQUIRE(arr.get(1) == 0);
    REQUIRE(arr.get(3) == 0);
    REQUIRE(arr.get(0) == 0);
    REQUIRE(arr.get(2) == 0);
}

TEST_CASE("Array initial zeros")
{
    Array arr(7);
    for (int i = 0; i < arr.getSize(); ++i)
        REQUIRE(arr.get(i) == 0);
}

TEST_CASE("Array multi-threaded set")
{
    Array arr(10);
    std::vector<std::thread> threads;

    for (int i = 0; i < 5; ++i)
    {
        threads.emplace_back([&arr, i]
            { arr.set(i, (i + 1) * 10); });
    }

    for (auto& t : threads) t.join();

    for (int i = 0; i < 5; ++i)
        REQUIRE(arr.get(i) == (i + 1) * 10);
}

TEST_CASE("MarkerData initialization")
{
    auto arr = std::make_shared<Array>(5);
    MarkerData marker;
    marker.id = 1;
    marker.sharedArray = arr;
    marker.terminate = false;
    marker.active = true;

    REQUIRE(marker.id == 1);
    REQUIRE(marker.sharedArray != nullptr);
    REQUIRE(!marker.terminate);
    REQUIRE(marker.active);
}

TEST_CASE("Marker multi-threaded simulation", "[threads]")
{
    const int N = 5;
    std::vector<std::thread> threads;
    std::vector<std::atomic<bool>> found(N);

    for (auto& f : found) f = false;

    for (int i = 0; i < N; ++i)
    {
        threads.emplace_back([i, &found]()
            {
                std::this_thread::sleep_for(std::chrono::milliseconds(20 * i));
                found[i] = true;
            });
    }

    for (auto& t : threads) t.join();

    for (int i = 0; i < N; ++i)
    {
        INFO("Index " << i << " was not set to true as expected");
        REQUIRE(found[i]);
    }
}
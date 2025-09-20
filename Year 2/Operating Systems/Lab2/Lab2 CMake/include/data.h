#pragma once

struct Data
{
    int* arr;
    int size;
    int min;
    int max;
    double average;

    Data() : arr(nullptr), size(0), min(0), max(0), average(0.0) {}
};
#include <data.h>

Data::Data(int n) : arr(new int[n]), size(0), min(0), max(0), average(0.0) {}

void Data::push(int value)
{ arr[size++] = value; }
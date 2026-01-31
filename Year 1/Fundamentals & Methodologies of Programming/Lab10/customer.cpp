#include "customer.h"

Customer::Customer() : id(0), purchases(0) {}
Customer::Customer(const int i, const int p) : id(i), purchases(p) {}
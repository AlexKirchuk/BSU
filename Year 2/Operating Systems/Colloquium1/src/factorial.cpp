#include <factorial.h>
#include <stdexcept>

std::vector<long long> generateFactorials(int n)
{
    if (n == 0)
        throw std::invalid_argument("Input must be a natural number greater than 0.");
    
    std::vector<long long> factorials;
    factorials.reserve(n);

    long long current = 1;
    for (int i = 1; i <= n; ++i)
    {
        if (i > 20)
            throw std::overflow_error("Factorial too large to fit in long long.");
        
        current = i == 1 ? 1 : current * i;
        factorials.push_back(current);
    }

    return factorials;
}
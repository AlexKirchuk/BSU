#include <unique.h>
#include <set>

template <typename T>
std::vector<T> removeDuplicates(const std::vector<T>& input)
{
    std::set<T> seen;
    std::vector<T> result;
    result.reserve(input.size());

    for (const auto& item : input)
    {
        if (seen.insert(item).second)
            result.push_back(item);
    }
    return result;
}
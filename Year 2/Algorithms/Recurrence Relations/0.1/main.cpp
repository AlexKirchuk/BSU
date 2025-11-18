#include <iostream>
#include <vector>

int main() {
    long long n;
    std::cin >> n;

    long long* arr = new long long[n];
    for (long long i = 0; i < n; i++)
    {
        std::cin >> arr[i];
    }

    std::vector<std::pair<long long, long long>> path(n);

    for (int i = 0; i < n; i++)
    {
        path[i].first = -1;
        path[i].second = -1;
    }

    path[0].first = arr[0];
    long long content;

    for (long long i = 0; i < n; i++)
    {
        if (path[i].first == -1) continue;

        if (i + 2 <= n - 1)
        {
            content = path[i].first + arr[i + 2];
            if (content > path[i + 2].first)
            {
                path[i + 2].first = content;
                path[i + 2].second = i;
            }
        }

        if (i + 3 <= n - 1)
        {
            content = path[i].first + arr[i + 3];
            if (content > path[i + 3].first)
            {
                path[i + 3].first = content;
                path[i + 3].second = i;
            }
        }
    }

    if (path[n - 1].first == -1)
    {
        std::cout << -1 << std::endl;
        return -1;
    }

    std::cout << path[n - 1].first << std::endl;

    std::vector<long long> track;
    for (long long i = n - 1; i != -1; i = path[i].second)
    {
        track.push_back(i);
    }

    for (long long i = track.size() - 1; i >= 0; i--)
    {
        std::cout << track[i] + 1 << " ";
    }

    return 0;
}
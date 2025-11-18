#include <iostream>
#include <fstream>
#include <vector>

int main()
{
    std::ifstream in("bst.in");
    std::ofstream out("bst.out");

    int n;
    in >> n;

    std::vector<long long> key(n);
    std::vector<int> parent(n, -1);
    std::vector<bool> isLeft(n, false);
    std::vector<long long> low(n), high(n);

    in >> key[0];

    for (int i = 1; i < n; i++)
    {
        int p;
        char c;
        in >> key[i] >> p >> c;
        parent[i] = p - 1;
        isLeft[i] = (c == 'L');
    }

    const long long INF = LLONG_MAX;
    low[0] = -INF;
    high[0] = INF;

    bool ok = true;

    for (int i = 1; i < n; i++)
    {
        int p = parent[i];
        if (isLeft[i])
        {
            low[i] = low[p];
            high[i] = key[p];
        }
        else
        {
            low[i] = key[p];
            high[i] = high[p];
        }

        if (!(low[i] <= key[i] && key[i] < high[i]))
        {
            ok = false;
            break;
        }
    }

    out << (ok ? "YES" : "NO");

    return 0;
}
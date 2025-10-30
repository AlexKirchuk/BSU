#include <fstream>
#include <vector>

int main()
{
    std::ifstream in("huffman.in");
    std::ofstream out("huffman.out");

    int n;
    in >> n;

    std::vector<long long> a(n);
    for (int i = 0; i < n; ++i)
    {
        in >> a[i];
    }

    std::vector<long long> b;
    b.reserve(n - 1);

    long long ans = 0;
    int i = 0, j = 0;

    while (true)
    {
        long long x, y;

        if (i < n && (j >= b.size() || a[i] < b[j]))
        {
            x = a[i++];
        }
        else
        {
            x = b[j++];
        }

        if (i < n && (j >= b.size() || a[i] < b[j]))
        {
            y = a[i++];
        }
        else
        {
            y = b[j++];
        }

        long long sum = x + y;
        ans += sum;
        b.push_back(sum);

        if (i + j == n + b.size() - 1)
        {
            break;
        }
    }

    out << ans;
    return 0;
}
#include <fstream>
#include <queue>
#include <vector>

int main()
{
    std::ifstream in("huffman.in");
    std::ofstream out("huffman.out");

    int n;
    in >> n;

    std::priority_queue<long long, std::vector<long long>, std::greater<long long>> pq;

    for (int i = 0; i < n; ++i)
    {
        long long x;
        in >> x;
        pq.push(x);
    }

    long long ans = 0;

    while (pq.size() > 1)
    {
        long long a = pq.top();
        pq.pop();
        long long b = pq.top();
        pq.pop();

        long long sum = a + b;
        ans += sum;
        pq.push(sum);
    }

    out << ans;
    return 0;
}
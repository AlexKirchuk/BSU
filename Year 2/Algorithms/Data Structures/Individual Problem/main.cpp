#include <fstream>
#include <vector>
#include <algorithm>
#include <set>

int main()
{
    std::ifstream fin("input.txt");
    std::ofstream fout("output.txt");

    long long n, w, h;
    fin >> n >> w >> h;

    std::vector<std::pair<long long, long long>> trees(n);
    for (long long i = 0; i < n; i++)
    {
        fin >> trees[i].first >> trees[i].second;
    }

    trees.push_back({ 0, -1 });
    trees.push_back({ w, -1 });

    std::sort(trees.begin(), trees.end());
    n = trees.size();

    long long maxArea = 0;

    for (long long i = 0; i < n; i++)
    {
        std::set<long long> ys;
        ys.insert(0);
        ys.insert(h);

        std::multiset<long long> gaps;
        gaps.insert(h);

        auto addY = [&](long long y)
            {
                if ((ys.find(y) != ys.end())) { return; }

                auto itR = ys.lower_bound(y);
                auto itL = itR;
                if (itL == ys.begin()) { ys.insert(y); return; }
                --itL;

                long long left = *itL;
                long long right = *itR;

                gaps.erase(gaps.find(right - left));
                gaps.insert(y - left);
                gaps.insert(right - y);

                ys.insert(y);
            };

        for (long long j = i + 1; j < n; j++)
        {
            long long width = trees[j].first - trees[i].first;
            long long height = *(gaps.rbegin());
            long long area = width * height;

            if (area > maxArea)
            {
                maxArea = area;
            }

            if (trees[j].second != -1)
            {
                addY(trees[j].second);
            }
        }
    }

    fout << maxArea;

    fin.close();
    fout.close();
    return 0;
}
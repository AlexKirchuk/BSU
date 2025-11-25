#include <fstream>
#include <set>
#include <vector>
#include <algorithm>

int main()
{
    std::ifstream fin("input.txt");
    std::ofstream fout("output.txt");

    int n, w, h, maxArea = 0;
    fin >> n >> w >> h;

    std::set<int> xs, ys;
    std::vector<std::pair<int, int>> trees(n);
    xs.insert(0);
    xs.insert(w);
    ys.insert(0);
    ys.insert(h);

    for (int i = 0; i < n; i++)
    {
        fin >> trees[i].first >> trees[i].second;
        xs.insert(trees[i].first);
        ys.insert(trees[i].second);
    }

    std::vector<int> cx(xs.begin(), xs.end());
    std::vector<int> cy(ys.begin(), ys.end());

    auto getX = [&](int x)
        {
            return std::lower_bound(cx.begin(), cx.end(), x) - cx.begin();
        };
    auto getY = [&](int y)
        {
            return std::lower_bound(cy.begin(), cy.end(), y) - cy.begin();
        };

    for (auto& t : trees)
    {
        t.first = getX(t.first);
        t.second = getY(t.second);
    }

    int X = cx.size(), Y = cy.size();
    std::vector<std::vector<int>> grid(X, std::vector<int>(Y, 0));
    for (auto& t : trees)
    {
        grid[t.first][t.second] = 1;
    }

    std::vector<std::vector<int>> pref(X + 1, std::vector<int>(Y + 1, 0));
    for (int i = 1; i <= X; i++)
    {
        for (int j = 1; j <= Y; j++)
        {
            pref[i][j] = grid[i - 1][j - 1] + pref[i - 1][j] + pref[i][j - 1] - pref[i - 1][j - 1];
        }
    }

    for (int y1 = 0; y1 < Y; ++y1)
    {
        for (int y2 = y1 + 1; y2 < Y; ++y2)
        {
            std::vector<int> nonEmpty(X, 0);
            for (int x = 0; x < X; ++x)
            {
                int cnt = pref[x + 1][y2] - pref[x][y2] - pref[x + 1][y1 + 1] + pref[x][y1 + 1];
                if (cnt > 0)
                {
                    nonEmpty[x] = 1;
                }
                else
                {
                    nonEmpty[x] = 0;
                }
            }
            int a = 0, non = 0;
            for (int b = 1; b < X; ++b)
            {
                non += nonEmpty[b - 1];
                while (a + 1 < b && non > 0)
                {
                    non -= nonEmpty[a + 1];
                    ++a;
                }
                int width = cx[b] - cx[a];
                int height = cy[y2] - cy[y1];
                int area = width * height;
                if (area > maxArea) maxArea = area;
            }
        }
    }

    fout << maxArea;
    fin.close();
    fout.close();
    return 0;
}
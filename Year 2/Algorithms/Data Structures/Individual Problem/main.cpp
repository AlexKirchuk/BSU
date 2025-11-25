#include <fstream>
#include <set>

int main()
{
    std::ifstream fin("input.txt");
    std::ofstream fout("output.txt");

    int n, w, h, maxArea = 0;
    fin >> n >> w >> h;

    std::set<int> xs, ys;
    std::set<std::pair<int, int>> trees;
    xs.insert(0);
    xs.insert(w);
    ys.insert(0);
    ys.insert(h);

    for (int i = 0; i < n; i++)
    {
        int fst, snd;
        fin >> fst >> snd;
        xs.insert(fst);
        ys.insert(snd);
        trees.insert({ fst, snd });
    }

    for (auto it1 = xs.begin(); it1 != xs.end(); ++it1)
    {
        for (auto it2 = std::next(it1); it2 != xs.end(); ++it2)
        {
            int x1 = *it1;
            int x2 = *it2;

            for (auto jt1 = ys.begin(); jt1 != ys.end(); ++jt1)
            {
                for (auto jt2 = std::next(jt1); jt2 != ys.end(); ++jt2)
                {
                    int y1 = *jt1;
                    int y2 = *jt2;

                    bool has_tree_inside = false;

                    for (auto& t : trees)
                    {
                        int tx = t.first, ty = t.second;
                        if (tx > x1 && tx < x2 && ty > y1 && ty < y2)
                        {
                            has_tree_inside = true;
                            break;
                        }
                    }

                    if (!has_tree_inside)
                    {
                        int area = (x2 - x1) * (y2 - y1);
                        if (area > maxArea)
                        {
                            maxArea = area;
                        }
                    }
                }
            }
        }
    }

    fout << maxArea;
    fin.close();
    fout.close();
    return 0;
}
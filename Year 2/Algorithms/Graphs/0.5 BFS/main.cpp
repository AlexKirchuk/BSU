#include <fstream>
#include <vector>
#include <queue>

int main()
{
    std::ifstream fin("input.txt");
    std::ofstream fout("output.txt");

    int n;
    fin >> n;

    std::vector<std::vector<int>> adjacency(n, std::vector<int>(n));

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            fin >> adjacency[i][j];
        }
    }

    std::vector<bool> visited(n, false);
    std::vector<int> order(n, 0);
    int currentLabel = 1;

    for (int start = 0; start < n; start++)
    {
        if (!visited[start])
        {
            std::queue<int> q;
            visited[start] = true;
            q.push(start);
            order[start] = currentLabel++;

            while (!q.empty())
            {
                int v = q.front();
                q.pop();

                std::vector<int> neighbors;
                for (int u = 0; u < n; u++)
                {
                    if (adjacency[v][u] && !visited[u])
                    {
                        neighbors.push_back(u);
                    }
                }

                for (int u : neighbors)
                {
                    visited[u] = true;
                    order[u] = currentLabel++;
                    q.push(u);
                }
            }
        }
    }

    for (int i = 0; i < order.size(); i++)
    {
        fout << order[i] << " ";
    }

    fin.close();
    fout.close();
    return 0;
}
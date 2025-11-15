#include <fstream>
#include <vector>
#include <stack>
#include <algorithm>

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
            std::stack<int> st;
            st.push(start);

            while (!st.empty())
            {
                int v = st.top();
                st.pop();

                if (!visited[v])
                {
                    visited[v] = true;
                    order[v] = currentLabel++;

                    std::vector<int> neighbors;
                    for (int u = 0; u < n; u++)
                    {
                        if (adjacency[v][u] && !visited[u])
                        {
                            neighbors.push_back(u);
                        }
                    }

                    std::sort(neighbors.rbegin(), neighbors.rend());

                    for (int u : neighbors)
                    {
                        st.push(u);
                    }
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
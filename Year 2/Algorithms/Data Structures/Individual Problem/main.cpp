#include <fstream>
#include <vector>
#include <algorithm>

struct Node
{
    int x;
    int count;
    Node* prev;
    Node* next;
    Node(int _x) : x(_x), count(0), prev(nullptr), next(nullptr) {}
};

int main()
{
    std::ifstream fin("input.txt");
    std::ofstream fout("output.txt");

    int n, w, h;
    fin >> n >> w >> h;

    std::vector<int> X(n), Y(n);
    for (int i = 0; i < n; i++)
    {
        fin >> X[i] >> Y[i];
    }

    std::vector<int> xs = X;
    std::sort(xs.begin(), xs.end());
    xs.erase(std::unique(xs.begin(), xs.end()), xs.end());
    int m = xs.size();

    std::vector<int> Xc(n);
    for (int i = 0; i < n; i++)
    {
        Xc[i] = std::lower_bound(xs.begin(), xs.end(), X[i]) - xs.begin();
    }

    std::vector<std::pair<int,int>> trees(n);
    for (int i = 0; i < n; i++)
    {
        trees[i] = { Y[i], Xc[i] };
    }
    std::sort(trees.begin(), trees.end(), [](auto& a, auto& b)
    {
        return a.first > b.first;
    });

    std::vector<int> yValues;
    yValues.push_back(0);
    for (int i = 0; i < n; i++)
    {
        yValues.push_back(trees[i].first);
    }

    int maxArea = 0;

    for (int bi = 0; bi < yValues.size(); bi++)
    {
        int ymin = yValues[bi];

        std::vector<int> count(m, 0);
        for (int i = 0; i < n; i++)
        {
            if (trees[i].first > ymin)
            {
                count[trees[i].second]++;
            }
        }

        std::vector<Node*> nodes(m, nullptr);
        Node* head = nullptr;
        Node* prev = nullptr;
        for (int i = 0; i < m; i++)
        {
            if (count[i] > 0)
            {
                Node* node = new Node(i);
                node->count = count[i];
                nodes[i] = node;
                if (!head)
                {
                    head = node;
                }
                node->prev = prev;
                if (prev)
                {
                    prev->next = node;
                }
                prev = node;
            }
        }

        int maxGap = 0;
        if (head)
        {
            maxGap = std::max(xs[head->x], w - xs[prev->x]);
            Node* cur = head;
            while (cur->next)
            {
                maxGap = std::max(maxGap, xs[cur->next->x] - xs[cur->x]);
                cur = cur->next;
            }
        }
        else
        {
            maxGap = w;
        }

        maxArea = std::max(maxArea, maxGap * (h - ymin));

        int top = h;
        for (int i = 0; i < n; i++)
        {
            if (trees[i].first <= ymin)
            {
                break;
            }
            int xi = trees[i].second;

            Node* node = nodes[xi];
            node->count--;
            if (node->count == 0)
            {
                int left, right;
                if (node->prev)
                {
                    left = xs[node->x] - xs[node->prev->x];
                }
                else
                {
                    left = xs[node->x];
                }
                if (node->next)
                {
                    right = xs[node->next->x] - xs[node->x];
                }
                else
                {
                    right = w - xs[node->x];
                }
                int combined = left + right;
                maxGap = std::max(maxGap, combined);

                if (node->prev)
                {
                    node->prev->next = node->next;
                }
                if (node->next)
                {
                    node->next->prev = node->prev;
                }
                if (head == node)
                {
                    head = node->next;
                }
            }

            top = trees[i].first;
            maxArea = std::max(maxArea, maxGap * (top - ymin));
        }

        for (int i = 0; i < m; i++)
        {
            delete nodes[i];
        }
    }

    fout << maxArea;
    return 0;
}
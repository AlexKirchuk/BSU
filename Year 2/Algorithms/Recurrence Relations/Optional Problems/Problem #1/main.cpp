#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <algorithm>

int main()
{
    std::string s;
    std::cin >> s;
    int n = s.size();

    const int ALPH = 26;

    std::vector<std::array<int, ALPH>> next_pos(n + 1);
    for (int c = 0; c < ALPH; c++)
    {
        next_pos[n][c] = -1;
    }

    for (int i = n - 1; i >= 0; i--)
    {
        for (int c = 0; c < ALPH; c++)
        {
            next_pos[i][c] = next_pos[i + 1][c];
        }
        next_pos[i][s[i] - 'a'] = i;
    }

    std::vector<std::array<int, ALPH>> prev_pos(n);
    for (int c = 0; c < ALPH; c++)
    {
        prev_pos[0][c] = -1;
    }
    prev_pos[0][s[0] - 'a'] = 0;

    for (int i = 1; i < n; i++)
    {
        for (int c = 0; c < ALPH; c++)
        {
            prev_pos[i][c] = prev_pos[i - 1][c];
        }
        prev_pos[i][s[i] - 'a'] = i;
    }

    std::vector<std::vector<short>> dp(n);
    for (int i = 0; i < n; i++)
    {
        dp[i].resize(n - i);
    }

    for (int i = n - 1; i >= 0; i--)
    {
        dp[i][0] = 1;
        if (i == n - 1)
        {
            continue;
        }

        for (int k = 1; k < n - i; k++)
        {
            int j = i + k;
            if (s[i] == s[j])
            {
                if (j == i + 1)
                {
                    dp[i][k] = 2;
                }
                else
                {
                    dp[i][k] = 2 + dp[i + 1][(j - 1) - (i + 1)];
                }
            }
            else
            {
                short a = dp[i + 1][k - 1];
                short b = dp[i][k - 1];
                dp[i][k] = (a >= b ? a : b);
            }
        }
    }

    auto build = [&](bool want_max)
        {
            int l = 0;
            int r = n - 1;
            int need = dp[0][n - 1];

            std::string L;
            std::string R;

            while (need > 1 && l <= r)
            {
                int chosen = -1;
                int ci = -1;
                int cj = -1;

                if (!want_max)
                {
                    for (int c = 0; c < ALPH; c++)
                    {
                        int i = next_pos[l][c];
                        if (i == -1 || i > r)
                        {
                            continue;
                        }
                        int j = prev_pos[r][c];
                        if (j == -1 || j < i)
                        {
                            continue;
                        }
                        if (i == j)
                        {
                            continue;
                        }

                        int inner = (i + 1 <= j - 1)
                            ? dp[i + 1][(j - 1) - (i + 1)]
                            : 0;

                        if (2 + inner == need)
                        {
                            chosen = c;
                            ci = i;
                            cj = j;
                            break;
                        }
                    }
                }
                else
                {
                    for (int c = ALPH - 1; c >= 0; c--)
                    {
                        int i = next_pos[l][c];
                        if (i == -1 || i > r)
                        {
                            continue;
                        }
                        int j = prev_pos[r][c];
                        if (j == -1 || j < i)
                        {
                            continue;
                        }
                        if (i == j)
                        {
                            continue;
                        }

                        int inner = (i + 1 <= j - 1)
                            ? dp[i + 1][(j - 1) - (i + 1)]
                            : 0;

                        if (2 + inner == need)
                        {
                            chosen = c;
                            ci = i;
                            cj = j;
                            break;
                        }
                    }
                }

                if (chosen == -1)
                {
                    break;
                }

                char ch = static_cast<char>('a' + chosen);
                L.push_back(ch);
                R.push_back(ch);

                l = ci + 1;
                r = cj - 1;
                need -= 2;
            }

            std::string center;

            if (need == 1)
            {
                if (!want_max)
                {
                    for (int c = 0; c < ALPH; c++)
                    {
                        int i = next_pos[l][c];
                        if (i != -1 && i <= r)
                        {
                            center = static_cast<char>('a' + c);
                            break;
                        }
                    }
                }
                else
                {
                    for (int c = ALPH - 1; c >= 0; c--)
                    {
                        int i = next_pos[l][c];
                        if (i != -1 && i <= r)
                        {
                            center = static_cast<char>('a' + c);
                            break;
                        }
                    }
                }
            }

            std::reverse(R.begin(), R.end());
            return L + center + R;
        };

    std::string mn = build(false);
    std::string mx = build(true);

    std::cout << mn << "\n" << mx << "\n";

    return 0;
}
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <unordered_set>

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int t;
    std::cin >> t;

    while (t--)
    {
        int n, m, k;
        std::cin >> n >> m >> k;

        std::vector<int> a(m);
        for (int i = 0; i < m; ++i)
        {
            std::cin >> a[i];
        }

        std::vector<int> q(k);
        for (int i = 0; i < k; ++i)
        {
            std::cin >> q[i];
        }

        std::unordered_set<int> unknown;
        for (int i = 1; i <= n; ++i)
        {
            unknown.insert(i);
        }

        for (int i = 0; i < k; ++i)
        {
            unknown.erase(q[i]);
        }

        std::string result;
        for (int i = 0; i < m; ++i)
        {
            // For each list, Monocarp can pass if either:
            // 1. The only unknown question is a[i] (the one not in the list)
            // 2. There are no unknown questions

            if (unknown.size() == 1 && unknown.count(a[i]))
            {
                result += '1';
            }
            else if (unknown.empty())
            {
                result += '1';
            }
            else
            {
                result += '0';
            }
        }

        std::cout << result << '\n';
    }

    return 0;
}
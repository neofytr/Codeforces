#include <bits/stdc++.h>
using namespace std;

bool canAchieve(int len, int m, char c, const vector<vector<int>> &prefix)
{
    int id = c - 'a';
    for (int i = 0; i + len <= prefix[0].size() - 1; ++i)
    {
        int diff = prefix[id][i + len] - prefix[id][i];
        if (diff <= m)
            return true;
    }
    return false;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    vector<char> garland(n);
    for (char &color : garland)
    {
        cin >> color;
    }

    int q;
    cin >> q;

    int m;
    char c;

    vector<vector<int>> prefix(26, vector<int>(n + 1, 0));

    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < 26; ++j)
        {
            prefix[j][i + 1] = prefix[j][i] + (garland[i] - 'a' != j);
        }
    }

    while (q--)
    {
        cin >> m >> c;

        // if we can repaint to achieve a koyomity of atleast x, we can repaint to achieve a koyomity of x - 1; x > 1

        // a koyomity of atleast this much is possible since we can choose to repaint none (we can repaint atmost m)
        int left = 0;
        int right = n + 1; // a koyomity of this much is impossible

        while (right != left + 1)
        {
            int mid = left + (right - left) / 2;
            if (canAchieve(mid, m, c, prefix))
            {
                left = mid;
            }
            else
            {
                right = mid;
            }
        }

        cout << left << "\n";
    }

    return EXIT_SUCCESS;
}
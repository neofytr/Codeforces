#include <bits/stdc++.h>
using namespace std;

bool canAchieve(int target, int m, char c, int n, const vector<vector<int>> &prefix)
{
    int cIndex = c - 'a';

    for (int left = 0; left + target <= n; ++left)
    {
        int right = left + target - 1;
        int count = prefix[cIndex][right + 1] - prefix[cIndex][left];
        if (target - count <= m)
            return true;
    }
    return false;
}

int main()
{
    int n;
    cin >> n;

    vector<char> garland(n);
    for (char &val : garland)
        cin >> val;

    int q;
    cin >> q;

    // prefix[ch][i] = count of char ch in garland[0..i-1]
    vector<vector<int>> prefix(26, vector<int>(n + 1, 0));

    for (int i = 0; i < n; i++)
    {
        for (int ch = 0; ch < 26; ch++)
        {
            prefix[ch][i + 1] = prefix[ch][i] + (garland[i] - 'a' == ch ? 1 : 0);
        }
    }

    while (q--)
    {
        int m;
        char c;
        cin >> m >> c;

        int left = 0, right = n + 1;

        while (right != left + 1)
        {
            int mid = (left + right) / 2;
            if (canAchieve(mid, m, c, n, prefix))
                left = mid;
            else
                right = mid;
        }

        cout << left << '\n';
    }

    return 0;
}

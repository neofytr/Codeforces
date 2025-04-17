#include <bits/stdc++.h>
using namespace std;

bool can_make_adjacent(int a1, int a2, int b1, int b2)
{
    // Try all possible swaps

    // Try (a1, b1)
    {
        int new_a1 = b1;
        int new_b1 = a1;

        // Check if a's are adjacent after swap
        if ((abs(new_a1 - a2) == 1) && (abs(new_b1 - b2) == 1))
        {
            return true;
        }
    }

    // Try (a1, b2)
    {
        int new_a1 = b2;
        int new_b2 = a1;

        // Check if a's are adjacent after swap
        if ((abs(new_a1 - a2) == 1) && (abs(b1 - new_b2) == 1))
        {
            return true;
        }
    }

    // Try (a2, b1)
    {
        int new_a2 = b1;
        int new_b1 = a2;

        // Check if a's are adjacent after swap
        if ((abs(a1 - new_a2) == 1) && (abs(new_b1 - b2) == 1))
        {
            return true;
        }
    }

    // Try (a2, b2)
    {
        int new_a2 = b2;
        int new_b2 = a2;

        // Check if a's are adjacent after swap
        if ((abs(a1 - new_a2) == 1) && (abs(b1 - new_b2) == 1))
        {
            return true;
        }
    }

    return false;
}

void solve()
{
    int n;
    cin >> n;
    vector<pair<int, int>> positions(n + 1);

    for (int i = 1; i <= 2 * n; i++)
    {
        int val;
        cin >> val;

        if (positions[val].first == 0)
        {
            positions[val].first = i;
        }
        else
        {
            positions[val].second = i;
        }
    }

    int ans = 0;

    for (int a = 1; a <= n; a++)
    {
        if (abs(positions[a].first - positions[a].second) == 1)
            continue;

        for (int b = a + 1; b <= n; b++)
        {
            if (abs(positions[b].first - positions[b].second) == 1)
                continue;

            int a1 = positions[a].first;
            int a2 = positions[a].second;
            int b1 = positions[b].first;
            int b2 = positions[b].second;

            if (can_make_adjacent(a1, a2, b1, b2))
            {
                ans++;
            }
        }
    }

    cout << ans << endl;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}
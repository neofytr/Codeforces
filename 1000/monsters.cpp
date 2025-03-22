#include <bits/stdc++.h>
using namespace std;

void solve()
{
    int64_t n, k;
    cin >> n >> k;

    vector<int64_t> health(n);
    for (int i = 0; i < n; i++)
    {
        cin >> health[i];
    }

    // Calculate defeat order directly
    vector<int> defeat_order;
    vector<bool> defeated(n, false);

    while (defeat_order.size() < n)
    {
        // Find monster with maximum health (and minimum index for tiebreaker)
        int max_idx = -1;
        int64_t max_health = -1;

        for (int i = 0; i < n; i++)
        {
            if (defeated[i])
                continue;

            if (max_idx == -1 || health[i] > max_health ||
                (health[i] == max_health && i < max_idx))
            {
                max_idx = i;
                max_health = health[i];
            }
        }

        // Attack this monster
        health[max_idx] -= k;

        // Check if defeated
        if (health[max_idx] <= 0)
        {
            defeat_order.push_back(max_idx);
            defeated[max_idx] = true;
        }
    }

    // Output defeat order (1-indexed)
    for (int idx : defeat_order)
    {
        cout << idx + 1 << " ";
    }
    cout << endl;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--)
    {
        solve();
    }

    return 0;
}
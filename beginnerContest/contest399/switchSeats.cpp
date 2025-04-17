#include <bits/stdc++.h>
using namespace std;

void solve()
{
    int n;
    cin >> n;

    vector<pair<int, int>> positions(n + 1);
    vector<int> value_at_pos(2 * n + 1);

    for (int i = 1; i <= 2 * n; i++)
    {
        int val;
        cin >> val;
        value_at_pos[i] = val;

        if (positions[val].first == 0)
            positions[val].first = i;
        else
            positions[val].second = i;
    }

    set<pair<int, int>> counted_pairs;

    for (int i = 1; i <= 2 * n; i++)
    {
        for (int j = 1; j <= 2 * n; j++)
        {
            if (i == j)
                continue;

            int val_i = value_at_pos[i];
            int val_j = value_at_pos[j];

            if (val_i == val_j ||
                abs(positions[val_i].first - positions[val_i].second) == 1 ||
                abs(positions[val_j].first - positions[val_j].second) == 1)
                continue;

            if (counted_pairs.count({min(val_i, val_j), max(val_i, val_j)}))
                continue;

            int other_i = (positions[val_i].first == i) ? positions[val_i].second : positions[val_i].first;
            int other_j = (positions[val_j].first == j) ? positions[val_j].second : positions[val_j].first;

            if (abs(j - other_i) == 1 && abs(i - other_j) == 1)
            {
                counted_pairs.insert({min(val_i, val_j), max(val_i, val_j)});
            }
        }
    }

    cout << counted_pairs.size() << endl;
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
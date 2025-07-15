#include <bits/stdc++.h>
using namespace std;

void solve()
{
    int n;
    cin >> n;

    vector<pair<int, int>> positions(n + 1);
    vector<int> value_at_pos(2 * n + 1, 0);

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

    vector<int> non_adjacent;
    for (int i = 1; i <= n; i++)
    {
        if (abs(positions[i].first - positions[i].second) != 1)
            non_adjacent.push_back(i);
    }

    set<pair<int, int>> valid_pairs;

    for (int pos1 = 1; pos1 <= 2 * n; pos1++)
    {
        int val1 = value_at_pos[pos1];

        if (abs(positions[val1].first - positions[val1].second) == 1)
            continue;

        int other_pos1 = (positions[val1].first == pos1) ? positions[val1].second : positions[val1].first;

        for (int adj_pos : {pos1 - 1, pos1 + 1})
        {
            if (adj_pos < 1 || adj_pos > 2 * n)
                continue;

            int val2 = value_at_pos[adj_pos];

            if (val1 == val2 || abs(positions[val2].first - positions[val2].second) == 1)
                continue;

            int other_pos2 = (positions[val2].first == adj_pos) ? positions[val2].second : positions[val2].first;

            if (abs(other_pos1 - other_pos2) == 1)
            {
                valid_pairs.insert({min(val1, val2), max(val1, val2)});
            }
        }
    }

    cout << valid_pairs.size() << endl;
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
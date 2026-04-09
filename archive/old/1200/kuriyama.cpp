// https://codeforces.com/contest/433/problem/B

#include <bits/stdc++.h>
using namespace std;

void solve()
{
    int n;
    cin >> n;

    vector<long long> cost(n);
    for (long long &val : cost)
    {
        cin >> val;
    }

    vector<long long> sorted_cost = cost;

    sort(sorted_cost.begin(), sorted_cost.end());

    vector<long long> prefix_one(n + 1);
    vector<long long> prefix_two(n + 1);
    prefix_one[0] = prefix_two[0] = 0;

    for (int index = 1; index < n + 1; index++)
    {
        prefix_one[index] = cost[index - 1] + prefix_one[index - 1];
        prefix_two[index] = sorted_cost[index - 1] + prefix_two[index - 1];
    }

    int m;
    cin >> m;

    int type, l, r;
    while (m--)
    {
        cin >> type >> l >> r;

        // convert to zero based indexing
        l--, r--;
        if (type == 1)
        {
            cout << prefix_one[r + 1] - prefix_one[l] << "\n";
        }
        else
        {
            cout << prefix_two[r + 1] - prefix_two[l] << "\n";
        }
    }
}

int main()
{
    solve();
    return EXIT_SUCCESS;
}
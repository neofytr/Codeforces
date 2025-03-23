#include <bits/stdc++.h>
using namespace std;

void solve()
{
    size_t n, m, k;
    cin >> n >> m >> k;

    vector<long long> arr(n);
    for (auto &val : arr)
    {
        cin >> val;
    }

    vector<tuple<size_t, size_t, long long>> operations(m); // l, r, d
    for (auto &trips : operations)
    {
        cin >> get<0>(trips) >> get<1>(trips) >> get<2>(trips);
        get<0>(trips)--;
        get<1>(trips)--;
    }

    // count how many times each operation is applied
    vector<long long> op_counts(m, 0);

    for (size_t query = 0; query < k; query++)
    {
        size_t x, y;
        cin >> x >> y;
        x--, y--;

        // increment count for operations x through y
        for (size_t i = x; i <= y; i++)
        {
            op_counts[i]++;
        }
    }

    vector<long long> prefix(n, 0);

    for (size_t i = 0; i < m; i++)
    {
        if (!op_counts[i])
            continue;

        auto [l, r, d] = operations[i];
        prefix[l] += d * op_counts[i];
        if (r + 1 < n)
        {
            prefix[r + 1] -= d * op_counts[i];
        }
    }

    for (size_t i = 1; i < n; i++)
    {
        prefix[i] += prefix[i - 1];
    }

    for (size_t i = 0; i < n; i++)
    {
        arr[i] += prefix[i];
        cout << arr[i] << " ";
    }

    cout << endl;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    solve();
    return 0;
}
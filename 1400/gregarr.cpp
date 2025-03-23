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

    // use a prefix array to count operation applications
    vector<long long> op_counts(m + 1, 0);

    for (size_t query = 0; query < k; query++)
    {
        size_t x, y;
        cin >> x >> y;
        x--, y--;

        // mark the range [x,y] using prefix technique
        op_counts[x]++;
        op_counts[y + 1]--; // decrement at y+1 to end the range
    }

    // propagate the prefix sum to get the actual count of each operation
    for (size_t i = 1; i < m; i++)
    {
        op_counts[i] += op_counts[i - 1];
    }

    // apply operations with their counts using another prefix array
    vector<long long> prefix(n, 0);

    for (size_t i = 0; i < m; i++)
    {
        if (op_counts[i] == 0)
            continue;

        auto [l, r, d] = operations[i];
        prefix[l] += d * op_counts[i];
        if (r + 1 < n)
        {
            prefix[r + 1] -= d * op_counts[i];
        }
    }

    // propagate the final prefix sum
    for (size_t i = 1; i < n; i++)
    {
        prefix[i] += prefix[i - 1];
    }

    // apply to original array and output
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
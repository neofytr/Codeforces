#include <bits/stdc++.h>
using namespace std;

#define int long long

// Problem: maxSubarraySumTwo
// URL: https://cses.fi/problemset/task/1644
// Difficulty: hard
// Tags:
// Strategy:

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, a, b;
    cin >> n >> a >> b;

    vector<int> arr(n);
    for (int &val : arr)
        cin >> val;

    vector<int> prefix(n + 1, 0);
    for (int r = 1; r <= n; r++)
        prefix[r] = prefix[r - 1] + arr[r - 1];

    // b >= a >= 1
    // we are to find the maximum sum of values in a contiguous subarray with length between a and b
    // to do this, we find the max(maximum sum of values in a contiguous subarray ending at r with length between a and b, for 0 <= r < n)

    // maximum sum of values in a contiguous subarray ending at r with length between a and b
    // = max(sum[l, r] for r - b + 1 <= l <= r - a + 1)
    // = max(prefix[r + 1] - prefix[l] for r - b + 1 <= l <= r - a + 1)

    // ans = max(max(prefix[r + 1] - prefix[l] for max(0, r - b + 1) <= l <= max(r - a + 1, 0) for 0 <= r < n)

    // so we have a sliding window for the range of l as we move r
    multiset<int> mini;
    int maxi = LLONG_MIN;
    for (int r = 0; r < n; r++) {
        if (r - a + 1 >= 0) // insert to the right end of the sliding window
            mini.insert(prefix[r - a + 1]);
        if (r - b >= 0)
            mini.erase(mini.find(prefix[r - b])); // remove from the left end of the sliding window
        if (r - a + 1 >= 0)
            maxi = max(maxi, prefix[r + 1] - *mini.begin());
    }
    cout << maxi << endl;
    return 0;
}

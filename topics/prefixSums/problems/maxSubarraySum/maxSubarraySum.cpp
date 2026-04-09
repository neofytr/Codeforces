#include <bits/stdc++.h>
using namespace std;

#define int long long

// Problem: maxSubarraySum
// URL: https://cses.fi/problemset/task/1643
// Difficulty: medium
// Tags:
// Strategy:

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;
    vector<int> arr(n);
    for (int &val : arr)
        cin >> val;

    // the following is the DP solution
    /*
    // dp[r] is the maximum subarray sum among all the subarrays that end at r
    vector<int> dp(n);
    dp[0] = arr[0];
    int maxi = dp[0];
    for (int r = 1; r < n; r++) {
        dp[r] = max(dp[r - 1] + arr[r], arr[r]);
        maxi = max(maxi, dp[r]);
    }
    cout << maxi << endl;
    */

    // the following is the prefix sum solution?
    vector<int> prefix(n + 1, 0);
    for (int index = 1; index <= n; index++)
        prefix[index] = prefix[index - 1] + arr[index - 1];
    // we find the maximum subarray sum among all subarrays that end at r, for all 0<= r < n
    // for any 0 <= r < n, maximum subarray sum ending at r = max(sum[l, r] for 0 <= l < r)
    //                                                      = max(prefix[r + 1] - prefix[l] for 0 <= l <= r)
    //                                                      = prefix[r + 1] - min(prefix[l] for 0 <= l <= r)
    // so, if for each 0 <= r < n, we can have the minimum among the following {prefix[0], ..., prefix[r]}, we are done

    int mini = prefix[0];
    int maxiSum = LLONG_MIN;
    for (int r = 0; r < n; r++) {
        maxiSum = max(maxiSum, prefix[r + 1] - mini); // prefix[r + 1] - mini is the max subarray sum ending at r
        mini = min(mini, prefix[r + 1]);              // update the mini for the next round
    }
    cout << maxiSum << endl;
    return 0;
}
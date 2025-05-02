#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    long long target;
    cin >> n >> target;

    vector<long long> arr(n);
    for (auto &val: arr) cin >> val;

    // we want to count the number of subsets of arr with 'sum' = target

    // 2D DP solution
    vector<vector<long long> > dp(n, vector<long long>(target + 1));
    // dp[i][r] is the number of subsets of [0, i] that sum up to r
    // base cases
    for (int index = 0; index < n; index++) {
        dp[index][0] = 1; // the empty subset
    }
    if (arr[0] <= target) {
        dp[0][arr[0]] = 1;
    }

    for (int index = 1; index < n; index++) {
        for (long long sum = 1; sum <= target; sum++) {
            // we don't take arr[index]
            dp[index][sum] += dp[index - 1][sum];

            // we take arr[index]
            if (sum >= arr[index]) {
                dp[index][sum] += dp[index - 1][sum - arr[index]];
            }
        }
    }

    cout << dp[n - 1][target] << endl;

    // 1D dp solution
    vector<long long> iter(target + 1, 0);
    // iter[r] is the number of subsets of arr that sum to r
    iter[0] = 1;

    for (long long num: arr) {
        for (long long sum = target; sum >= num; sum--) {
            iter[sum] += iter[sum - num];
        }
    }

    cout << iter[target] << endl;

    return EXIT_SUCCESS;
}

#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, target;
    cin >> n >> target;
    vector<int> arr(n);
    for (int &val: arr) {
        cin >> val;
    }

    // we are given denominations in arr and the target amount target
    // what is the minimum possible number of coins used?

    vector<int> dp(target + 1, 0);
    // dp[r] is the minimum possible number of coins used to make sum r
    for (int sum = 1; sum <= target; sum++) {
        int minimum = INT_MAX;
        for (int index = 0; index < n; index++) {
            if (sum - arr[index] >= 0) {
                minimum = min(minimum, dp[sum - arr[index]]);
            }
        }
        dp[sum] = minimum + 1;
    }

    cout << dp[target] << endl;
    return EXIT_SUCCESS;
}

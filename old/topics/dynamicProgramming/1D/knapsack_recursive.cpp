#include <bits/stdc++.h>
using namespace std;

bool solve(const vector<int> &arr, const int index, const int target) {
    if (!target) {
        return true;
    }

    if (index >= arr.size()) {
        return false;
    }

    // either we take the current index or we not take the current index
    return solve(arr, index + 1, target - arr[index]) || solve(arr, index + 1, target);
}

int main() {
    int n, target;
    cin >> n >> target;
    vector<int> arr(n);
    for (int &val: arr) {
        cin >> val;
    }
    // we have to check whether there is a subset of arr that sums to target

    // dp[i][j] is true if a subset of first i elements sums to j
    vector<vector<bool> > dp(n + 1, vector<bool>(target + 1));
    // base cases
    dp[0][0] = true; // we can make sum 0 with first 0 elements
    for (int index = 1; index <= n; index++) {
        dp[index][0] = false; // we cannot make sum 0 with any element quantity > 0 (since all elements are positive)
    }
    for (int sum = 1; sum <= target; sum++) {
        dp[0][sum] = false;
    }

    for (int index = 1; index <= n; index++) {
        for (int sum = 1; sum <= target; sum++) {
            // don't take arr[index - 1]
            dp[index][sum] = dp[index - 1][sum];
            if (sum >= arr[index - 1]) {
                dp[index][sum] = dp[index][sum] || dp[index - 1][sum - arr[index - 1]];
            }
        }
    }

    if (dp[n][target]) {
        cout << "YES\n";
    } else {
        cout << "NO\n";
    }

    return EXIT_SUCCESS;
}

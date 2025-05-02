#include <bits/stdc++.h>
using namespace std;

bool solve(vector<long long> &arr, vector<vector<long long> > &dp, const int index, const long long target) {
    // returns true if we can make the sum target using a subset from [index, n - 1]; false otherwise
    if (!target) {
        return true;
    }
    if (target < 0 || index >= arr.size()) {
        return false;
    }

    if (dp[index][target] != -1) {
        return dp[index][target];
    }

    // either include the current index in the sum or do not
    const bool include = solve(arr, dp, index + 1, target - arr[index]);
    const bool exclude = solve(arr, dp, index + 1, target);

    return dp[index][target] = include || exclude;
}

int main() {
    int n;
    long long target;
    cin >> n >> target;
    vector<long long> arr(n);
    for (long long &val: arr) {
        cin >> val;
    }

    // we want to check if there's a subset of arr whose sum is equal to target

    vector<vector<long long> > dp(n, vector<long long>(target + 1, -1));
    // dp[i][r] indicates whether it's possible to make the sum r using a subset of [i, n - 1]
    // base case
    for (int index = 0; index < n; index++) {
        dp[index][0] = 1; // it's possible to make sum 0 using any subset
    }

    if (solve(arr, dp, 0, target)) {
        cout << "YES\n";
    } else {
        cout << "NO\n";
    }

    // we now do an iterative solution
    vector<vector<long long> > iter(n, vector<long long>(target + 1, 0));
    // iter[i][r] indicates if it's possible to make sum r using a subset of [0, i]
    iter[0][0] = 1; // we can make 0 by not choosing anything in the first subset [0, 0]
    if (arr[0] <= target) {
        iter[0][arr[0]] = 1;
    }

    for (int index = 1; index < n; index++) {
        for (long long sum = 0; sum <= target; sum++) {
            if (iter[index - 1][sum]) {
                // if we can make 'sum' using subsets of [0, index - 1], we can now make
                // 'sum' + arr[index] too; we can also make 'sum' if we dont choose the current element into the sum
                iter[index][sum + arr[index]] = 1;
                iter[index][sum] = 1;
            }
        }
    }

    if (iter[n - 1][target]) {
        cout << "YES\n";
    } else {
        cout << "NO\n";
    }

    return EXIT_SUCCESS;
}

#include <bits/stdc++.h>
#include <climits>
#include <vector>
using namespace std;

// Problem: mortalKombat
// URL: https://codeforces.com/problemset/problem/1418/C
// Difficulty: hard
// Tags:
// Strategy:

int dfs(int index, int player, vector<int> &arr, vector<vector<int>> &dp) {
    int n = (int)arr.size();
    if (index >= n)
        return 0;
    if (dp[player][index] != -1) {
        return dp[player][index];
    }

    int justCurrent = INT_MAX;
    int both = INT_MAX;
    // we can either kill the next two, or the next one
    if (!player) {
        // friend
        // can't kill hard without using skips
        // can kill the current or the next two
        justCurrent = (arr[index] ? 1 : 0) + dfs(index + 1, !player, arr, dp);
        if (index + 1 < n) {
            both = (arr[index] ? 1 : 0) + (arr[index + 1] ? 1 : 0) + dfs(index + 2, !player, arr, dp);
        }
    } else {
        justCurrent = dfs(index + 1, !player, arr, dp);
        if (index + 1 < n) {
            both = dfs(index + 2, !player, arr, dp);
        }
    }

    return dp[player][index] = min(justCurrent, both);
}

void solve() {
    int n;
    cin >> n;
    vector<int> arr(n);
    for (int &val : arr)
        cin >> val;

    vector<vector<int>> dp(2, vector<int>(n, -1));
    // dp[p][r] gives the min number of skip points required to kill all the bosses from [r, n - 1] with
    // the first turn being of player p

    cout << dfs(0, 0, arr, dp) << endl;
    return;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
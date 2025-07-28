#include <bits/stdc++.h>
#include <climits>
#include <vector>
using namespace std;

// Problem: longJumps
// URL: https://codeforces.com/problemset/problem/1472/C
// Difficulty: easy
// Tags:
// Strategy:

long long dfs(int node, vector<long long> &arr, vector<long long> &dp) {
    int n = (int)arr.size() - 1;
    if (node > n) {
        return 0;
    }
    if (dp[node] != -1) {
        return dp[node];
    }

    return dp[node] = arr[node] + dfs(node + arr[node], arr, dp);
}

void solve() {
    int n;
    cin >> n;

    vector<long long> arr(n + 1);
    vector<long long> dp(n + 1, -1);
    for (int index = 1; index <= n; index++) {
        cin >> arr[index];
    }

    // dp[r] is the maximum score possible with starting index r
    long long maxi = LLONG_MIN;
    for (int node = 1; node <= n; node++) {
        maxi = max(maxi, dfs(node, arr, dp));
    }

    cout << maxi << endl;
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
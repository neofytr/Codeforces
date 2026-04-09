#include <bits/stdc++.h>
using namespace std;

int solve(const vector<char> &str, const unordered_set<char> &allowed, const int index, vector<int> &dp) {
    // returns the length of the largest subsequence satisfying the condition starting at index
    if (index >= str.size()) return 0;

    if (dp[index] != -1) return dp[index];

    if (allowed.count(str[index])) {
        return dp[index] = 1 + solve(str, allowed, index + 1, dp);
    }

    return dp[index] = 0;
}

int main() {
    int n, k;
    cin >> n >> k;
    vector<char> str(n);
    for (char &val: str) cin >> val;

    unordered_set<char> allowed;
    char val;
    while (k--) {
        cin >> val;
        allowed.insert(val);
    }

    vector<int> dp(n, -1);
    long long ans = 0;
    for (int i = 0; i < n;) {
        const int len = solve(str, allowed, i, dp);
        if (len > 0) {
            ans += 1LL * len * (len + 1) / 2;
            // all the subsequences inside the given length will satisfy the condition too
            i += len; // skip the segment since it's already processed
        } else {
            ++i;
        }
    }

    cout << ans << endl;
    return 0;
}

#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MAX (int)(2 * 1e5)

struct cmp {
    bool operator()(const pair<int, int> &a, const pair<int, int> &b) const {
        if (a.first != b.first)
            return a.first < b.first; // min first
        return a.second > b.second;   // max second
    }
};

int arr[MAX + 1];
int dp[MAX + 1];
int p[MAX + 1];

void solve() {
    int n;
    cin >> n;

    for (int r = 1; r <= n; r++)
        arr[r] = p[r] = dp[r] = 0;

    for (int r = 1; r <= n; r++)
        cin >> arr[r];

    p[0] = p[1] = 0;
    for (int r = 2; r <= n; r++)
        p[r] = p[r - 1] + (arr[r] > arr[r - 1] ? 1 : 0);

    // (dp[k] + p[r - 1] - p[k]) for 0 <= k <= r - 1
    // dp[r] is the minimum possible total score for the array [1, r]
    set<pair<int, int>, cmp> s;
    dp[0] = dp[1] = 0;
    s.insert({dp[0] - p[0], LLONG_MAX});
    s.insert({dp[1] - p[1], arr[1]});
    for (int r = 2; r <= n; r++) {
        cout << r << endl;
        for (auto &[e, m] : s)
            cout << e << " " << m << endl;
        cout << endl;
        auto [v, elt] = *s.begin();
        dp[r] = p[r - 1] + v + (arr[r] > elt ? 1 : 0);
        s.erase({v, elt});
        s.insert({dp[r] - p[r], arr[r]});
    }

    cout << dp[n] << endl;
}

int32_t main() {
    int t;
    cin >> t;

    while (t--) {
        solve();
    }
    return 0;
}
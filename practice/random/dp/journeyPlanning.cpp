#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MAX (int)(2 * 1e5)

int arr[MAX + 1];
int p[MAX + 1];
int dp[MAX + 1][2];

struct Cmp {
    bool operator()(const pair<int, int> &a, const pair<int, int> &b) const {
        if (a.first != b.first)
            return a.first < b.first; // increasing on first
        return a.second > b.second;   // decreasing on second
    }
};

int32_t main() {
    int n;
    cin >> n;

    for (int r = 1; r <= n; r++)
        cin >> arr[r];

    for (int r = 1; r <= n; r++)
        p[r] = r - arr[r];

    for (int r = 1; r <= n; r++)
        for (int s = 0; s <= 1; s++)
            dp[r][s] = LLONG_MIN;

    set<pair<int, int>, Cmp> s;
    dp[1][0] = arr[1], dp[1][1] = 0;
    s.insert({p[1], dp[1][0]});
    for (int r = 2; r <= n; r++) {
        if (auto itr = s.lower_bound({p[r], LLONG_MAX}); itr != s.end()) {
            const int px = itr->first;
            if (const int d = itr->second; px == p[r] && d != LLONG_MIN)
                dp[r][0] = max(dp[r][0], d + arr[r]);
        }
        dp[r][0] = max(dp[r][0], arr[r]);
        dp[r][1] = max(dp[r - 1][0], dp[r - 1][1]);
        s.insert({p[r], dp[r][0]});
    }

    cout << max(dp[n][0], dp[n][1]) << endl;
    return 0;
}
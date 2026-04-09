#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MAX 4000

int dp[MAX + 1];

int32_t main() {
    int n, a, b, c;
    cin >> n >> a >> b >> c;

    set<int> v;
    v.insert(a), v.insert(b), v.insert(c);

    // dp[r] is the maximum number of ribbon pieces possible for r
    for (int r = 1; r <= MAX; r++)
        dp[r] = -1;

    dp[0] = 0;
    for (int r = 1; r <= n; r++) {
        for (const int e : v)
            if (r >= e && dp[r - e] != -1)
                dp[r] = max(dp[r], dp[r - e] + 1);
    }

    cout << dp[n] << endl;
    return 0;
}
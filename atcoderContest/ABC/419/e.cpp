#include <bits/stdc++.h>
using namespace std;

const long long INF = 1e18;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m, l;
    cin >> n >> m >> l;

    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        a[i] %= m; // make sure values are in [0, m-1]
    }

    vector<vector<long long>> costs(l, vector<long long>(m, 0));
    for (int k = 0; k < l; ++k) {
        vector<int> freq(m, 0);
        long long p = 0;
        for (int i = k; i < n; i += l) {
            freq[a[i]]++;
            p++;
        }
        if (p == 0) continue;

        long long s = 0;
        for (int v = 0; v < m; ++v) {
            s += 1LL * v * freq[v];
        }

        // initial cost for remainder 0
        costs[k][0] = 1LL * m * (p - freq[0]) - s;

        // use recurrence to compute all others
        for (int r = 0; r < m - 1; ++r) {
            costs[k][r + 1] = costs[k][r] + p - 1LL * m * freq[(r + 1) % m];
        }
    }

    vector<long long> dp(m, INF);
    dp[0] = 0;

    for (int k = 0; k < l; ++k) {
        vector<long long> next_dp(m, INF);
        for (int prev = 0; prev < m; ++prev) {
            if (dp[prev] == INF) continue;
            for (int r = 0; r < m; ++r) {
                int new_rem = (prev + r) % m;
                long long cur = dp[prev] + costs[k][r];
                next_dp[new_rem] = min(next_dp[new_rem], cur);
            }
        }
        dp.swap(next_dp);
    }

    cout << dp[0] << "\n";
    return 0;
}

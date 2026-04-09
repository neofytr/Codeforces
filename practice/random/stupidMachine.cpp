#include <bits/stdc++.h>

using namespace std;
#define int long long

void solve() {
    int n;
    cin >> n;

    int val;
    priority_queue<pair<int, int>> pq;
    for (int r = 1; r <= n; r++)
        cin >> val, pq.push({-val, r});

    int lastIdx = n + 1;
    int lastVal = 0;
    int sum = 0;
    while (!pq.empty()) {
        auto [val, idx] = pq.top();
        val = -val;
        pq.pop();
        if (idx > lastIdx)
            continue;

        const int gain = max(0LL, val - lastVal);
        sum += gain * (lastIdx - 1);
        lastIdx = idx;
        lastVal = val;
    }

    cout << sum << endl;
}

int32_t main() {
    int t;
    cin >> t;

    while (t--) {
        solve();
    }
    return 0;
}
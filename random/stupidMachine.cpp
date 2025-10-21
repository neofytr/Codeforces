#include <bits/stdc++.h>

using namespace std;

void solve() {
    int n;
    cin >> n;

    int val;
    priority_queue<pair<int, int>> pq;
    for (int r = 1; r <= n; r++)
        cin >> val, pq.push({val, r});
}

int main() {
    int t;
    cin >> t;

    while (t--) {
        solve();
    }
    return 0;
}
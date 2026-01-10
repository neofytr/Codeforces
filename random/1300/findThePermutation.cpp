#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve() {
    int n;
    cin >> n;

    string col;
    vector adj(n + 1, vector<int>(n + 1, 0));
    for (int r = 1; r <= n; r++) {
        cin >> col;
        for (int c = 1; c <= n; c++)
            adj[r][c] = col[c - 1] - '0';
    }
}

int32_t main() {
    int t;
    cin >> t;

    while (t--) {
        solve();
    }

    return 0;
}
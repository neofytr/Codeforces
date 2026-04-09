#include <bits/stdc++.h>
using namespace std;

#define int long long

// Problem: beginnersZelda
// URL: https://codeforces.com/problemset/problem/1905/B
// Difficulty: hard
// Tags:
// Strategy:

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        int u, v;
        vector<vector<int>> tree(n + 1);
        for (int r = 1; r <= n - 1; r++)
            cin >> u >> v, tree[u].push_back(v), tree[v].push_back(u);


    }
    return 0;
}
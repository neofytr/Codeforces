#include <bits/stdc++.h>
using namespace std;

#define int long long

// Problem: appleTree
// URL: https://codeforces.com/problemset/problem/1843/D
// Difficulty: medium
// Tags:
// Strategy:

#include <bits/stdc++.h>
using namespace std;

#define int long long

// if v is NOT the root node, it's the leaf node iff its degree is 1
// if v is a root node, it's degree is one means the tree has just two elements

// so check for leaf node in this manner ->
int dfs(const int u, const int parent, const vector<vector<int>> &tree, vector<int> &dp) {
    bool isLeaf = true;
    int total = 0;
    for (int v : tree[u]) {
        if (v == parent)
            continue;
        isLeaf = false;
        total += dfs(v, u, tree, dp); // each subtree has unique leaves, so we can just add the number
    }
    if (isLeaf)
        return dp[u] = 1; // true leaf
    return dp[u] = total;
}

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        vector<vector<int>> tree(n + 1);
        for (int i = 1; i <= n - 1; i++) {
            int u, v;
            cin >> u >> v;
            tree[u].push_back(v);
            tree[v].push_back(u);
        }

        vector<int> dp(n + 1, 0);
        dfs(1, -1, tree, dp);

        int q;
        cin >> q;
        while (q--) {
            int x, y;
            cin >> x >> y;
            cout << dp[x] * dp[y] << "\n";
        }
    }
}

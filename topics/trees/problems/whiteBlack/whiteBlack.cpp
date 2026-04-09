#include <bits/stdc++.h>
using namespace std;

#define int long long

// Problem: whiteBlack
// URL: https://codeforces.com/problemset/problem/1676/G
// Difficulty: medium
// Tags:
// Strategy:

int cnt = 0;
// this returns the number of white vertices - black vertices in the subtree rooted at node
int bal(const int node, const string &coloring, const vector<vector<int>> &tree) {
    int diff = 0;
    for (const int v : tree[node])
        diff += bal(v, coloring, tree);
    diff += ((coloring[node - 1] == 'B') ? -1 : 1);
    if (!diff)
        cnt++;
    return diff;
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        int root = 1;
        int pt;
        vector<vector<int>> tree(n + 1);
        for (int r = 2; r <= n; r++)
            cin >> pt, tree[pt].push_back(r); // we store the tree as a directed graph

        string coloring;
        cin >> coloring;
        // bal(n) = true iff the number of white vertices and black vertices in the subtree rooted at n are equal
        bal(root, coloring, tree);
        cout << cnt << endl;
        cnt = 0;
    }
    return 0;
}
#include <bits/stdc++.h>
using namespace std;

#define int long long

// Problem: maximizeTheRoot
// URL: https://codeforces.com/problemset/problem/1997/D
// Difficulty: hard
// Tags:
// Strategy:

int dfs(const int x, const vector<int> &arr, const vector<vector<int>> &tree) {
    if (!tree[x].size()) // leaf node
        return arr[x];

    int ans = LLONG_MAX;
    for (const int v : tree[x])
        ans = min(ans, dfs(v, arr, tree));

    if (x != 1) {
        if (arr[x] > ans)
            return ans;
        return (ans + arr[x]) / 2;
    }
    return arr[x] + ans;
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        vector<int> arr(n + 1);
        for (int r = 1; r <= n; r++)
            cin >> arr[r];

        int p;
        vector<vector<int>> tree(n + 1);
        for (int r = 2; r <= n; r++)
            cin >> p, tree[p].push_back(r);

        int root = 1;
        cout << dfs(root, arr, tree) << endl;
    }

    return 0;
}
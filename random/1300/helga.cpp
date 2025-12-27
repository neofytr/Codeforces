#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MOD (1e9 + 7)

int n, m, k, x;

int cnt(const int node, const int parent, const int strongLeft, const bool isStrong, const bool isParentStrong, const vector<vector<int>> &tree) {
    int res = 0;
    if (isStrong) { // the current node is strong, then the parent can't be strong anyways
        int strong = 1;
        for (const int v : tree[node])
            if (v != parent)
                strong *= cnt(v, node, strongLeft, false, true,  tree);
        res += strong;
    } else {
        if (isParentStrong) {
            // the parent node is strong but not the current node
            int first = k - 1;
            for (const int v : tree[node])
                if (v != parent)
                    first *= (cnt(v, node, strongLeft, false, false, tree) + cnt(v, node, strongLeft - 1, true, false, tree)); // the adjacent can be both strong or not strong, doesn't matter
            res += first;
        } else {
            // the current node and its parent node both aren't strong
            const int sz = (int)tree[node].size();
            if (sz == 1) return (m - 1);

            int sum1 = 0, sum2 = 0;
            vector<int> f1(sz), f2(sz);
            for (int r = 0; r < sz; r++)
                if (tree[node][r] != parent) {
                    f1[r] = cnt(tree[node][r], node, strongLeft, false, false, tree);
                    f2[r] = cnt(tree[node][r], node, strongLeft - 1, true, false, tree);
                    sum1 += f1[r], sum2 += f2[r];
                }

            int first = k - 1; // assuming at least one of the neighbors is strong
            for (int r = 0; r < sz; r++)
                if (tree[node][r] != parent)
                    first *= (f1[r] + f2[r]);

            first -= (k - 1) * (sum1); // overcounting

            int second = (m - 1); // assuming none of the neighbors is strong
            second *= (sum1);

            res += (first + second);
        }
        return res;
    }

    return res;
}

int32_t main() {
    cin >> n >> m;

    int u, v;
    vector<vector<int>> tree(n + 1);
    for (int r = 1; r <= n - 1; r++) {
        cin >> u >> v;
        tree[u].push_back(v);
        tree[v].push_back(u);
    }

    cin >> k >> x;
    cout << cnt(1, -1, x - 1, true, false, tree) + cnt(1, -1, x, false, false, tree) << endl;
    return 0;
}
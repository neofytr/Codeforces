#include <bits/stdc++.h>
using namespace std;

#define int long long

// Problem: christmasSpruce
// URL: https://codeforces.com/problemset/problem/913/B
// Difficulty: medium
// Tags:
// Strategy:

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    int pt;
    vector<vector<int>> tree(n + 1);
    for (int r = 2; r <= n; r++)
        cin >> pt, tree[pt].push_back(r);

    int root = 1;
    bool isSpruce = true;

    queue<int> que;
    que.push(root);
    while (!que.empty()) {
        int size = (int)que.size();
        for (int r = 1; r <= size; r++) {
            int node = que.front();
            que.pop();

            if (tree[node].empty())
                continue; // skip the leaf nodes

            int leafChildren = 0;
            for (const int v : tree[node])
                if (tree[v].empty())
                    leafChildren++;
                else
                    que.push(v);
            if (leafChildren < 3)
                isSpruce = false;
        }
    }
    cout << (isSpruce ? "Yes\n" : "No\n");
    return 0;
}
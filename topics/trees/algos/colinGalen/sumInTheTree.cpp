#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main() {
    int n;
    cin >> n;

    int root = 1;
    vector<int> parent(n + 1), s(n + 1);
    vector<vector<int>> tree(n + 1);
    for (int r = 2; r <= n; r++)
        cin >> parent[r], tree[parent[r]].push_back(r);
    for (int r = 1; r <= n; r++)
        cin >> s[r];

    // s[v] == -1 iff h(v) is odd

    // if v is a non-leaf node such that s[v] = -1, then
    // s[parent[v]] and s[child[v]] won't be -1 since h(v) is even and h(parent[v]) and h(child[v]) are odd
    // Also, we want to minimize the sum(a[r], 1 <= r <= n), so we maximize a[v] and minimize a[child[v]]
    // s[k] = a[k] + s[v] for all children k of v
    // since all a[r] >= 0, to minimize a[k] across all k, we put
    // s[v] = min(s[k] for all children k of v)
    // also,  a[v] = s[v] - s[parent[v]] >= 0

    // if v is a leaf node with s[v] = -1, we put s[v] = s[parent[v]]

    queue<int> que;
    que.push(root);
    while (!que.empty()) {
        int node = que.front();
        que.pop();

        if (s[node] == -1)
            if (tree[node].empty())
                s[node] = s[parent[node]];
            else {
                int mn = LLONG_MAX;
                for (const int v : tree[node])
                    mn = min(mn, s[v]);
                if (mn - s[parent[node]] < 0) {
                    cout << -1 << endl;
                    return EXIT_SUCCESS;
                }
                s[node] = mn;
            }
        for (const int v : tree[node])
            que.push(v);
    }

    int sum = 0;
    for (int r = 1; r <= n; r++)
        sum += s[r] - s[parent[r]];
    cout << sum << endl;
    return EXIT_SUCCESS;
}

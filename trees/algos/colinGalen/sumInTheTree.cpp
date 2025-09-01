#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main() {
    int n;
    cin >> n;

    vector<int> parent(n + 1);
    vector<vector<int>> tree(n + 1);

    for (int r = 2; r <= n; r++) {
        int pr;
        cin >> pr;
        tree[pr].push_back(r);
        parent[r] = pr;
    }

    vector<int> s(n + 1);
    for (int r = 1; r <= n; r++)
        cin >> s[r];

    queue<int> que;
    que.push(1);
    while (!que.empty()) {
        int node = que.front();
        que.pop();

        if (s[node] == -1) {
            if (tree[node].empty()) {
                s[node] = s[parent[node]]; // leaf → same as parent
            } else {
                int mn = LLONG_MAX;
                for (int v : tree[node])
                    mn = min(mn, s[v]);
                s[node] = mn;
            }
        }

        for (int v : tree[node])
            que.push(v);
    }

    // compute answer
    int sum = s[1]; // a[1] = s[1]
    for (int v = 2; v <= n; v++) {
        int a = s[v] - s[parent[v]];
        if (a < 0) {
            cout << -1 << "\n";
            return 0;
        }
        sum += a;
    }

    cout << sum << "\n";
    return 0;
}

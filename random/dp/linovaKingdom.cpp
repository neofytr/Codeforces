#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main() {
    int n, k;
    cin >> n >> k;

    int u, v;
    vector<vector<int>> graph(n + 1);
    for (int r = 1; r <= n; r++)
        cin >> u >> v, graph[u].push_back(v), graph[v].push_back(u);

    vector<int> dp(n + 1, 0);
    vector<int> type(n + 1, 0);
    vector<set<int>> depth(n + 1);

    int d = 1;
    queue<pair<int, int>> que;
    que.push({1, -1});
    while (!que.empty()) {
        int sz = (int)que.size();
        while (sz--) {
            auto [x, p] = que.front();
            que.pop();
            depth[d].insert(x);

            for (int node : graph[x])
                if (node != p)
                    que.push({node, x});
        }
        d++;
    }

    set<pair<int, int>> pq1, pq2;

    for (int e : depth[d - 1])
        if (k)
            pq1.insert({0, e});
    d--;

    while (true) {
        int sz = pq1.size();
        while (sz--) {
            auto [m, node] = *pq1.begin();
            if (k)
                dp[node] += 1, m++, k--, type[node] = 1;
            pq1.erase(pq1.begin());

            for (int x : graph[node]) {
                if (depth[d - 1].contains(x)) {
                    pq2.erase({dp[x], x});
                    pq2.insert({dp[x] += dp[node], x});
                }
            }
        }
        if (pq2.empty())
            break;
        swap(pq1, pq2);
        d--;
    }

    int res = 0;
    for (int r = 1; r <= n; r++)
        if (type[r])
            cout << r << " " << dp[r] << endl;

    cout << res << endl;
    return 0;
}
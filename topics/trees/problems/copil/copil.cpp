#include <bits/stdc++.h>
using namespace std;

#define int long long

// Problem: copil
// URL: https://codeforces.com/problemset/problem/1830/A
// Difficulty: hard
// Tags:
// Strategy:

#include <bits/stdc++.h>
using namespace std;

#define int long long

struct pair_hash {
    template <class T1, class T2> std::size_t operator()(const std::pair<T1, T2> &p) const {
        auto h1 = std::hash<T1>{}(p.first);
        auto h2 = std::hash<T2>{}(p.second);

        // Combine hashes (example method: XOR with shifting)
        return h1 ^ (h2 << 1);
    }
};

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        unordered_map<pair<int, int>, int, pair_hash> mp;
        vector<vector<int>> g(n + 1);
        for (int i = 1; i <= n - 1; i++) {
            int u, v;
            cin >> u >> v;
            g[u].push_back(v);
            g[v].push_back(u);
            mp[{u, v}] = mp[{v, u}] = i;
        }

        // dp[r] is the number of scans needed to activate node r
        vector<int> dp(n + 1, -1);

        int src = 1;
        queue<pair<int, int>> que;

        // id[r] is the index of the edge (in the input array) that made the node r
        vector<int> id(n + 1, -1);
        dp[1] = 1;
        id[1] = 0;
        que.push({src, -1});
        while (!que.empty()) {
            auto [node, parent] = que.front();
            que.pop();
            for (const int v : g[node]) {
                if (v == parent)
                    continue;
                const int edgeID = mp[{v, node}];
                if (edgeID > id[node])
                    dp[v] = dp[node];
                else
                    dp[v] = dp[node] + 1;
                id[v] = edgeID;
                que.push({v, node});
            }
        }

        int ans = dp[1];
        for (int r = 1; r <= n; r++)
            ans = max(dp[r], ans);
        cout << ans << endl;
    }
    return 0;
}

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

// Use long long for values to avoid overflow
vector<long long> a;
vector<vector<int>> adj;
vector<long long> max_threat_vals;
vector<long long> min_threat_vals;

void dfs(int u, int p) {
    // For any node u that is not the root, calculate its min/max threat
    // based on the already computed values of its parent p.
    if (p != 0) {
        // The maximum possible sum starting at u is either a[u] itself,
        // or a[u] minus the minimum possible sum from its parent.
        max_threat_vals[u] = max(a[u], a[u] - min_threat_vals[p]);

        // The minimum possible sum starting at u is either a[u] itself,
        // or a[u] minus the maximum possible sum from its parent.
        min_threat_vals[u] = min(a[u], a[u] - max_threat_vals[p]);
    }

    // After computing values for u, traverse to its children.
    for (int v : adj[u]) {
        if (v != p) {
            dfs(v, u);
        }
    }
}

void solve() {
    int n;
    cin >> n;

    // Use 1-based indexing to match problem statement
    a.assign(n + 1, 0);
    adj.assign(n + 1, vector<int>());
    max_threat_vals.assign(n + 1, 0);
    min_threat_vals.assign(n + 1, 0);

    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }

    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // Root node (vertex 1) initialization. Its path is just itself.
    max_threat_vals[1] = a[1];
    min_threat_vals[1] = a[1];

    // Start DFS from the root. A single call will traverse the whole tree.
    // The parent of the root is passed as 0 (a sentinel value).
    dfs(1, 0);

    for (int i = 1; i <= n; ++i) {
        cout << max_threat_vals[i] << (i == n ? "" : " ");
    }
    cout << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
#include <bits/stdc++.h>

void solve() {
    int n;
    std::cin >> n;

    std::vector<std::vector<int>> adj(n + 1);
    std::vector<int> degree(n + 1, 0);
    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        std::cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
        degree[u]++;
        degree[v]++;
    }

    std::vector<bool> is_leaf(n + 1, false);
    int num_leaves = 0;
    for (int i = 1; i <= n; ++i) {
        if (degree[i] == 1) {
            is_leaf[i] = true;
            num_leaves++;
        }
    }

    int max_score = 0;
    for (int i = 1; i <= n; ++i) {
        int current_score = 0;

        if (is_leaf[i]) {
            current_score = 1;
        }

        for (int neighbor : adj[i]) {
            if (is_leaf[neighbor]) {
                current_score++;
            }
        }

        if (current_score > max_score) {
            max_score = current_score;
        }
    }

    std::cout << num_leaves - max_score << std::endl;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int t;
    std::cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}
#include <bits/stdc++.h>
using namespace std;

#define int long long

pair<int, int> bfs(int src, vector<vector<int>> &tree) {
	int n = tree.size() - 1;
	vector<bool> vis(n + 1, false);
	vis[src] = true; queue<int> q;

	while (!q.empty()) {
		int x = q.front(); q.pop();
	}
}

int32_t main() {
	int n; cin >> n;
	vector<vector<int>> tree(n + 1);
	vector<pair<int, int>> edges;

	int u, v;
	for (int r = 1; r <= n - 1; r++)
		cin >> u >> v, tree[u].push_back(v), tree[v].push_back(u), edges.push_back({u, v});


	return 0;
}
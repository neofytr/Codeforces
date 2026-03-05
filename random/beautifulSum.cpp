#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MAX (int)(1e5)

void solve() {
	int n; cin >> n;
	int u, v, w;
	int root = 1;
	int t = 0;
	vector<int> parent(n + 1);
	vector<int> lin(n + 1), start(n + 1), finish(n + 1), val(n + 1);
	vector<vector<pair<int, int>>> graph(n + 1);
	for (int i = 1; i <= n - 1; i++)
		cin >> u >> v >> w, graph[u].push_back({v, w}), graph[u].push_back({u, w});

	auto dfs = [&](auto &&self, int x, int p) -> void {
		++t;
		start[x] = t, lin[t] = val[x];
		for (auto &[v, w]: graph[x])
			if (v != p) 
				val[v] = w, parent[v] = x, self(self, v, x);
		finish[x] = t;
	};

	dfs(dfs, root, -1);
}

int32_t main() {
	int t; cin >> t;
	while (t--) solve();
	return 0;
}
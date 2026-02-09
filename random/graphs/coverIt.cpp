#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve() {
	int n, m; cin >> n >> m;

	int u, v;
	vector<vector<int>> graph(n + 1);
	while (m--)
		cin >> u >> v, graph[u].push_back(v), graph[v].push_back(u);
}

int32_t main() {
	int t; cin >> t;
	while (t--) solve();
	return 0;
}
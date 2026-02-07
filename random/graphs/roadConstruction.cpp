#include <bits/stdc++.h>
using namespaces std;

#define int long long

int32_t main() {
	int n, m; cin >> n >> m;
	vector<set<int>> graph(n + 1);
	for (int r = 1; r <= n; r++)
		for (int v = 1; v <= n; v++)
			if (r != v) graph[r].insert(v);

	int u, v;
	while (m--) 
		cin >> u >> v, graph[u].erase(v), graph[v].erase(u);

	queue<int> que;
	vector<bool> vis(n + 1, false);

	int src = 1;
	vis[src] = true;
	while (!que.empty()) {
		int x = que.front();
		que.pop();

		for (int v : graph[x])
			if (!vis[v]) {
				vis[v] = true;
				que.push(v);
			} else {
				// useless edge
			}
	}
}
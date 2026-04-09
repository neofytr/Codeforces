#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main() {
	int n, m; cin >> n >> m;
	int u, v;
	vector<vector<int>> graph(n + 1);
	vector<pair<int, int>> edges;
	while (m--)
		cin >> u >> v, graph[u].push_back(v), graph[v].push_back(u), edges.push_back({u, v});

	int src = 1;
	queue<int> que;
	vector<int> color(n + 1, -1);

	color[src] = 0, que.push(src);
	while (!que.empty()) {
		int x = que.front(); que.pop();
		for (int v : graph[x])
			if (color[v] == -1) color[v] = !color[x], que.push(v);
			else if (color[v] == color[x]) {
				cout << "NO" << endl;
				return 0;
			}
	}
	cout << "YES" << endl;
	for (auto [u, v] : edges)
		cout << color[u];
	cout << endl;
	return 0;
}
#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve() {
	int n, m; cin >> n >> m;
	vector<vector<int>> graph(n + 1), inv(n + 1);
	int u, v;
	while (m--) 
		cin >> u >> v, graph[u].push_back(v);

	queue<int> que;
	vector<int> dist(n + 1, LLONG_MAX);

	dist[1] = 0, que.push(1);
	while (!que.empty()) {
		int x = que.front(); que.pop();
		for (int v : graph[x])
			if (dist[v] > dist[x] + 1)
				dist[v] = dist[x] + 1, que.push(v);
	}

	set<pair<int, int>> s;
	for (int node = 1; node <= n; node++)
		for (int v : graph[node])
			if (dist[v] <= dist[node])
				s.insert({dist[v], node});
			else
				inv[v].push_back(node);

	while (!s.empty()) {
		auto [d, node] = *s.begin();
		if (dist[node] > d) dist[node] = d;
		s.erase(s.begin());
		for (int v : inv[node])
			if (dist[v] > d)
				dist[v] = d, s.insert({d, v});
	}

	for (int r = 1; r <= n; r++)
		cout << dist[r] << " ";
	cout << endl;
}

int32_t main() {
	int t; cin >> t;
	while (t--) solve();
	return 0;
}
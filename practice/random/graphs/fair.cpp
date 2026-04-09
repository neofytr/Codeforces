#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int n, m, k, s; cin >> n >> m >> k >> s;

	int t;
	vector<vector<int>> type(k + 1);
	for (int r = 1; r <= n; r++) 
		cin >> t, type[t].push_back(r);

	int u, v; 
	vector<vector<int>> graph(n + 1);
	while (m--) 
		cin >> u >> v, graph[u].push_back(v), graph[v].push_back(u);

	queue<int> que;
	vector<vector<int>> dist(n + 1, vector<int>(k + 1, LLONG_MAX));
	for (int t = 1; t <= k; t++) {
		for (int v : type[t]) que.push(v), dist[v][t] = 0;
		while (!que.empty()) {
			int x = que.front(); que.pop();
			int d = dist[x][t];
			for (int v : graph[x])
				if (dist[v][t] > d + 1)
					dist[v][t] = d + 1, que.push(v);
		}
	}

	for (int node = 1; node <= n; node++) {
		sort(dist[node].begin() + 1, dist[node].end());
		int cost = 0;
		for (int r = 1; r <= s; r++)
			cost += dist[node][r];
		cout << cost << " ";
	}
	cout << endl;
	return 0;
}
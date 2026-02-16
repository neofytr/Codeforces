#include <bits/stdc++.h>
using namespace std;

#define int long long

pair<int, int> bfs(int node, vector<vector<int>> &tree) {
	int n = tree.size() - 1;
	queue<int> que;
	vector<int> dist(n + 1, LLONG_MAX);

	dist[node] = 0, que.push(node);
	while (!que.empty()) {
		int x = que.front(); que.pop();
		int d = dist[x];
		for (int v : tree[x])
			if (dist[v] > d + 1)
				dist[v] = d + 1, que.push(v);
	}

	int maxi = LLONG_MIN;
	for (int r = 1; r <= n; r++) maxi = max(maxi, dist[r]);
	for (int r = 1; r <= n; r++) if (dist[r] == maxi) return {r, dist[r]};
	return {0, 0};	
}

int32_t main() {
	int n; cin >> n;

	int u, v;
	vector<vector<int>> tree(n + 1);
	for (int r = 1; r <= n - 1; r++)
		cin >> u >> v, tree[u].push_back(v), tree[v].push_back(u);

	auto [x, dx] = bfs(1, tree);
	auto [y, dy] = bfs(x, tree);

	// x and y are diameter endpoints
	queue<int> que;
	vector<int> parent(n + 1, -1);

	que.push(x);
	while (!que.empty()) {
		int node = que.front(); que.pop();
		for (int v : tree[node])
			if (v != parent[node])
				parent[v] = node, que.push(v);
	}

	int t = y;
	vector<int> dist(n + 1, LLONG_MAX);
	while (parent[t] != -1)
		dist[t] = 0, que.push(t), t = parent[t];
	dist[t] = 0, que.push(t);

	while (!que.empty()) {
		int node = que.front(); que.pop();
		for (int v : tree[node])
			if (dist[v] > dist[node] + 1)
				dist[v] = dist[node] + 1, que.push(v);
	} 

	int maxi = LLONG_MIN;
	int z = -1;
	for (int node = 1; node <= n; node++)
		if (maxi < dist[node] && node != x && node != y)
			maxi = dist[node], z = node;

	cout << dist[z] + dy << endl;
	cout << x << " " << y << " " << z << endl;
}
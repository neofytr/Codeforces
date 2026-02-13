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

	queue<int> que;
	vector<int> distx(n + 1, LLONG_MAX), disty(n + 1, LLONG_MAX);
	distx[x] = 0, que.push(x);
	while (!que.empty()) {
		int node = que.front(); que.pop();
		int d = distx[node];
		for (int v : tree[node])
			if (distx[v] > d + 1)
				distx[v] = d + 1, que.push(v);
	}
	disty[y] = 0, que.push(y);
	while (!que.empty()) {
		int node = que.front(); que.pop();
		int d = disty[node];
		for (int v : tree[node])
			if (disty[v] > d + 1)
				disty[v] = d + 1, que.push(v);
	}
	for (int r = 1; r <= n; r++)
		cout << max(distx[r], disty[r]) << " ";
	cout << endl;
	return 0;
}
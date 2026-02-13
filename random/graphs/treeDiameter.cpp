#include <bits/stdc++.h>
using namespace std;

#define int long long

pair<int, int> bfs(int src, vector<vector<int>> &tree) {
	int n = tree.size() - 1;

	queue<int> que;
	vector<int> dist(n + 1, LLONG_MAX); 

	que.push(src), dist[src] = 0;
	while (!que.empty()) {
		int x = que.front(); que.pop();
		for (int v : tree[x])
			if (dist[v] > dist[x] + 1)
				dist[v] = dist[x] + 1, que.push(v);
	}

	int maxi = -1;
	for (int node = 1; node <= n; node++)
		maxi = max(maxi, dist[node]);

	for (int node = 1; node <= n; node++)
		if (dist[node] == maxi)
			return {node, maxi};
	return {0,0};
}

int32_t main() {
	int n; cin >> n;
	vector<vector<int>> tree(n + 1);

	int u, v;
	for (int r = 1; r <= n - 1; r++)
		cin >> u >> v, tree[u].push_back(v), tree[v].push_back(u);

	auto [x, d] = bfs(1, tree);
	auto [y, diam] = bfs(x, tree);
	cout << diam << endl;
	return 0;
}
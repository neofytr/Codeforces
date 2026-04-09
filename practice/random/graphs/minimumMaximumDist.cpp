#include <bits/stdc++.h>
using namespace std;

#define int long long

pair<int, int> bfs(int src, vector<vector<int>> &tree) {
	int n = tree.size() - 1;

	queue<int> q;
	vector<int> dist(n + 1, LLONG_MAX);

	q.push(src);
	dist[src] = 0;

	while (!q.empty()) {
		int x = q.front(); q.pop();
		for (int v : tree[x]) {
			if (dist[v] > dist[x] + 1) {
				dist[v] = dist[x] + 1;
				q.push(v);
			}
		}
	}

	int far = src;
	for (int i = 1; i <= n; i++)
		if (dist[i] != LLONG_MAX && dist[i] > dist[far])
			far = i;

	return {far, dist[far]};
}

void solve() {
	int n, k; 
	cin >> n >> k;

	vector<int> special(k);
	set<int> s;
	for (int i = 0; i < k; i++) {
		cin >> special[i];
		s.insert(special[i]);
	}

	vector<vector<int>> tree(n + 1);
	for (int i = 0; i < n - 1; i++) {
		int u, v;
		cin >> u >> v;
		tree[u].push_back(v);
		tree[v].push_back(u);
	}

	int root = special[0];
	vector<int> parent(n + 1, -1);
	queue<int> q;
	q.push(root);
	parent[root] = 0;

	while (!q.empty()) {
		int x = q.front(); q.pop();
		for (int v : tree[x]) 
			if (parent[v] == -1) 
				parent[v] = x, q.push(v);
	}

	vector<int> needed(n + 1, 0);
	for (int x : special) 
		while (x != 0 && !needed[x]) {
			needed[x] = 1;
			x = parent[x];
		}
	

	vector<vector<int>> modi(n + 1);
	for (int u = 1; u <= n; u++) {
		if (!needed[u]) continue;
		for (int v : tree[u]) 
			if (needed[v]) 
				modi[u].push_back(v);
	}

	auto [x, _] = bfs(root, modi);
	auto [y, diam] = bfs(x, modi);

	cout << (diam + 1) / 2 << '\n';
}

int32_t main() {
	int t; 
	cin >> t;
	while (t--) solve();
}

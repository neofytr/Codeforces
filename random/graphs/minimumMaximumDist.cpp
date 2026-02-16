#include <bits/stdc++.h>
using namespace std;

#define int long long

bool dfs(int node, int parent, set<int> &ends, vector<vector<int>> &tree, vector<vector<int>> &modi) {
	if (ends.find(node) != ends.end()) 
		return true;
	if (tree[node].size() == 1 && parent != -1) 
		return false;

	for (int v : tree[node])
		if (v != parent) 
			if (dfs(v, node, ends, tree, modi))
				modi[node].push_back(v), modi[v].push_back(node);
	return modi[node].size() >= 1;
}

void norm(int node, int parent, vector<vector<int>> &tree) {
	for (int v : tree[node])
		if (v != parent)
			norm(v, node, tree);

	cout << node << endl;
	for (int v : tree[node])
		if (v != parent)
			cout << v << " ";
	cout << endl;
}

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

void solve() {
	int n, k; cin >> n >> k;

	set<int> s;
	int v, u;
	for (int r = 1; r <= k; r++) 
		cin >> v, s.insert(v);

	vector<vector<int>> tree(n + 1);
	for (int r = 1; r <= n - 1; r++)
		cin >> u >> v, tree[u].push_back(v), tree[v].push_back(u);

	vector<vector<int>> modi(n + 1);
	dfs(*s.begin(), -1, s, tree, modi);
	norm(*s.begin(), -1, modi);

	auto [x, d] = bfs(*s.begin(), modi);
	auto [y, diam] = bfs(x, modi);
	cout << (diam + 1) / 2 << endl;
}

int32_t main() {
	int t; cin >> t;
	while (t--) solve();
	return 0;
}
#include <bits/stdc++.h>
using namespace std;

#define int long long

void dfs(int node, int parent, int c, vector<int> &dp, vector<int> &sz, vector<vector<int>> &tree) {
	if (tree[node].size() == 1 && parent != -1) return;

	int cnt = 0;
	for (int v : tree[node])
		if (v != parent) cnt += sz[v];

	for (int v : tree[node])
		if (v != parent) dp[v] = dp[node] + (cnt - 2 * sz[v]) + c;

	for (int v : tree[node])
		if (v != parent) dfs(v, node, c + cnt, dp, sz, tree);
}

int szdfs(int node, int parent, vector<int> &sz, vector<vector<int>> &tree) {
	if (tree[node].size() == 1 && parent != -1)
		return sz[node] = 1;

	sz[node] = 1;
	for (int v : tree[node])
		if (v != parent)
			sz[node] += (szdfs(v, node, sz, tree));
	return sz[node];
}

int32_t main() {
	int n; cin >> n;

	int u, v;
	vector<vector<int>> tree(n + 1);
	for (int r = 1; r <= n - 1; r++)
		cin >> u >> v, tree[u].push_back(v), tree[v].push_back(u);

	vector<int> sz(n + 1, 0);
	szdfs(1, -1, sz, tree);

	queue<int> que;
	vector<int> dist(n + 1, LLONG_MAX);

	que.push(1), dist[1] = 0;
	while (!que.empty()) {
		int x = que.front(); que.pop();
		int d = dist[x] + 1;
		for (int v : tree[x])
			if (dist[v] > d + 1) dist[v] = d + 1, que.push(v);
	}

	vector<int> dp(n + 1, 0);
	for (int r = 1; r <= n; r++)
		dp[1] += dist[r];

	dfs(1, -1, 1, dp, sz, tree);
	for (int r = 1; r <= n; r++)
		cout << dp[r] << " ";
	cout << endl;
	return 0;
}
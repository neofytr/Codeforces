#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MAX (int)(2 * 1e5)
#define LOG (19)

int tree[8 * MAX + 8];
int lin[2 * MAX + 1], start[MAX + 1], finish[MAX + 1];

int t = 0;
int val[MAX + 1];
int parent[MAX + 1];
int depth[MAX + 1];
pair<int, int> edges[MAX + 1];
vector<pair<int, int>> graph[MAX + 1];

int dp[LOG + 1][MAX + 1];

int walk(int v, int k) {
	int curr = v;
	for (int i = 0; i <= LOG; i++)
		if (k & (1ll << i)) {
			curr = dp[i][curr];
			if (curr == -1) return curr;
		}
	return curr;
}

int lca(int u, int v) {
	if (depth[u] < depth[v]) swap(u, v);
	u = walk(u, depth[u] - depth[v]);

	if (u == v) return u;
	for (int i = LOG; i >= 0; i--)
		if (dp[i][u] != dp[i][v])
			u = dp[i][u], v = dp[i][v];

	return dp[0][u];
}

void dfs(int node) {
	++t;
	start[node] = t, lin[t] = val[node];
	for (auto &[v, w] : graph[node])
		if (v != parent[node]) 
			depth[v] = depth[node] + 1, parent[v] = node, dp[0][v] = node, val[v] = w, dfs(v);
	++t;
	finish[node] = t, lin[t] = -val[node];
}

void build(int l, int r, int idx) {
	if (l == r) {
		tree[idx] = lin[l];
		return;
	}
	int m = (l + r) >> 1;
	build(l, m, idx << 1), build(m + 1, r, (idx << 1) | 1);
	tree[idx] = tree[idx << 1] + tree[(idx << 1) | 1];
}

void update(int i, int w, int l, int r, int idx) {
	if (l == r) {
		tree[idx] = w;
		return;
	}

	int m = (l + r) >> 1;
	if (i <= m) update(i, w, l, m, idx << 1);
	else update(i, w, m + 1, r, (idx << 1) | 1);
	tree[idx] = tree[idx << 1] + tree[(idx << 1) | 1];
} 

int query(int ql, int qr, int l, int r, int idx) {
	if (r < ql || l > qr) return 0;
	if (l >= ql && r <= qr) return tree[idx];

	int m = (l + r) >> 1;
	return query(ql, qr, l, m, idx << 1) + query(ql, qr, m + 1, r, (idx << 1) | 1);
}

int32_t main() {
	std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
	int n; cin >> n;
	int u, v, w;
	for (int i = 1; i <= n - 1; i++)
		cin >> u >> v >> w, graph[u].push_back({v, w}), graph[v].push_back({u, w}), edges[i] = {u, v};

	int root = 1;
	val[root] = 0;
	parent[root] = -1;
	dp[0][root] = -1;
	depth[root] = 0;
	dfs(root);
	build(1, 2 * n, 1);
	for (int i = 1; i <= LOG; i++)
		for (int j = 1; j <= n; j++)
			if (dp[i - 1][j] == -1) dp[i][j] = -1;
			else dp[i][j] = dp[i - 1][dp[i - 1][j]];


	int q; cin >> q;
	while (q--) {
		int t, x, y; cin >> t >> x >> y;
		if (t == 1) {
			auto [a, b] = edges[x];
			if (parent[b] == a) swap(a, b);
			update(start[a], y, 1, 2 * n, 1), update(finish[a], -y, 1, 2 * n, 1); 
		} else {
			int a = query(start[root], start[x], 1, 2 * n, 1);
			int b = query(start[root], start[y], 1, 2 * n, 1);
			int c = query(start[root], start[lca(x, y)], 1, 2 * n, 1);
			cout << a + b - 2 * c << endl;
		}
	}

	return 0;
}
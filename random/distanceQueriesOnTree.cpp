#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MAX (int)(2 * 1e5)

int tree[8 * MAX + 1];
int lin[2 * MAX + 1], start[MAX + 1], finish[MAX + 1];

int t = 0;
int val[MAX + 1];
vector<vector<pair<int, int>>> graph[MAX + 1];

void dfs(int node, int parent) {
	++t;
	start[node] = t, lin[t] = val[node];
	for (auto &[v, w] : graph[node])
		if (v != parent) 
			val[v] = w, dfs(v, node);
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
	int n; cin >> n;
	int u, v, w;
	for (int i = 1; i <= n - 1; i++)
		cin >> u >> v >> w, graph[u].push_back({v, w}), graph[v].push_back({u, w});

	int root = 1;
	val[root] = 0;
	dfs(root, -1);
}
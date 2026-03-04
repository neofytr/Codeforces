#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MAX (int)(2 * 1e5)

vector<int> graph[MAX + 1];
int tree[8 * MAX + 8];
int val[MAX + 1];

int lin[2 * MAX + 1];
int post[MAX + 1];
int pre[MAX + 1];
int t = 0;

void build(int l, int r, int idx) {
	if (l == r) {
		tree[idx] = lin[l];
		return;
	}

	int m = (l + r) >> 1;
	build(l, m, idx << 1), build(m + 1, r, (idx << 1) | 1);
	tree[idx] = tree[idx << 1] + tree[(idx << 1) | 1];
}

int query(int ql, int qr, int l, int r, int idx) {
	if (r < ql || l > qr) return 0;
	if (l >= ql && r <= qr) return tree[idx];
	int m = (l + r) >> 1;
	int res = query(ql, qr, l, m, idx << 1) + query(ql, qr, m + 1, r, (idx << 1) | 1);
	return res;
}

void update(int i, int val, int l, int r, int idx) {
	if (l == r) {
		tree[idx] = val;
		return;
	}

	int m = (l + r) >> 1;
	if (i <= m) update(i, val, l, m, idx << 1);
	else update(i, val, m + 1, r, (idx << 1) | 1);
	tree[idx] = tree[idx << 1] + tree[(idx << 1) | 1];
}

void dfs(int node, int parent) {
	++t;
	pre[node] = t;
	lin[t] = val[node];
	for (int v : graph[node])
		if (v != parent) dfs(v, node);

	post[node] = t;
}


int32_t main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int n, q; cin >> n >> q;
	for (int i = 1; i <= n; i++) cin >> val[i];
	int u, v;
	for (int i = 1; i <= n - 1; i++)
		cin >> u >> v, graph[u].push_back(v), graph[v].push_back(u);

	dfs(1, -1);
	build(1, 2 * n, 1);
	while (q--) {
		int t; cin >> t;
		if (t == 1) {
			int s, x; cin >> s >> x;
			update(pre[s], x, 1, 2 * n, 1);
		} else {
			int s; cin >> s;
			cout << query(pre[s], post[s], 1, 2 * n, 1) << endl;
		}
	}
	return 0;
}
#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MAX (int)(2 * 1e5)

int tree[4 * MAX + 1], lazy[4 * MAX + 1];
vector<int> graph[MAX + 1];

int v[MAX + 1];
int lin[MAX + 1], start[MAX + 1], finish[MAX + 1];
int t = 0;

void dfs(int node) {
	++t;
	start[node] = t;
	lin[t] = v[node];
	for (int v : graph[node]) dfs(v);
	finish[node] = t;
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

void push(int l, int r, int idx) {
	if (!lazy[idx]) return;

	tree[idx] = (r - l + 1) - tree[idx];
	if (l != r)
		lazy[idx << 1] ^= 1, lazy[(idx << 1) | 1] ^= 1;
	lazy[idx] = 0;
}

void update(int ql, int qr, int l, int r, int idx) {
	push(l, r, idx);
	if (r < ql || l > qr) return;
	if (l >= ql && r <= qr) {
		lazy[idx] ^= 1;
		push(l, r, idx);
		return;
	}

	int m = (l + r) >> 1;
	update(ql, qr, l, m, idx << 1), update(ql, qr, m + 1, r, (idx << 1) | 1);
	tree[idx] = tree[idx << 1] + tree[(idx << 1) | 1];
}

int query(int ql, int qr, int l, int r, int idx) {
	push(l, r, idx);
	if (r < ql || l > qr) return 0;
	if (l >= ql && r <= qr) return tree[idx];
	int m = (l + r) >> 1;
	return query(ql, qr, l, m, idx << 1) + query(ql, qr, m + 1, r, (idx << 1) | 1);
}

int32_t main() {
	int n; cin >> n;
	int root = 1;

	int p;
	for (int i = 2; i <= n; i++) cin >> p, graph[p].push_back(i);
	for (int i = 1; i <= n; i++) cin >> v[i];

	int q; cin >> q;
	dfs(root);
	build(1, n, 1);
	while (q--) {
		string t; int v;
		cin >> t >> v;
		if (t == "get") cout << query(start[v], finish[v], 1, n, 1) << endl;
		else update(start[v], finish[v], 1, n, 1);
	}
	return 0;
}
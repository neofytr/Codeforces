#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MAX (int)(4 * 1e5)

int c[MAX + 1];
vector<int> graph[MAX + 1];

int lin[MAX + 1];
int pre[MAX + 1], post[MAX + 1];
int t = 0;

int tree[4 * MAX + 1];
int lazy[4 * MAX + 1];

void dfs(int node, int parent) {
	++t;
	pre[node] = t;
	lin[t] = c[node];
	for (int v : graph[node])
		if (v != parent) dfs(v, node);

	post[node] = t;
}

void build(int l, int r, int idx) {
	if (l == r) {
		tree[idx] = (1ll << lin[l]);
		return;
	}

	int m = (l + r) >> 1;
	build(l, m, idx << 1), build(m + 1, r, (idx << 1) | 1);
	tree[idx] = tree[idx << 1] | tree[(idx << 1) | 1];
}

void push(int l, int r, int idx) {
	if (!lazy[idx]) return;
	tree[idx] = (1ll << lazy[idx]);

	if (l != r) {
		lazy[idx << 1] = lazy[idx];
		lazy[(idx << 1) | 1] = lazy[idx]; 
	}

	lazy[idx] = 0;
}

int query(int ql, int qr, int l, int r,  int idx) {
	push(l, r, idx);
	if (r < ql || l > qr) return 0;
	if (l >= ql && r <= qr) return tree[idx];

	int m = (l + r) >> 1;
	return query(ql, qr, l, m, idx << 1) | query(ql, qr, m + 1, r, (idx << 1) | 1);
}

void update(int ql, int qr, int v, int l, int r, int idx) {
	push(l, r, idx); // even if we return from this segment as it was out of bounds, if we don't push
	// the segments value may be incorrect due to a lazy value propagated below
	if (r < ql || l > qr) return;
	if (l >= ql && r <= qr) {
		lazy[idx] = v;
		push(l, r, idx);
		return;
	}

	int m = (l + r) >> 1;
	update(ql, qr, v, l, m, idx << 1), update(ql, qr, v, m + 1, r, (idx << 1) | 1);
	tree[idx] = tree[idx << 1] | tree[(idx << 1) | 1];
}

int32_t main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	
	int n, m; cin >> n >> m;
	for (int i = 1; i <= n; i++) cin >> c[i];
	int u, v;
	for (int i = 1; i <= n - 1; i++)
		cin >> u >> v, graph[u].push_back(v), graph[v].push_back(u);

	dfs(1, -1);
	build(1, n, 1);
	while (m--) {
		int k; cin >> k;
		if (k == 1) {
			int vk, ck; cin >> vk >> ck;
			update(pre[vk], post[vk], ck, 1, n, 1);
		} else {
			int vk; cin >> vk;
			int i = query(pre[vk], post[vk], 1, n, 1);
			cout << __builtin_popcountll(i) << endl;
		}
	}
	return 0;
}
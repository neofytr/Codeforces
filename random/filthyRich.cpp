#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MAX (int)(3 * 1e5)
#define double long double

vector<int> graph[MAX + 1];

int t = 0;
double lin[MAX + 1];
int start[MAX + 1], finish[MAX + 1];
void dfs(int node, int parent) {
	++t; 
	start[node] = t;
	lin[t] = 1.0;
	for (int x : graph[node])
		if (x != parent) dfs(x, node);
	finish[node] = t;
}

double tree[4 * MAX + 1];
void build(int l, int r, int idx) {
	if (l == r) {
		tree[idx] = lin[r];
		return;
	}

	int m = (l + r) >> 1;
	build(l, m, idx << 1), build(m + 1, r, (idx << 1) | 1);
	tree[idx] = tree[idx << 1] * tree[(idx << 1) | 1];
}

void update(int i, double val, int l, int r, int idx) {
	if (l == r) {
		tree[idx] = val;
		return;
	}

	int m = (l + r) >> 1;
	if (i <= m) update(i, val, l, m, idx << 1);
	else update(i, val, m + 1, r, (idx << 1) | 1);
	tree[idx] = tree[idx << 1] * tree[(idx << 1) | 1];
}

double query(int ql, int qr, int l, int r, int idx) {
	if (r < ql || l > qr) return 1;
	if (l >= ql && r <= qr) return tree[idx];

	int m = (l + r) >> 1;
	return query(ql, qr, l, m, idx << 1) * query(ql, qr, m + 1, r, (idx << 1) | 1);
}

int32_t main() {
	int n; cin >> n;

	int u, v;
	for (int i = 1; i <= n - 1; i++)
		cin >> u >> v, graph[u].push_back(v), graph[v].push_back(u);

	int root = 1;
	dfs(root, -1);
	build(1, n, 1);

	int q; cin >> q;
	while (q--) {
		int t, x, y; cin >> t >> x >> y;
		if (t == 1) 
			update(start[x], y, 1, n, 1);
		else {
			double one = query(start[x], finish[x], 1, n, 1);
			double two = query(start[y], finish[y], 1, n, 1);
			if (one > 1e9 * two)
				cout << (int)(1e9) << endl;
			else cout << setprecision(24) << one / two << endl;
		}
	}
	return 0;
}
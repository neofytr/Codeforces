#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MAX (int)(3e5)

vector<int> graph[MAX + 1];

int timer = 0;
int start[MAX + 1], finish[MAX + 1];

void dfs(int node, int parent) {
	start[node] = ++timer;

	for (int x : graph[node])
		if (x != parent)
			dfs(x, node);

	finish[node] = timer;
}

double tree[4 * MAX + 5];

void build(int l, int r, int idx) {
	if (l == r) {
		tree[idx] = 0; // log(1)
		return;
	}

	int m = (l + r) >> 1;

	build(l, m, idx << 1);
	build(m + 1, r, idx << 1 | 1);

	tree[idx] = tree[idx << 1] + tree[idx << 1 | 1];
}

void update(int pos, double val, int l, int r, int idx) {
	if (l == r) {
		tree[idx] = val;
		return;
	}

	int m = (l + r) >> 1;

	if (pos <= m)
		update(pos, val, l, m, idx << 1);
	else
		update(pos, val, m + 1, r, idx << 1 | 1);

	tree[idx] = tree[idx << 1] + tree[idx << 1 | 1];
}

double query(int ql, int qr, int l, int r, int idx) {
	if (r < ql || l > qr) return 0;

	if (ql <= l && r <= qr)
		return tree[idx];

	int m = (l + r) >> 1;

	return query(ql, qr, l, m, idx << 1)
	     + query(ql, qr, m + 1, r, idx << 1 | 1);
}

int32_t main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int n;
	cin >> n;

	for (int i = 1; i < n; i++) {
		int u, v;
		cin >> u >> v;
		graph[u].push_back(v);
		graph[v].push_back(u);
	}

	dfs(1, -1);

	build(1, n, 1);

	int q;
	cin >> q;

	const double LIMIT = log(1e9);

	while (q--) {
		int type, x;
		long long y;

		cin >> type >> x >> y;

		if (type == 1) {
			update(start[x], log((double)y), 1, n, 1);
		}
		else {
			double one = query(start[x], finish[x], 1, n, 1);
			double two = query(start[y], finish[y], 1, n, 1);

			double diff = one - two;

			if (diff > LIMIT)
				cout << 1000000000 << "\n";
			else
				cout << fixed << setprecision(12) << exp(diff) << "\n";
		}
	}
}
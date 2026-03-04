#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve() {
	int q; 
	cin >> q;

	vector<pair<int, int>> queries;

	int n = 1;
	while (q--) {
		int t; 
		cin >> t;

		if (t == 1) {
			int v; 
			cin >> v;
			n++;
			queries.push_back({-1, v});
		} else {
			int v, x; 
			cin >> v >> x;
			queries.push_back({v, x});
		}
	}

	int sz = 1;
	vector<vector<int>> graph(n + 1);

	for (auto &[x, y] : queries) {
		if (x == -1) {
			++sz;
			graph[y].push_back(sz);
			graph[sz].push_back(y);
		}
	}

	vector<int> val(n + 1, 0);
	vector<int> start(n + 1), finish(n + 1);

	int timer = 0;

	auto dfs = [&](auto &&self, int node, int parent) -> void {
		++timer;
		start[node] = timer;

		for (int x : graph[node])
			if (x != parent)
				self(self, x, node);

		finish[node] = timer;
	};

	dfs(dfs, 1, -1);

	vector<int> tree(4 * n + 1, 0), lazy(4 * n + 1, 0);

	auto push = [&](int l, int r, int idx) {
		if (!lazy[idx]) return;

		tree[idx] += (r - l + 1) * lazy[idx];

		if (l != r) {
			lazy[idx << 1] += lazy[idx];
			lazy[(idx << 1) | 1] += lazy[idx];
		}

		lazy[idx] = 0;
	};

	function<int(int,int,int,int,int)> query =
	[&](int ql, int qr, int l, int r, int idx) -> int {
		push(l, r, idx);

		if (r < ql || l > qr) return 0;

		if (l >= ql && r <= qr)
			return tree[idx];

		int m = (l + r) >> 1;

		return query(ql, qr, l, m, idx << 1)
		     + query(ql, qr, m + 1, r, (idx << 1) | 1);
	};

	function<void(int,int,int,int,int,int)> update =
	[&](int ql, int qr, int val, int l, int r, int idx) {
		push(l, r, idx);

		if (r < ql || l > qr) return;

		if (l >= ql && r <= qr) {
			lazy[idx] += val;
			push(l, r, idx);
			return;
		}

		int m = (l + r) >> 1;

		update(ql, qr, val, l, m, idx << 1);
		update(ql, qr, val, m + 1, r, (idx << 1) | 1);

		tree[idx] = tree[idx << 1] + tree[(idx << 1) | 1];
	};

	sz = 1;

	for (auto &[x, y] : queries) 
		if (x == -1) {
			++sz;
			int i = query(start[sz], finish[sz], 1, n, 1);
			i /= (finish[sz] - start[sz] + 1);
			update(start[sz], finish[sz], -i, 1, n, 1);
		}
		else 
			update(start[x], finish[x], y, 1, n, 1);

	for (int i = 1; i <= n; i++)
		cout << query(start[i], start[i], 1, n, 1) << " ";

	cout << endl;
}

int32_t main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int t; 
	cin >> t;

	while (t--)
		solve();

	return 0;
}
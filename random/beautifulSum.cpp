#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MAX (int)(1e5)
#define LOG (20)

struct XOR {
	int size = 0;
	int cnt[LOG + 1] = {0};
};

struct Node {
	XOR even, odd;
};

void solve() {
	int n; cin >> n;
	int u, v, w;
	int root = 1;
	int t = 0;

	vector<int> dp(n + 1);
	vector<int> depth(n + 1);

	vector<int> lin(n + 1), start(n + 1), finish(n + 1);
	vector<int> euler_node(n + 1);
	vector<vector<pair<int,int>>> graph(n + 1);

	for (int i = 1; i <= n - 1; i++)
		cin >> u >> v >> w,
		graph[u].push_back({v, w}),
		graph[v].push_back({u, w});

	auto dfs = [&](auto &&self, int x, int p) -> void {
		for (auto &[v, w] : graph[x])
			if (v != p) {
				depth[v] = depth[x] ^ 1;
				dp[v] = dp[x] ^ w;
				self(self, v, x);
			}
	};

	dp[root] = 0;
	depth[root] = 0;
	dfs(dfs, root, -1);

	auto euler = [&](auto &&self, int x, int p) -> void {
		++t;
		start[x] = t;
		lin[t] = dp[x];
		euler_node[t] = x;

		for (auto &[v, w] : graph[x])
			if (v != p)
				self(self, v, x);

		finish[x] = t;
	};

	euler(euler, root, -1);
	vector<Node> tree(4 * n + 1);
	vector<int> lazy_even(4 * n + 1);
	vector<int> lazy_odd(4 * n + 1);

	auto combine = [&](Node &L, Node &R) -> Node {
		Node node;

		node.even.size = L.even.size + R.even.size;
		node.odd.size  = L.odd.size  + R.odd.size;

		for (int i = 0; i <= LOG; i++) {
			node.even.cnt[i] = L.even.cnt[i] + R.even.cnt[i];
			node.odd.cnt[i]  = L.odd.cnt[i]  + R.odd.cnt[i];
		}

		return node;
	};

	auto build = [&](auto &&self, int l, int r, int idx) -> void {
		if (l == r) {
			XOR &even = tree[idx].even;
			XOR &odd  = tree[idx].odd;

			int node = euler_node[l];
			int val  = lin[l];
			if (!depth[node]) {
				even.size = 1;
				for (int i = 0; i <= LOG; i++)
					even.cnt[i] = (val >> i) & 1;
			} else {
				odd.size = 1;
				for (int i = 0; i <= LOG; i++)
					odd.cnt[i] = (val >> i) & 1;
			}
			return;
		}

		int m = (l + r) >> 1;

		self(self, l, m, idx << 1);
		self(self, m + 1, r, idx << 1 | 1);

		tree[idx] = combine(tree[idx << 1], tree[idx << 1 | 1]);
	};

	auto apply = [&](XOR &grp, int x) {
		for (int i = 0; i <= LOG; i++)
			if (x & (1LL << i))
				grp.cnt[i] = grp.size - grp.cnt[i];
	};

	auto push = [&](int l, int r, int idx) {
		if (lazy_even[idx])
			apply(tree[idx].even, lazy_even[idx]);
		if (lazy_odd[idx])
			apply(tree[idx].odd, lazy_odd[idx]);
		if (l != r) {
			lazy_even[idx << 1] ^= lazy_even[idx];
			lazy_even[idx << 1 | 1] ^= lazy_even[idx];

			lazy_odd[idx << 1] ^= lazy_odd[idx];
			lazy_odd[idx << 1 | 1] ^= lazy_odd[idx];
		}

		lazy_even[idx] = 0;
		lazy_odd[idx] = 0;
	};

	auto update = [&](auto &&self, int ql, int qr, int x_even, int x_odd, int l, int r, int idx) -> void {
		push(l, r, idx);
		if (qr < l || r < ql) return;
		if (l >= ql && r <= qr) {
			lazy_even[idx] ^= x_even;
			lazy_odd[idx] ^= x_odd;
			push(l, r, idx);
			return;
		}

		int m = (l + r) >> 1;
		self(self, ql, qr, x_even, x_odd, l, m, idx << 1);
		self(self, ql, qr, x_even, x_odd, m + 1, r, idx << 1 | 1);
		tree[idx] = combine(tree[idx << 1], tree[idx << 1 | 1]);
	};

	auto query = [&](auto &&self, int ql, int qr, int l, int r, int idx) -> Node {
		push(l, r, idx);
		if (qr < l || r < ql)
			return Node();
		if (l >= ql && r <= qr)
			return tree[idx];

		int m = (l + r) >> 1;
		Node left  = self(self, ql, qr, l, m, idx << 1);
		Node right = self(self, ql, qr, m + 1, r, idx << 1 | 1);
		return combine(left, right);
	};

	auto ans = [&](Node &node) -> int {
		int res = 0;
		for (int bit = 0; bit <= LOG; bit++) {
			int e1 = node.even.cnt[bit];
			int e0 = node.even.size - e1;
			int o1 = node.odd.cnt[bit];
			int o0 = node.odd.size - o1;
			res += (e1 * e0 + o1 * o0 + e1 * o0 + e0 * o1) * (1LL << bit);
		}
		return res;
	};

	build(build, 1, n, 1);
	int q; cin >> q;
	while (q--) {
		int k; cin >> k;
		if (k == 1) {
			int u, x; cin >> u >> x;
			int xe = 0, xo = 0;
			if (!(depth[u] & 1)) xo = x;
			else xe = x;
			update(update, start[u], finish[u], xe, xo, 1, n, 1);

		}
		else {
			int u; cin >> u;
			Node res = query(query, start[u], finish[u], 1, n, 1);
			cout << ans(res) << endl;
		}
	}
}

int32_t main() {
	int t; cin >> t;
	while (t--) solve();
}
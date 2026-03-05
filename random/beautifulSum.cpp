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
	vector<int> lin(n + 1), start(n + 1), finish(n + 1);

	vector<vector<pair<int, int>>> graph(n + 1);
	for (int i = 1; i <= n - 1; i++)
		cin >> u >> v >> w,
		graph[u].push_back({v, w}),
		graph[v].push_back({u, w});

	auto dfs = [&](auto &&self, int x, int p) -> void {
		for (auto &[v, w] : graph[x])
			if (v != p)
				dp[v] = w ^ dp[x], self(self, v, x);
	};

	dp[root] = 0;
	dfs(dfs, root, -1);

	auto euler = [&](auto &&self, int x, int p) -> void {
		++t;
		start[x] = t;
		lin[t] = dp[x];

		for (auto &[v, w] : graph[x])
			if (v != p)
				self(self, v, x);

		finish[x] = t;
	};

	euler(euler, root, -1);

	vector<Node> tree(4 * n + 1);
	vector<int> lazy(4 * n + 1);

	auto combine = [&](Node &left, Node &right) -> Node {
		Node node;
		XOR &even = node.even;
		XOR &odd = node.odd;

		even.size = left.odd.size + right.odd.size;
		odd.size  = left.even.size + right.even.size;
		for (int i = 0; i <= LOG; i++) {
			even.cnt[i] = left.odd.cnt[i] + right.odd.cnt[i];
			odd.cnt[i]  = left.even.cnt[i] + right.even.cnt[i];
		}
		return node;
	};

	auto build = [&](auto &&self, int l, int r, int idx) -> void {
		if (l == r) {
			XOR &even = tree[idx].even;
			XOR &odd = tree[idx].odd;

			even.size = 1;
			odd.size = 0;
			for (int i = 0; i <= LOG; i++) {
				even.cnt[i] = (lin[l] >> i) & 1;
				odd.cnt[i] = 0;
			}
			return;
		}

		int m = (l + r) >> 1;

		self(self, l, m, idx << 1);
		self(self, m + 1, r, idx << 1 | 1);

		tree[idx] = combine(tree[idx << 1], tree[idx << 1 | 1]);
	};

	auto ans = [&](Node &node) -> int {
		int res = 0;
		XOR &even = node.even;
		XOR &odd = node.odd;

		for (int bit = 0; bit <= LOG; bit++) {
			res += (
				even.cnt[bit] * (even.size - even.cnt[bit]) +
				odd.cnt[bit]  * (odd.size  - odd.cnt[bit]) +
				odd.cnt[bit]  * (even.size - even.cnt[bit]) +
				even.cnt[bit] * (odd.size  - odd.cnt[bit])
			) * (1LL << bit);
		}
		return res;
	};

	auto push = [&](int l, int r, int idx) -> void {
		if (!lazy[idx]) return;
		XOR &odd = tree[idx].odd;
		for (int i = 0; i <= LOG; i++)
			if (lazy[idx] & (1LL << i))
				odd.cnt[i] = odd.size - odd.cnt[i];
		if (l != r) {
			lazy[idx << 1] ^= lazy[idx];
			lazy[idx << 1 | 1] ^= lazy[idx];
		}
		lazy[idx] = 0;
	};

	auto update = [&](auto &&self, int ql, int qr, int x, int l, int r, int idx) -> void {
		push(l, r, idx);
		if (qr < l || r < ql) return;
		if (l >= ql && r <= qr) {
			lazy[idx] ^= x;
			push(l, r, idx);
			return;
		}

		int m = (l + r) >> 1;
		self(self, ql, qr, x, l, m, idx << 1);
		self(self, ql, qr, x, m + 1, r, idx << 1 | 1);
		tree[idx] = combine(tree[idx << 1], tree[idx << 1 | 1]);
	};

	auto query = [&](auto &&self, int ql, int qr, int l, int r, int idx) -> int {
		push(l, r, idx);
		if (qr < l || r < ql) return 0;
		if (l >= ql && r <= qr)
			return ans(tree[idx]);
		int m = (l + r) >> 1;
		return self(self, ql, qr, l, m, idx << 1)
		     + self(self, ql, qr, m + 1, r, idx << 1 | 1);
	};

	build(build, 1, n, 1);
	int q; cin >> q;
	while (q--) {
		int k; cin >> k;
		if (k == 1) {
			int u, x; cin >> u >> x;
			update(update, start[u] + 1, finish[u], x, 1, n, 1);
		}
		else {
			int u; cin >> u;
			cout << query(query, start[u] + 1, finish[u], 1, n, 1) << endl;
		}
	}
}

int32_t main() {
	int t; cin >> t;
	while (t--) solve();
	return 0;
}
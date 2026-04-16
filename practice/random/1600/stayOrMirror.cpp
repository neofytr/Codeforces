#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MAX (5 * 1e3)

int tree[4 * MAX + 1];

int query(int ql, int qr, int l, int r, int idx) {
	if (l < qr || ql > r) return 0;
	if (l >= ql && r <= qr) return tree[idx];

	int m = (l + r) >> 1;
	return query(ql, qr, l, m, idx << 1) + query(ql, qr, m + 1, r, (idx << 1) | 1);
}

void update(int v, int l, int r, int idx) {
	if (l == r) {
		tree[idx]++; 
		return;
	}

	int m = (l + r) >> 1;
	if (v <= m) update(v, l, m, idx << 1);
	else update(v, m + 1, r, (idx << 1) | 1);
	tree[idx] = tree[idx << 1] + tree[(idx << 1) | 1];
}

void solve() {
	int n, m = -1; cin >> n;
	vector<int> p(n + 1);
	for (int i = 1; i <= n; i++) cin >> p[i], m = max(m, p[i]);
	for (int i = 1; i <= 4 * n; i++) tree[i] = 0;

	vector<vector<int>> dp(n + 1, vector<int>(2, LLONG_MAX));
	dp[1] = 0, update(p[1], 1, m, 1);
	for (int i = 2; i <= n; i++) {
		dp[i][0] = min(dp[i - 1][0], dp[i - 1][1])  + query(p[i] + 1, m, 1, m, 1);
		dp[i][1] = min(dp[i - 1][0], dp[i - 1][1]) + query(2 * n - p[i] + 1, m, 1, m, 1)

	}
	
	cout << min(dp[i][0], dp[i][1]) << endl;
}

int32_t main() {
	int t; cin >> t;
	while (t--) solve();
	return 0;
}
#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MAX (int)(1e5)
#define INF (int)(1e18)

int tree[4 * MAX + 1];

void init(int l = 0, int r = MAX, int idx = 1) {
	tree[idx] = INF;
	if (l == r) return;
	int m = (l + r) >> 1;
	init(l, m, idx << 1), init(m + 1, r, (idx << 1) | 1);
}

void update(int i, int val, int l = 0, int r = MAX, int idx = 1) {
	if (l == r) {
		tree[idx] = val;
		return;
	}

	int m = (l + r) >> 1;
	if (i <= m) update(i, val, l, m, idx << 1);
	else update(i, val, m + 1, r, (idx << 1) | 1);
	tree[idx] = min(tree[idx << 1], tree[(idx << 1) | 1]);
}

int query(int ql, int qr, int l = 0, int r = MAX, int idx = 1) {
	if (r < ql || l > qr) return INF;
	if (l >= ql && r <= qr) return tree[idx];

	int m = (l + r) >> 1;
	return min(query(ql, qr, l, m, idx << 1), query(ql, qr, m + 1, r, (idx << 1) | 1));
}

int32_t main() {
	int n; cin >> n;
	vector<int> a(n);
	for (int i = 1; i <= n - 1; i++) cin >> a[i];

	// dp[i] = summation(p(i, j) for i < j <= n)
	init();
	vector<int> dp(n + 1);
	dp[n - 1] = 1, update(n - 1, dp[n - 1] + n - 1);
	for (int i = n - 2; i >= 1; i--) 
		dp[i] = n + query(i + 1, a[i]) - a[i] - i, update(i, dp[i] + i);

	int cnt = 0;
	for (int i = 1; i <= n - 1; i++) cnt += dp[i];
	cout << cnt << endl;
	return 0;
}
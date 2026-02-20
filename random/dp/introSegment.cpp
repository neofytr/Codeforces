#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MAX (int)(2 * 1e5)

int tree[4 * MAX + 1];

void update(int i, int x, int l, int r, int idx) {
	if (i < l || i > r) return;
	if (l == r) {
		tree[idx] = x;
		return;
	}

	int m = (l + r) >> 1;
	if (i <= m)
		update(i, x, l, m, 2 * idx);
	else 
		update(i, x, m + 1, r, 2 * idx + 1);
	tree[idx] = min(tree[2 * idx], tree[2 * idx + 1]);
}

int query(int ql, int qr, int l, int r, int idx) {
	if (qr < l || ql > r) return LLONG_MAX;
	if (l >= ql && r <= qr) return tree[idx];
	int m = (l + r) >> 1;
	int left = query(ql, qr, l, m, 2 * idx);
	int right = query(ql, qr, m + 1, r, 2 * idx + 1);
	return min(left, right);
}

int32_t main() {
	int n; cin >> n;
	vector<int> arr(n + 1);
	for (int r = 1; r <= n; r++) cin >> arr[r];

	vector<pair<int, int>> ran(n + 1);
	for (int r = 2; r <= n; r++) cin >> ran[r].first >> ran[r].second;

	// dp[r] is the minimum cost to get from 1 to r
	vector<int> dp(n + 1), p(n + 1, 0);
	dp[1] = 0;
	for (int r = 1; r <= n; r++) p[r] += p[r - 1] + arr[r];
	update(1, dp[1] - p[1 - 1], 1, n, 1);

	cout << dp[1] << " ";
	for (int i = 2; i <= n; i++) {
		// we can only come to i from 0 <= [l, r] < i
		auto [l, r] = ran[i];
		dp[i] = p[i] + query(l, r, 1, n, 1);
		update(i, dp[i] - p[i - 1], 1, n, 1);
		cout << dp[i] << " ";
	}
	cout << endl;
	return 0;
}
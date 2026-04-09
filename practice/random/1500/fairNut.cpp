#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MOD (int)(1e9 + 7)
#define MAX (int)(1e5)

int tree[4 * MAX + 1];

void update(int i, int val, int l, int r, int idx) {
	if (l == r) {
		tree[idx] = val % MOD;
		return;
	}

	int m = (l + r) >> 1;
	if (i <= m) update(i, val, l, m, idx << 1);
	else update(i, val, m + 1, r, (idx << 1) | 1);
	tree[idx] = (tree[idx << 1] + tree[(idx << 1) | 1]) % MOD;
}

int query(int ql, int qr, int l, int r, int idx) {
	if (qr < l || ql > r) return 0;
	if (l >= ql && r <= qr) return tree[idx] % MOD;

	int m = (l + r) >> 1;
	return (query(ql, qr, l, m, idx << 1) + query(ql, qr, m + 1, r, (idx << 1) | 1)) % MOD;
}


int32_t main() {
	string s; cin >> s;
	int n = s.length();
	vector<int> a(n + 1);
	for (int r = 1; r <= n; r++) a[r] = s[r - 1] - 'a';

	vector<int> last(n + 1, -1);
	for (int r = 1; r <= n; r++)
		if (a[r] == 1) last[r] = r;
		else last[r] = last[r - 1];


	vector<int> dp(n + 1, 0);
	for (int r = 1; r <= n; r++)
		if (!a[r]) {
			int l = last[r];
			dp[r] = 1;
			if (l != -1)
				dp[r] = (dp[r] + query(1, l, 1, n, 1)) % MOD;
			update(r, dp[r], 1, n, 1);
		} 

	int cnt = 0;
	for (int r = 1; r <= n; r++) cnt = (cnt + dp[r]) % MOD;
	cout << cnt << endl;
	return 0;
}
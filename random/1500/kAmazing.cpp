#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MAX (int)(3 * 1e5)

int tree[4 * MAX + 1];
int a[MAX + 1];

void build(int l, int r, int idx) {
	if (l == r) {
		tree[idx] = a[l];
		return;
	}

	int m = (l + r) >> 1;
	build(l, m, idx << 1);
	build(m + 1, r, (idx << 1) | 1);
	tree[idx] = min(tree[idx << 1], tree[(idx << 1) | 1]);
}

int query(int ql, int qr, int l, int r, int idx) {
	if (qr < l || ql > r) return LLONG_MAX;
	if (l >= ql && r <= qr) return tree[idx];

	int m = (l + r) >> 1;
	return min(query(ql, qr, l, m, idx << 1), query(ql, qr, m + 1, r, (idx << 1) | 1));
}

void solve() {
	int n; cin >> n;
	for (int r = 1; r <= n; r++) cin >> a[r];

	vector<int> f(n + 1, 0);
	set<pair<int, int>> s;
	for (int k = 1; k <= n; k++) {
		bool found = false; int mini = LLONG_MAX;
		for (int j = k; j <= n; j += k) {
			f[a[j]]++;
			if (f[a[j]] >= n - k + 1) {
				found = true;
				mini = min(mini, a[j]);
			}
		}

		cout << (found ? mini : - 1) << " ";
	}
	cout << endl;
}

int32_t main() {
	int t; cin >> t;
	while (t--) solve();
	return 0;
}
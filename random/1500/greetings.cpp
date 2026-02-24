#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MAX (int)(2 * 1e5)

int tree[4 * MAX + 1];
int n;
void update(int i, int l, int r, int idx) {
	if (l == r) {
		tree[idx] = 1;
		return;
	}

	int m = (l + r) >> 1;
	if (i <= m) update(i, l, m, idx << 1);
	else update(i, m + 1, r, (idx << 1) | 1);
	tree[idx] = tree[idx << 1] + tree[(idx << 1) | 1];
}

int query(int ql, int qr, int l, int r, int idx) {
	if (ql > r || qr < l) return 0;
	if (l >= ql && r <= qr) return tree[idx];

	int m = (l + r) >> 1;
	return query(ql, qr, l, m, idx << 1) + query(ql, qr, m + 1, r, (idx << 1) | 1);
}

void solve() {
	int n; cin >> n;
	vector<pair<int, int>> v(n + 1);
	vector<int> b(n + 1);
	for (int r = 1; r <= n; r++)
		cin >> v[r].first >> v[r].second, b[r] = v[r].second;

	sort(v.begin() + 1, v.end()), sort(b.begin() + 1, b.end());
	for (int r = 0; r <= 4 * n; r++) tree[r] = 0;
	int i = lower_bound(b.begin(), b.end(), v[1].second) - b.begin();
	update(i, 0, n, 1); 

	int cnt = 0;
	for (int r = 2; r <= n; r++) {
		i = (lower_bound(b.begin(), b.end(), v[r].second) - b.begin());
		cnt += query(i, n, 0, n, 1);
		update(i, 0, n, 1);
	}

	cout << cnt << endl;
}

int32_t main() {
	int t; cin >> t;
	while (t--) solve();
	return 0;
}
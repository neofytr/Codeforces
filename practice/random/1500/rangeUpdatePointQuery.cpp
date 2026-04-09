#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MAX (int)(2 * 1e5)

int tree[4 * MAX + 1];

void update(int ql, int qr, int i, int l, int r, int idx) {
	if (r < ql || qr < l) return;
	if (l >= ql && r <= qr) {
		tree[idx] += i;
		return;
	}

	int m = (l + r) >> 1;
	update(ql, qr, i, l, m, idx << 1), update(ql, qr, i, m + 1, r, (idx << 1) | 1);
}

int get(int i, int l, int r, int idx) {
	if (l == r) return tree[idx];
	int m = (l + r) >> 1;
	if (i <= m) return tree[idx] + get(i, l, m, idx << 1);
	return tree[idx] + get(i, m + 1, r, (idx << 1) | 1);
}

void solve() {
	int n, q; cin >> n >> q;
	vector<int> a(n + 1);
	for (int i = 1; i <= n; i++) cin >> a[i];
	for (int i = 1; i <= 4 * n; i++) tree[i] = 0;

	while (q--) {
		int t; cin >> t;
		if (t == 1) {
			int l, r; cin >> l >> r;
			update(l, r, 1, 1, n, 1);
		} else {
			int x; cin >> x;
			int j = get(x, 1, n, 1);
			int i = 0;
			while (a[x] >= 10 && i < j) {
				int num = a[x];
				int sum = 0;
				while (num) {
					int d = num % 10;
					sum += d;
					num /= 10;
				}
				i++;
				a[x] = sum;
			}
			update(x, x, -j, 1, n, 1);
			cout << a[x] << endl;
		}
	}
}

int32_t main() {
	int t; cin >> t;
	while (t--) solve();
	return 0;
}
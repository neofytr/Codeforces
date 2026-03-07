#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MAX (int)(1e5)

int tree[4 * MAX + 1];

void update(int ql, int qr, int v, int l, int r, int idx) {
	if (r < ql || qr < l) return;
	if (l >= ql && r <= qr) {
		tree[idx] += v;
		return;
	}

	int m = (l + r) >> 1;
	update(ql, qr, v, l, m, idx << 1), update(ql, qr, v, m + 1, r, (idx << 1) | 1);
}

int get(int i, int l, int r, int idx) {
	if (l == r) return tree[idx];
	int m = (l + r) >> 1;
	if (i <= m) return tree[idx] + get(i, l, m, idx << 1);
	return tree[idx] + get(i, m + 1, r, (idx << 1) | 1);
}

void solve(int t) {
	int n, m, k; cin >> n >> m >> k;
	vector<int> a(m + 1);
	for (int i = 1; i <= m; i++) cin >> a[i];

	if (k > m) {
		cout << "NO" << endl;
		return;
	}

	int cnt = 0;
	for (int i = 1; i <= 4 * n; i++) tree[i] = 0;
	sort(a.begin() + 1, a.end());
	for (int i = 1; i <= m; i++)
		cout << a[i] << " ";
	cout << endl;
	for (int i = 1; i <= m - k + 1; i++) {
		int elt = a[i] - get(i, 1, n, 1);
		cnt += elt;
		update(i, i + k - 1, elt, 1, n, 1);
	}

	if (cnt < n / k) {
		cout << "NO" << endl;
		return;
	}

	int unique = 0;
	for (int i = 1; i <= m; i++)
		if (a[i] - get(i, 1, n, 1)) unique++;

	if (unique < (n % k)) {
		cout << "NO" << endl;
		return;
	}

	cout << "YES" << endl;
}

int32_t main() {
	int t; cin >> t;
	for (int i = 1; i <= t; i++) solve(i);
	return 0;
}
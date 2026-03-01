#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MAX (int)(2 * 1e5)

int tree[4 * MAX + 1];
void update(int i, int val, int l, int r, int idx) {
	if (l == r) {
		tree[idx] += val;
		return;
	}

	int m = (l + r) >> 1;
	if (i <= m) update(i, val, l, m, idx << 1);
	else update(i, val, m + 1, r, (idx << 1) | 1);
	tree[idx] = tree[idx << 1] + tree[(idx << 1) | 1];
}

int query(int ql, int qr, int l, int r, int idx) {
	if (qr < l || ql > r) return 0;
	if (l >= ql && r <= qr) return tree[idx];

	int m = (l + r) >> 1;
	return query(ql, qr, l, m, idx << 1) + query(ql, qr, m + 1, r, (idx << 1) | 1);
}

int32_t main() {
	int n; cin >> n;
	vector<pair<int, int>> segs(n + 1);
	for (int i = 1; i <= n; i++) {
		auto &[l, r] = segs[i];
		cin >> l >> r;
	}

	vector<int> right(n + 1);
	for (int i = 1; i <= n; i++)
		right[i] = segs[i].second;
	sort(right.begin() + 1, right.end()), sort(segs.begin() + 1, segs.end());

	for (int i = 1; i <= n; i++) {
		auto [l, r] = segs[i];
		int j = lower_bound(right.begin() + 1, right.end(), l) - right.begin();
		int k = lower_bound(right.begin() + 1, right.end(), r) - right.begin();
		if (query(j, n, 1, n, 1) > 1) {
			cout << "NO" << endl;
			return 0;
		}

		update(k, 1, 1, n, 1);
	}

	cout << "YES" << endl;
	return 0;
}
#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MAX (int)(3 * 1e5)

int tree[4 * MAX + 1];
void update(int i, int val, int l, int r, int idx) {
	if (l == r) {
		tree[idx] = val;
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
	vector<tuple<int, int, int>> segs(n + 1);
	for (int r = 1; r <= n; r++) {
		auto &[i, j, k] = segs[r];
		cin >> i >> j; k = r;
	}

	vector<int> right(n + 1);
	for (int r = 1; r <= n; r++) right[r] = get<1>(segs[r]);
	sort(segs.begin() + 1, segs.end(), [](const tuple<int, int, int> &one, const tuple<int, int, int> &two){
		auto &[l1, r1, k1] = one;
		auto &[l2, r2, k2] = two;
		if (l1 < l2) return true;
		if (l1 == l2 && r1 > r2) return true;
		return false;
	}), sort(right.begin() + 1, right.end());

	for (int i = 1; i <= n; i++) {
		auto [l, r, k] = segs[i];
		int j = lower_bound(right.begin() + 1, right.end(), r) - right.begin();
		if (query(j, n, 1, n, 1)) {
			for (int m = 1; m < i; m++)
				if (get<1>(segs[m]) >= r) {
					cout << k << " " << get<2>(segs[m]) << endl;
					return 0;
				}
		}
		update(j, 1, 1, n, 1);
	}

	cout << -1 << " " << -1 << endl;
	return 0;
}
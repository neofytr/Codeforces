#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MAX (int)(3 * 1e5)
#define INF (int)(1e17)

int tree1[4 * MAX + 1], tree2[4 * MAX + 1];

void build(int l, int r, int idx, vector<int> &v, int tree[]) {
	if (l == r) {
		tree[idx] = v[l];
		return;
	}
	int m = (l + r) >> 1;
	build(l, m, idx << 1, v, tree);
	build(m + 1, r, (idx << 1) | 1, v, tree);
	tree[idx] = min(tree[idx << 1], tree[(idx << 1) | 1]);
}

int query(int ql, int qr, int l, int r, int idx, int tree[]) {
	if (qr < l || r < ql) return INF;
	if (l >= ql && r <= qr) return tree[idx];

	int m = (l + r) >> 1;
	return min(
		query(ql, qr, l, m, idx << 1, tree),
		query(ql, qr, m + 1, r, (idx << 1) | 1, tree)
	);
}

void solve() {
	int n, k; cin >> n >> k;

	vector<pair<int, int>> a(k + 1, {INF, 1});
	for (int i = 1; i <= k; i++) cin >> a[i].first;
	for (int i = 1; i <= k; i++) cin >> a[i].second;

	sort(a.begin() + 1, a.end());

	vector<int> v1(k + 1), v2(k + 1);
	for (int i = 1; i <= k; i++) {
		v1[i] = a[i].second + a[i].first;
		v2[i] = a[i].second - a[i].first;
	}

	build(1, k, 1, v1, tree1);
	build(1, k, 1, v2, tree2);

	for (int i = 1; i <= n; i++) {
		int s = lower_bound(a.begin() + 1, a.end(), make_pair(i, 0ll)) - a.begin();
		int one = INF, two = INF;
		one = query(s, k, 1, k, 1, tree1) - i;
		two = query(1, s - 1, 1, k, 1, tree2) + i;
		cout << min(one, two) << " ";
	}
	cout << endl;
}

int32_t main() {
	int t; cin >> t;
	while (t--) solve();
	return 0;
}
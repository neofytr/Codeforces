#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MAX (int)(1e5)
#define INF (int)(1e15)

int tree[4 * MAX + 1];

void build(int l = 0, int r = MAX, int idx = 1) {
	tree[idx] = -INF;
	if (l == r) return;
	int m = (l + r) >> 1;
	build(l, m, idx << 1), build(m + 1, r, (idx << 1) | 1);
}

int query(int elt, int l = 0, int r = MAX, int idx = 1) {
	// [elt, MAX]
	if (MAX < l || elt > r) return -INF;
	if (l >= elt && r <= MAX) return tree[idx];

	int m = (l + r) >> 1;
	return max(query(elt, l, m, idx << 1), query(elt, m + 1, r, (idx << 1) | 1));
}

void update(int i, int val, int l = 0, int r = MAX, int idx = 1) {
	if (l == r) {
		tree[idx] = max(tree[idx], val);
		return;
	}

	int m = (l + r) >> 1;
	if (i <= m) update(i, val, l, m, idx << 1);
	else update(i, val, m + 1, r, (idx << 1) | 1);
	tree[idx] = max(tree[idx << 1], tree[(idx << 1) | 1]);
}

int32_t main() {
	int n; cin >> n;
	vector<tuple<int, int, int>> v(n + 1);
	for (int r = 1; r <= n; r++) {
		auto &[x, y, z] = v[r];
		cin >> x >> y >> z;
	}

	sort(v.begin() + 1, v.end(), [](const tuple<int, int, int> &t1, const tuple<int, int, int> &t2) {
		auto [a, x, b] = t1;
		auto [c, y, d] = t2;
		if (x < y) return true;
		if (x == y && a < c) return true;
		return false;
	});

	int i = 1;
	unordered_map<int, int> f;
	vector<int> vec;
	f[get<1>(v[1])] = i++, vec.push_back(get<1>(v[1]));
	for (int r = 2; r <= n; r++) {
		auto [a, x, b] = v[r - 1];
		auto [c, y, d] = v[r];
		if (y != x) f[y] = i++, vec.push_back(y);
	}

	build();
	vector<int> dp(n + 1);
	dp[1] = get<2>(v[1]), update(f[get<1>(v[1])], dp[1]);
	int maxi = dp[1];
	for (int r = 2; r <= n; r++) {
		auto [a, b, h] = v[r];
		int k = upper_bound(vec.begin(), vec.end(), a) - vec.begin();
		dp[r] = h;
		if (k < vec.size()) dp[r] = max(dp[r], h + query(f[vec[k]]));
		update(f[b], dp[r]);
		maxi = max(maxi, dp[r]);
	}

	cout << maxi << endl;
	return 0;
}
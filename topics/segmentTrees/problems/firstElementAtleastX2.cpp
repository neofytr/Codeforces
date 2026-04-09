#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MAX (int)(1e5)

pair<int, int> tree[4 * MAX + 1];
void build(int idx, int l, int r, vector<int> &arr) {
	if (l == r) {
		tree[idx] = {arr[l], l};
		return;
	}

	int m = (l + r) >> 1;
	build(2 * idx, l, m, arr);
	build(2 * idx + 1, m + 1, r, arr);

	auto [left, leftidx] = tree[2 * idx];
	auto [right , rightidx] = tree[2 * idx + 1];

	if (left > right) tree[idx] = {left, leftidx};
	else if (right > left) tree[idx] = {right, rightidx};
	else tree[idx] = {left, min(leftidx, rightidx)};
}

void update(int idx, int l, int r, int i, int v) {
	if (i < l || i > r) return;
	if (l == r) {
		tree[idx] = {v, l};
		return;
	}

	int m = (l + r) >> 1;
	if (i <= m) update(2 * idx, l, m, i, v);
	else update(2 * idx + 1, m + 1, r, i, v);

	auto [left, leftidx] = tree[2 * idx];
	auto [right , rightidx] = tree[2 * idx + 1];
	
	if (left > right) tree[idx] = {left, leftidx};
	else if (right > left) tree[idx] = {right, rightidx};
	else tree[idx] = {left, min(leftidx, rightidx)};
}

int query(int idx, int l, int r, int ql, int x) {
	if (tree[idx].first < x) return LLONG_MAX;
	if (r < ql) return LLONG_MAX;
	if (l == r) return l;

	int m = (l + r) >> 1;
	int left = LLONG_MAX;
	if (tree[2 * idx].first >= x)
		left = query(2 * idx, l, m, ql, x);
	if (left != LLONG_MAX) return left;
	return query(2 * idx + 1, m + 1, r, ql, x);
}

int32_t main() {
	int n, m;
	cin >> n >> m;

	vector<int> arr(n + 1);
	for (int r = 1; r <= n; r++) cin >> arr[r];

	build(1, 1, n, arr);
	while(m--) {
		int q, v, r;
		cin >> q >> v >> r;

		if (q == 1) 
			update(1, 1, n, v + 1, r);
		else { 
			int j = query(1, 1, n, r + 1, v);
			cout << (j == LLONG_MAX ? -1 : j - 1) << endl;
		}
	}
	return 0;
}
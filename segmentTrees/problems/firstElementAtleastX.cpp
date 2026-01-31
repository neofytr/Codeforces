#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MAX (int)(1e5)

int tree[4 * MAX + 1];
void build(int idx, int l, int r, vector<int> &arr) {
	if (l == r) {
		tree[idx] = arr[l];
		return;
	}

	int m = (l + r) >> 1;
	build(2 * idx, l, m, arr);
	build(2 * idx + 1, m + 1, r, arr);

	tree[idx] = max(tree[2 * idx], tree[2 * idx + 1]);
}

void update(int idx, int l, int r, int i, int v) {
	if (i < l || i > r) return;
	if (l == r) {
		tree[idx] = v;
		return;
	}

	int m = (l + r) >> 1;
	if (i <= m)
		update(2 * idx, l, m, i, v);
	else 
		update(2 * idx + 1, m + 1, r, i, v);
	tree[idx] = max(tree[2 * idx], tree[2 * idx + 1]);
}

int query(int idx, int l, int r, int x) {
	if (tree[idx] < x) return LLONG_MAX;
	if (l == r) {
		return (tree[idx] == x ? l : LLONG_MAX);
	}
	int m = (l + r) >> 1;

	int k = min(query(2 * idx, l, m, x), query(2 * idx + 1, m + 1, r, x));
	return k;
}

int32_t main() {
	int n, m;
	cin >> n >> m;

	vector<int> arr(n + 1);
	for (int r = 1; r <= n; r++) cin >> arr[r];

	build(1, 1, n, arr);
	while (m--) {
		int q, v;
		cin >> q >> v;

		if (q == 1) {
			int e; cin >> e;
			update(1, 1, n, v + 1, e);
		} else {
			int id = query(1, 1, n, v);
			cout << (id == LLONG_MAX ? -1 : id - 1) << endl;
		}
	}
	return 0;
}
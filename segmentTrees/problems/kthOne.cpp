#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MAX (int)(1e5)

int tree[4 * MAX + 1];
void build(int idx, int l, int r, vector<int> &arr) {
	if (l == r) {
		tree[idx] = arr[r];
		return;
	}

	int m = (l + r) >> 1;
	build(2 * idx, l, m, arr);
	build(2 * idx + 1, m + 1, r, arr);

	tree[idx] = tree[2 * idx] + tree[2 * idx + 1];
}

int query(int idx, int l, int r, int k) {
	if (l == r)
		return l;

	int m = (l + r) >> 1;
	if (tree[2 * idx] < k)
		return query(2 * idx + 1, m + 1, r, k);
	return query(2 * idx, l, m, k);
}

void update(int idx, int l, int r, int i) {
	if (i < l || i > r) return;
	if (l == r) {
		tree[idx] ^= 1;
		return;
	}

	int m = (l + r) >> 1;
	if (i <= m) update(2 * idx, l, m, i);
	else update(2 * idx + 1, m + 1, r, i);

	tree[idx] = tree[2 * idx] + tree[2 * idx + 1];
}

int32_t main() {
	int n, m;
	cin >> n >> m;

	vector<int> arr(n + 1);
	for (int r = 1; r <= n; r++) 
		cin >> arr[r];

	build(1, 1, n, arr);
	while (m--) {
		int q, v;
		cin >> q >> v;
		if (q == 1) 
			update(1, 1, n, v + 1);
		else 
			cout << query(1, 1, n, v + 1) - 1 << endl;
	}
	return 0;
}
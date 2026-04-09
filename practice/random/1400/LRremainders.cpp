#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MAX (int)(2 * 1e5)

int n, m;
int tree[4 * MAX + 1];
int arr[MAX + 1];
void build(int idx, int l, int r) {
	if (l == r) {
		tree[idx] = arr[l] % m;
		return;
	}

	int mid = (l + r) >> 1;
	build(2 * idx, l, mid);
	build(2 * idx + 1, mid + 1, r);

	if (tree[2 * idx] == -1) tree[idx] = tree[2 * idx + 1];
	else if (tree[2 * idx + 1] == -1) tree[idx] = tree[2 * idx];
	else tree[idx] = (tree[2 * idx] * tree[2 * idx + 1]) % m;
}

int query(int ql, int qr, int l, int r, int idx) {
	if (r < ql || l > qr) return -1;
	if (l >= ql && r <= qr) return tree[idx];

	int mid = (l + r) >> 1;
	int left = query(ql, qr, l, mid, 2 * idx);
	int right = query(ql, qr, mid + 1, r, 2 * idx + 1);

	if (left == -1) return right;
	if (right == -1) return left;
	return (left * right) % m;
}

void solve() {
	cin >> n >> m;
	for (int r = 1; r <= n; r++) cin >> arr[r];
	string str; cin >> str;
	for (int r = 1; r <= 4 * n; r++) tree[r] = -1;

	int l = 1, r = n;
	build(1, 1, n);
	for (int c : str) {
		cout << query(l, r, 1, n, 1) << " ";
		if (c == 'L') l++;
		else r--;
	}
	cout << endl;
}

int32_t main() {
	int t; cin >> t;
	while(t--) solve();
	return 0;
}
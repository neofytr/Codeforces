#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MOD (int)(1e9 + 9)
#define MAX (int)(1e5)

int tree[4 * MAX + 1];

int query(int ql, int qr, int l, int r, int idx) {
	if (qr < l || ql > r) return 0;
	if (l >= ql && r <= qr) return tree[idx];

	int m = (l + r) >> 1;
	int left = query(ql, qr, l, m, idx << 1);
	int right = query(ql, qr, m + 1, r, (idx << 1) | 1);
	return (left + right) % MOD;
}

void update(int i, int x, int l, int r, int idx) {
	if (i < l || i > r) return;
	if (l == r) {
		tree[idx] = x;
		return;	
	}

	int m = (l + r) >> 1;
	if (i <= m) update(i, x, l, m, idx << 1);
	else update(i, x, m + 1, r, (idx << 1) | 1);
	tree[idx] = (tree[idx << 1] + tree[(idx << 1) | 1]) % MOD;
}

int32_t main() {
	int n; cin >> n;
	vector<int> arr(n + 1);
	for (int r = 1; r <= n; r++) cin >> arr[r];

	int shift = 0;
	set<int> s;
	for (int r = 1; r <= n; r++) {
 		shift += arr[r];
 		s.insert(arr[r] - shift);
	}

 	int sz = s.size();
 	vector<int> A(sz + 1);
 	int i = 1;
 	for (int elt : s) A[i++] = elt;

 	shift = arr[1];
 	int zro = lower_bound(A.begin() + 1, A.end(), 0) - A.begin();
 	update(zro, 1, 1, sz, 1);

 	for (int r = 2; r <= n; r++) {
 		int x = 0;
 		int idx = lower_bound(A.begin() + 1, A.end(), -shift) - A.begin();
 		if (idx <= sz) 
 			x = query(idx, sz, 1, sz, 1);
 		shift += arr[r];
 		idx = lower_bound(A.begin() + 1, A.end(), arr[r] - shift) - A.begin();
 		int y = query(idx, idx, 1, sz, 1);
 		update(idx, (x + y) % MOD, 1, sz, 1);
 	}

 	int idx = lower_bound(A.begin() + 1, A.end(), -shift) - A.begin();
 	if (idx > sz) {
 		cout << 0 << endl;
 		return 0;
 	}
 	cout << query(idx, sz, 1, sz, 1) % MOD << endl;
 	return 0;
}
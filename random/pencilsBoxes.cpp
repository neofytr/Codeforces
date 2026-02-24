#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MAX (int)(5 * 1e5)

int tree[4 * MAX + 1];
int arr[MAX + 1];
int dp[MAX + 1];

void update(int i, int val, int l = 0, int r = MAX, int idx = 1) {
	if (l == r) {
		tree[idx] = val;
		return;
	}

	int m = (l + r) >> 1;
	if (i <= m) update(i, val, l, m, idx << 1);
	else update(i, val, m + 1, r, (idx << 1) | 1);
	tree[idx] = tree[idx << 1] + tree[(idx << 1) | 1];
}

int query(int ql, int qr, int l = 0, int r = MAX, int idx = 1) {
	if (qr < l || ql > r) return 0;
	if (l >= ql && r <= qr) return tree[idx];

	int m = (l + r) >> 1;
	return query(ql, qr, l, m, idx << 1) + query(ql, qr, m + 1, r, (idx << 1) | 1);
}

int32_t main() {
	int n, k, d; cin >> n >> k >> d;
	for (int r = 1; r <= n; r++) cin >> arr[r];

	sort(arr + 1, arr + n + 1);
	for (int i = 1; i <= n; i++)
		cout << arr[i] << " ";
	cout << endl;
	dp[0] = 1, update(0, dp[0]);
	for (int i = 1; i <= n; i++) {
		int left = 1;
		int right = n;
		while (right != left + 1) {
			int mid = left + (right - left) / 2;
			if (arr[mid] < arr[i] - d) left = mid;
			else right = mid;
		}

		cout << left << " " << i - k + 1 << endl;
		if (left <= i - k + 1) dp[i] = query(left - 1, i - k);
		update(i, dp[i]);
	}

	cout << (dp[n] ? "YES" : "NO") << endl;
	return 0;
}
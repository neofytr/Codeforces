#include <bits/stdc++.h>
using namespace std;

#define int long long

int cnt = 0;
void merge(int l, int r, vector<int> &arr) {
	if (l == r) return;

	int sz = r - l + 1;
	merge(l, l + sz / 2 - 1, arr);
	merge(l + sz / 2, r, arr);

	vector<int> tmp(sz + 1);
	int i = l, j = l + sz / 2, k = 1;
	while (i <= l + sz / 2 - 1 && j <= r)
		if (arr[i] < arr[j]) tmp[k++] = arr[i++];
		else cnt += ((l + sz / 2) - i), tmp[k++] = arr[j++];

	while (i <= l + sz / 2 - 1)
		tmp[k++] = arr[i++];
	while (j <= r)
		tmp[k++] = arr[j++];

	for (int q = l; q <= r; q++)
		arr[q] = tmp[q - l + 1];
}

void solve() {
	int n;
	cin >> n;

	cnt = 0;
	vector<int> arr(n + 1);
	for (int r = 1; r <= n; r++) cin >> arr[r];

	merge(1, n, arr);
	cout << cnt << endl;
}

int32_t main() {
	int t;
	cin >> t;

	while (t--) solve();
	return 0;
}
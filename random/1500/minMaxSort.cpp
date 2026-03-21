#include <bits/stdc++.h>
using namespace std;

#define int long long

void mergeSort(int l, int r, vector<int> &arr, vector<int> &invleft, vector<int> &invright, int &inv) {
	if (l == r) return;
	int m = (l + r) >> 1;
	mergeSort(l, m, arr, invleft, invright, inv), mergeSort(m + 1, r, arr, invleft, invright, inv);
	vector<int> tmp(r - l + 1 + 1);

	int i = l, j = m + 1, k = 1;
	while (i <= m && j <= r)
		if (arr[i] < arr[j]) tmp[k++] = arr[i++];
		else inv += (m - i + 1), invleft[j] += (m - i + 1), invright[i] += 1, invright[m + 1] -= 1, tmp[k++] = arr[j++];

	while (i <= m) tmp[k++] = arr[i++];
	while (j <= r) tmp[k++] = arr[j++];

	for (int g = 1; g <= r - l + 1; g++)
		arr[l + g - 1] = tmp[g];
}

void solve() {
	int n; cin >> n;
	vector<int> p(n + 1), q(n + 1), g(n + 1), invleft(n + 2, 0), invright(n + 2, 0);
	for (int i = 1; i <= n; i++) cin >> p[i], q[i] = p[i], g[p[i]] = i;

	int inv = 0;
	mergeSort(1, n, q, invleft, invright, inv);
	for (int i = 1; i <= n; i++)
		invright[i] += invright[i - 1];


	int cnt = 0;
	int l = 1, r = n;
	while (l <= r) {
		if (!inv) {
			cout << cnt << endl;
			return;
		}

		int left = g[l], right = g[r];
		inv -= (invright[left] + invleft[left]);
		inv -= (invleft[right] + invright[left]);
		if (left > right) inv++;
		cout << inv << endl;
		l++, r--;
	}
}

int32_t main() {
	int t; cin >> t;
	while (t--) solve();
	return 0;
}
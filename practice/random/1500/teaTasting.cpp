#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve() {
	int n; cin >> n;
	vector<int> a(n + 1), b(n + 1);
	for (int r = 1; r <= n; r++) cin >> a[r];
	for (int r = 1; r <= n; r++) cin >> b[r];

	vector<int> mult(n + 2, 0), p(n + 1, 0), lt(n + 2, 0);
	for (int r = 1; r <= n; r++) p[r] += p[r - 1] + b[r];

	for (int r = 1; r <= n; r++) {
		int left = r, right = n;
		int res = -1;
		while (left <= right) {
			int mid = left + (right - left) / 2;
			if (p[mid] - p[r - 1] <= a[r]) left = mid + 1, res = max(res, mid);
			else right = mid - 1;
		}

		if (res == -1) {
			// everything > a[r]
			lt[r] += a[r];
			continue;
		}

		mult[r] += 1, mult[res + 1] -= 1;
		lt[res + 1] += (a[r] - (p[res] - p[r - 1]));
	}

	for (int r = 1; r <= n; r++) mult[r] += mult[r - 1];
	for (int r = 1; r <= n; r++) 
		cout << b[r] * mult[r] + lt[r] << " ";
	cout << endl;
}

int32_t main() {
	int t; cin >> t;
	while (t--) solve();
	return 0;
}
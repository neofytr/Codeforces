#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main() {
	int n, k; cin >> n >> k;
	vector<int> a(n + 1), b(n + 1);
	for (int r = 1; r <= n; r++) cin >> a[r];
	for (int r = 1; r <= n; r++) cin >> b[r];

	int maxi = LLONG_MIN;
	for (int r = 1; r <= n; r++)
		maxi = max(maxi, (b[r] + k) / a[r]);

	auto can = [&a, &b, &n, &k] (int x) {
		int extra = 0;
		for (int r = 1; r <= n; r++) {
			extra += max(0ll, a[r] * x - b[r]);
			if (extra > k) return false;
		}
		return true;
	};

	int left = 0;
	int right = maxi + 1;
	while (right != left + 1) {
		int mid = left + ((right - left) >> 1);
		if (can(mid)) left = mid;
		else right = mid;
	}

	cout << left << endl;
	return 0;
}
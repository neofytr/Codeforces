#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main() {
	int n, m; cin >> n >> m;
	vector<int> a(n + 1), b(m + 1);
	for (int r = 1; r <= n; r++) cin >> a[r];
	for (int r = 1; r <= m; r++) cin >> b[r];

	sort(a.begin() + 1, a.end()), sort(b.begin() + 1, b.end());

	bool c = true;
	for (int i = 1; i <= n; i++) {
		auto itr = lower_bound(b.begin() + 1, b.end(), a[i]);
		if (itr == b.end() || *itr > a[i]) {
			c = false;
			break;
		}
	}

	if (c) {
		cout << 0 << endl;
		return 0;
	}
	
	int left = 0;
	int right = 1e13;

	auto can = [&a, &b, &n, &m](int x) {
		vector<int> y(n + 3, 0);
		for (int i = 1; i <= m; i++) {
			int l = b[i] - x, r = b[i] + x;
			int j = lower_bound(a.begin() + 1, a.end(), l) - a.begin();
			int k = upper_bound(a.begin() + 1, a.end(), r) - a.begin() - 1;

			if (j <= k)
				y[j] += 1, y[k + 1] -= 1;
		}

		for (int r = 1; r <= n; r++) y[r] += y[r - 1];
		for (int r = 1; r <= n; r++)
			if (!y[r]) return false;
		return true;
	};

	while (right != left + 1) {
		int mid = left + ((right - left) >> 1);
		if (can(mid)) right = mid;
		else left = mid;
	}

	cout << right << endl;
	return 0;
}
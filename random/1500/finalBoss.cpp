#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve() {
	int h, n; cin >> h >> n;
	vector<int> a(n + 1), c(n + 1);
	int mini = LLONG_MAX, cmini;
	for (int r = 1; r <= n; r++) cin >> a[r], mini = min(mini, a[r]);
	for (int r = 1; r <= n; r++) {
		cin >> c[r];
		if (a[r] == mini)	
			cmini = c[r];
	}

	auto can = [&a, &c, &n, &h] (int x) -> bool {
		int t = 0;
		for (int i = 1; i <= n; i++) {
			t += ((x - 1) / c[i] + 1) * a[i];
			if (t >= h) return true;
		}
		return false;
	};

	int left = 0;
	int right = (h / mini) * cmini + 1;
	while (right != left + 1) {
		int mid = left + ((right - left) >> 1);
		if (can(mid)) right = mid;
		else left = mid;
	}

	cout << right << endl;
}

int32_t main() {
	int t; cin >> t;
	while (t--) solve();
	return 0;
}
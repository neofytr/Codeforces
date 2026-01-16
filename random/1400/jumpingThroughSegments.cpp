#include <bits/stdc++.h>
using namespace std;

#define int long long 

void solve() {
	int n;
	cin >> n;

	vector<pair<int, int>> seg(n + 1);
	for (int r = 1; r <= n; r++) cin >> seg[r].first >> seg[r].second;

	// It's possible to complete with 0 iff all the segments have 0
	bool psbl = true;
	for (int i = 1; i <= n; i++) {
		int l = seg[i].first, r = seg[i].second;
		if (l) {
			psbl = false;
			break;
		}
	}

	if (psbl) {
		cout << 0 << endl;
		return;
	}

	int left = 0;
	int right = 1e9 + 1;

	auto can = [&](int x) -> bool {
		int L = 0, R = 0;
		for (int i = 1; i <= n; i++) {
			int l = seg[i].first, r = seg[i].second;
			int ldash = max(L - x, 0ll), rdash = R + x;
			if (r < ldash || l > rdash)
				return false;
			L = max(ldash, l), R = min(rdash, r);
		}
		return true;
	};

	while (right != left + 1) {
		int mid = left + (right - left) / 2;
		if (can(mid))
			right = mid;
		else 
			left = mid;
	}

	cout << right << endl;
}

int32_t main() {
	int t;
	cin >> t;

	while (t--) {
		solve();
	}
	return 0;
}
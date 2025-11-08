#include <bits/stdc++.h>
using namespace std;

#define int long long 

void solve() {
	int n;
	cin >> n;

	bool allZero = true;
	vector<pair<int, int>> segments(n);
	for (auto &[l, r] : segments) {
		cin >> l >> r;
		if (l)
			allZero = false;
	}

	if (allZero) {
		cout << 0 << endl;
		return;
	}

	// [l2, r2] [b, a]

	auto can = [&](int k) -> bool {
		// can it be done with step being atmost k?

		int alpha = 0, beta = 0;
		for (auto &[l, r] : segments) {
		 	alpha += k;
		 	beta -= k;

		 	if (r < beta || alpha < l)
		 		return false;

		 	alpha = min(r, alpha);
		 	beta = max(l, beta);
		}

		return true;
	};

	int left = 0; // wont work
	int right = 1e9 + 1; // will definitely work

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

	while(t--) {
		solve();
	}
	return 0;
}
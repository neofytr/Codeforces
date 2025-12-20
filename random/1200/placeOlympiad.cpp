#include <bits/stdc++.h>
using namespace std;

#define int long long 

void solve() {
	int n, m, k;
	cin >> n >> m >> k;

	auto can = [&](int x) -> bool {
		// can all the benches be of length <= x
		int q = m / (x + 1);
		int r = m % (x + 1);
		int one = q * x + r;
		return one * n >= k;
	};

	int left = 0;
	int right = max(n, m) + 1;

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
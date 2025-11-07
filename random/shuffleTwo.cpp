#include <bits/stdc++.h>
using namespace std;

#define int long long 

void solve() {
	int n, x, m;
	cin >> n >> x >> m;

	int l, r;

	int left = 0, right = 0;
	while(m--) {
		cin >> l >> r;
		if (!left && x >= l && x <= r)
			left = l, right = r;
		if (left && r >= left && l <= right)
			left = min(left, l), right = max(right, r);
	}

	cout << right - left + 1 << endl;
}

int32_t main() {
	int t;
	cin >> t;

	while(t--) {
		solve();
	}
	return 0;
}
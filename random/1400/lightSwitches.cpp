#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve() {
	int n, k; cin >> n >> k;
	vector<int> arr(n + 1);

	int maxi = LLONG_MIN;
	int left = 0, right = k - 1;
	for (int r = 1; r <= n; r++) cin >> arr[r], maxi = max(maxi, arr[r]);
	for (int i = 1; i <= n; i++) {
		int r = (maxi - arr[i] + (k - 1)) % (2 * k);
		int lft = (k - 1) - r;
		int rght = (2 * k - 2 - r);
		left = max(left, lft);
		right = min(right, rght);
	}

	if (left > right) {
		cout << -1 << endl;
		return;
	}

	cout << maxi + left << endl;
}

int32_t main() {
	int t; cin >> t;
	while (t--) solve();
	return 0;
}
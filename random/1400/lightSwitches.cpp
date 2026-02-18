#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve() {
	int n, k; cin >> n >> k;
	vector<int> arr(n + 1);
	for (int r = 1; r <= n; r++) cin >> arr[r];

	sort(arr.begin() + 1, arr.end());
	for (int r = 1; r <= n - 1; r++) {
		int left = (k + arr[r + 1] - arr[r]) / (2 * k);
		int right = (k - 1 + arr[r + 1] - arr[r]) / (2 * k);
		if (left > right) {
			cout << -1 << endl;
			return;
		}
	}

	int mini = LLONG_MAX;
	int m = (k + arr[n] - arr[n - 1]) / (2 * k);
	for (int y = 0; y <= k - 1; y++) {
		int x = arr[n - 1] + 2 * k * m + y - arr[n];
		if (x >= 0 && x <= k - 1) mini = min(mini, arr[n] + x);
	}

	cout << mini << endl;
}

int32_t main() {
	int t; cin >> t;
	while (t--) solve();
	return 0;
}
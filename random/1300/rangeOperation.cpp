#include <bits/stdc++.h>
using namespace std;

#define int long long 

void solve() {
	int n;
	cin >> n;

	vector<int> arr(n + 1);
	for (int r = 1; r <= n; r++) cin >> arr[r];

	// Find the subarray arr[l, r], where 1 <= l <= r <= n such that
	// (l + r)(r - l + 1) - sum[l, r] is maximized
	// (r2 - l2 + l + r - p[r] + p[l - 1]) is maximized
	// (-l2 + l + p[l - 1]) + (r2 + r - p[r]) is maximized

	vector<int> p(n + 1, 0);
	for (int r = 1; r <= n; r++) p[r] += p[r - 1] + arr[r];

	int maxi = LLONG_MIN;
	int prevm = -1 * 1 * 1 + 1 + p[1 - 1];
	for (int r = 1; r <= n; r++)
		maxi = max(maxi, prevm + r + r * r - p[r]), prevm = max(prevm, -1 * (r + 1) * (r + 1) + (r + 1) + p[r]);

	if (maxi >= 0) 
		cout << p[n] + maxi << endl;
	else 
		cout << p[n] << endl;
}

int32_t main() {
	int t;
	cin >> t;

	while (t--) {
		solve();
	}
	return 0;
}
#include <bits/stdc++.h>
using namespace std;

#define int long long 
#define MAX (int)(2 * 1e5)

void solve() {
	int n;
	cin >> n;

	// dp[r] is the maximum number of balls we can remove in [1, r] for 1 <= r <= n
	vector<int> arr(n + 1), dp(n + 1, 0), maxi(MAX + 1, LLONG_MIN);
	for (int r = 1; r <= n; r++) cin >> arr[r];
	for (int r = 1; r <= n; r++) {
		// if we've seen some arr[r] before, we can remove all the elements
		// between that and r, or we can choose to not remove the current element
		// altogether

		// we choose the best arr[r] that comes before to remove
		// for that we keep the maxi array
		if (maxi[arr[r]] == LLONG_MIN)
			dp[r] = dp[r - 1];
		else 
			dp[r] = max(dp[r - 1], maxi[arr[r]] + r);
		maxi[arr[r]] = max(maxi[arr[r]], dp[r - 1] - r + 1);
	}
	cout << dp[n] << endl;
}

int32_t main() {
	int t;
	cin >> t;

	while(t--) {
		solve();
	}
	return 0;
}
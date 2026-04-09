#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MOD (998244353)

void solve() {
	int n;
	cin >> n;

	vector<int> a(n + 1), b(n + 1);
	for (int r = 1; r <= n; r++) cin >> a[r];
	for (int r = 1; r <= n; r++) cin >> b[r];

	// dp[r][0] is the number of good subsets of the subarray [1, r]
	// that doesn't include the rth index
	// dp[r][1] is the number of good subsets of the subarray [1, r]
	// that includes the rth index
	vector<vector<int>> dp(n + 1, vector<int>(2, 0));

	dp[1][0] = 1, dp[1][1] = 1; 
	for (int r = 2; r <= n; r++) {
		if (a[r] >= a[r - 1] && b[r] >= b[r - 1]) 
			dp[r][0] = (dp[r][0] + dp[r - 1][0]) % MOD, dp[r][1] = (dp[r][1] + dp[r - 1][1]) % MOD;
		if (b[r] >= a[r - 1] && a[r] >= b[r - 1])
			dp[r][1] = (dp[r][1] + dp[r - 1][0]) % MOD, dp[r][0] = (dp[r][0] + dp[r - 1][1]) % MOD;
	}

	cout << (dp[n][0] + dp[n][1]) % MOD << endl;
}

int32_t main() {
	int t;
	cin >> t;

	while (t--) {
		solve();
	}
	return 0;
}
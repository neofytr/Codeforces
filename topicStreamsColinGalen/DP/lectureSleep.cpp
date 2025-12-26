#include <bits/stdc++.h>
using namespace std;

#define int long long 
#define MAXN 1e5

int32_t main() {
	int n, k;
	cin >> n >> k;

	vector<int> a(n + 1), t(n + 1);
	for (int r = 1; r <= n; r++) cin >> a[r];
	for (int r = 1; r <= n; r++) cin >> t[r];

	vector<int> p(n + 1, 0);
	for (int r = 1; r <= n; r++) p[r] += p[r - 1] + a[r];

	vector<vector<int>> dp(n + 1, vector<int>(2, LLONG_MIN));


	dp[0][0] = dp[0][1] = 0;
	dp[1][0] = (t[1] ? a[1] : 0);
	if (k == 1) dp[1][1] = a[1];
	for (int r = 2; r <= n; r++) {
		dp[r][0] = dp[r - 1][0] + (t[r] ? a[r] : 0);
		if (r >= k)
			dp[r][1] = max(dp[r - 1][1] + (t[r] ? a[r] : 0), p[r] - p[r - k] + dp[r - k][0]);
	}

	cout << dp[n][1] << endl;
}
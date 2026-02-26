#include <bits/stdc++.h>
using namespace std;

#define int long long
#define INF (int)(1e18)

void solve() {
	int n; cin >> n;
	vector<int> a(n + 1);
	for (int r = 1; r <= n; r++) cin >> a[r];

	if (n == 1) {
		cout << a[1] << endl;
		return;
	}

	// dp[i][0] is the minimum cost to kill the first i monsters with the ith monster
	// killed by A
	// dp[i][1] is the minimum cost to kill the first i monsters with the ith monster
	// killed by B
	vector<vector<int>> dp(n + 1, vector<int>(2));
	dp[1][0] = a[1];
	dp[1][1] = INF;
	dp[2][0] = a[1] + a[2];
	dp[2][1] = a[1];

	for (int i = 3; i <= n; i++) {
		dp[i][1] = min(dp[i - 1][0], dp[i - 2][0]);
		dp[i][0] = min(dp[i - 1][1] + a[i], dp[i - 2][1] + a[i - 1] + a[i]);
	}
	cout << min(dp[n][0], dp[n][1]) << endl;
}

int32_t main() {
	int t; cin >> t;
	while (t--) solve();
	return 0;
}
#include <bits/stdc++.h>
using namespace std;
 
#define int long long
 
void solve() {
	int n; cin >> n;
	vector<int> arr(n + 1);
	for (int r = 1; r <= n; r++) cin >> arr[r];
 
	vector<vector<int>> dp(n + 1, vector<int>(2, 0));
	dp[1][0] = dp[1][1] = 0;
	for (int r = 2; r <= n; r++) {
		dp[r][0] = min(dp[r - 1][1] + (arr[r] == arr[n - r + 2]) + (arr[n - r + 1] == arr[r - 1]), dp[r - 1][0] + (arr[r] == arr[r - 1]) + (arr[n - r + 1] == arr[n - r + 2]));
		dp[r][1] = min(dp[r - 1][1] + (arr[n - r + 1] == arr[n - r + 2]) + (arr[r] == arr[r - 1]), dp[r - 1][0] + (arr[n - r + 1] == arr[r - 1]) + (arr[r] == arr[n - r + 2]));
	}
 
	cout << min(dp[n][0], dp[n][1]) / 2 << endl;
}
 
int32_t main() {
	int t; cin >> t;
	while (t--) solve();
	return 0;
}
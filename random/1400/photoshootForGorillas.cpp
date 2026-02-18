#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve() {
	int n, m, k; cin >> n >> m >> k;
	int w; cin >> w;

	vector<int> arr(w);
	for (int r = 0; r < w; r++) cin >> arr[r];

	vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
	for (int r = 1; r <= n - k + 1; r++)
		for (int c = 1; c <= m - k + 1; c++) {
			dp[r][c] += 1;
			dp[r + k][c] -= 1;
			dp[r][c + k] -= 1;
			dp[r + k][c + k] += 1;
		}

	for (int r = 1; r <= n; r++)
		for (int c = 1; c <= m; c++) 
			dp[r][c] += dp[r - 1][c] + dp[r][c - 1] - dp[r - 1][c - 1];
		

	vector<int> p;
	for (int r = 1; r <= n; r++)
		for (int c = 1; c <= m; c++)
			p.push_back(dp[r][c]);

	sort(p.rbegin(), p.rend());
	sort(arr.rbegin(), arr.rend());
	int res = 0;
	for (int r = 0; r < w; r++) res += arr[r] * p[r];
	cout << res << endl;
}

int32_t main() {
	int t; cin >> t;
	while (t--) solve();
	return 0;
}
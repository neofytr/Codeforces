#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve() {
	string s;
	cin >> s;

	int n = (int)s.length();
	vector<int> v(n + 1);
	for (int r = 1; r <= n; r++)
		if (s[r - 1] == '?') v[r] = 2;
		else v[r] = s[r - 1] - '0';

	vector<vector<int>> dp(n + 1, vector<int>(2, 0));
	if (v[1] == 1) dp[1][1] = 1;
	if (v[1] == 0) dp[1][0] = 1;
	if (v[1] == 2) dp[1][0] = dp[1][1] = 1;

	for (int r = 2; r <= n; r++)
		if (!v[r]) dp[r][0] = dp[r - 1][1] + 1;
		else if (v[r] == 1) dp[r][1] = dp[r - 1][0] + 1;
		else {
			dp[r][0] = dp[r - 1][1] + 1;
			dp[r][1] = dp[r - 1][0] + 1;
		}
		
	int res = 0;
	for (int r = 1; r <= n; r++)
		res += max(dp[r][0], dp[r][1]);
	cout << res << endl;
}

int32_t main() {
	int t;
	cin >> t;

	while (t--) solve();
	return 0;
}
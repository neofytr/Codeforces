#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve() {
	int n, h; cin >> n >> h;
	vector<int> a(n + 1);
	for (int i = 1; i <= n; i++) cin >> a[i];

	sort(a.begin() + 1, a.end());
	vector<vector<vector<int>>> dp(n + 1, vector<vector<int>>(3, vector<int>(2, -1)));
	dp[0][0][0] = h;
	dp[0][0][1] = h * 3;
	dp[0][1][0] = h * 2;
	dp[0][1][1] = h * 6;
	dp[0][2][0] = h * 4;
	dp[0][2][1] = h * 12;

	for (int i = 1; i <= n; i++) {
		for (int g = 0; g <= 2; g++)
			for (int b = 0; b <= 1; b++)
				if (dp[i - 1][g][b] > a[i]) 
					dp[i][g][b] = dp[i - 1][g][b] + a[i] / 2;

		for (int g = 0; g <= 2; g++)
			for (int b = 0; b <= 1; b++) {
				if (g < 2) dp[i][g + 1][b] = max(dp[i][g + 1][b], dp[i][g][b] * 2);
				if (b < 1) dp[i][g][b + 1] = max(dp[i][g][b + 1], dp[i][g][b] * 3);
				if (g < 2 && b < 1) dp[i][g + 1][b + 1] = max(dp[i][g + 1][b + 1], dp[i][g][b] * 6);
			}

		bool yes = false;
		for (int g = 0; g <= 2; g++)
			for (int b = 0; b <= 1; b++)
				if (dp[i][g][b] > 0) {
					yes = true;
					break;
				}

		if (!yes) {
			cout << i - 1 << endl;
			return;
		}
	}

	// for (int i = 0; i <= n; i++) {
	// 	cout << i << endl;
	// 	for (int g = 0; g <= 2; g++) {
	// 		for (int b = 0; b <= 1; b++)
	// 			cout << dp[i][g][b] << " ";
	// 		cout << endl;
	// 	}
	// }
	cout << n << endl;
}

int32_t main() {
	int t; cin >> t;
	while (t--) solve();
	return 0;
}
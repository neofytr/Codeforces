#include <bits/stdc++.h>
using namespace std;

#define int long long 
#define MAX_N (int)(1e3)
#define MAX_W (int)(1e3)

int dp[MAX_N + 1][64][MAX_W + 1];

int32_t main() {
	int n, W;
	cin >> n >> W;

	vector<int> w(n + 1), v(n + 1), k(n + 1);
	for (int r = 1; r <= n; r++) cin >> w[r] >> v[r] >> k[r];

	for (int r = 0; r <= n; r++)
		for (int b = 0; b <= 63; b++)
			for (int x = 0; x <= W; x++)
				dp[r][b][x] = LLONG_MIN;

	dp[0][0][0] = 0;
	for (int r = 1; r <= n; r++) {
		for (int x = 0; x <= W; x++) {
			dp[r][0][x] = dp[r - 1][0][x];
			if (x >= w[r] && (k[r] & 1)) dp[r][0][x] = max(dp[r][0][x], dp[r - 1][63][x - w[r]] + v[r]);
		}

		for (int b = 1; b <= 63; b++)
			for (int x = 0; x <= W; x++) {
				dp[r][b][x] = max({dp[r - 1][63][x], dp[r][b - 1][x]});
				if ((1ll << b) & k[r]) {
					int wt = w[r] * (1ll << b);
					int val = v[r] * (1ll << b);
					if (x >= wt) dp[r][b][x] = max(dp[r][b][x], dp[r][b - 1][x - wt] + val);
				}
			}
	}
	return 0;
}
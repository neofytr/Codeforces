#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MAX_N (int)(1e3)
#define MAX_W (int)(1e4)
#define INF (int)(1e15)

int dp[MAX_N + 1][MAX_W + 1];
int w[MAX_N + 1], s[MAX_N + 1], v[MAX_N + 1];
pair<int, int> cpy[MAX_N + 1];

int32_t main() {
	int n;
	cin >> n;

	for (int r = 1; r <= n; r++) cin >> w[r] >> s[r] >> v[r], cpy[r] = {s[r], r};
	sort(cpy + 1, cpy + n + 1);

	for (int r = 0; r <= n; r++)
		for (int x = 0; x <= MAX_W; x++)
			dp[r][x] = -INF;

	dp[0][0] = 0;
	for (int r = 1; r <= n; r++) {
		dp[r][0] = 0;
		for (int x = 1; x <= MAX_W; x++) {
			dp[r][x] = dp[r - 1][x];
			if (x >= w[r] && x - w[r] <= s[r]) dp[r][x] = max(dp[r][x], dp[r - 1][x - w[r]] + v[r]);
		}
	}

	int maxi = LLONG_MIN;
	for (int x = 0; x <= MAX_W; x++)
		maxi = max(maxi, dp[n][x]);
	cout << maxi << endl;
	return 0;
}
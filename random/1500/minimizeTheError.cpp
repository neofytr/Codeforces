#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MAX (int)(1e3)

int n, k1, k2;
int a[MAX + 1], b[MAX + 1];
int dp[10][MAX + 1][MAX + 1];

int32_t main() {
	cin >> n >> k1 >> k2;
	for (int i = 1; i <= n; i++) cin >> a[i];
	for (int i = 1; i <= n; i++) cin >> b[i];

	for (int i = 1; i <= n; i++)
		for (int j = 0; j <= k1; j++)
			for (int k = 0; k <= k2; k++) {
				dp[i][j][k] = dp[i - 1][j][k] + (a[i] - b[i]) * (a[i] - b[i]);

				if (j >= 1)
					dp[i][j][k] = min({dp[i][j][k], 
					dp[i - 1][j - 1][k] + (a[i] + 1 - b[i]) * (a[i] + 1 - b[i]),
					dp[i - 1][j - 1][k] + (a[i] - 1 - b[i]) * (a[i] - 1 - b[i])});

				if (k >= 1)
					dp[i][j][k] = min({dp[i][j][k], 
					dp[i - 1][j][k - 1] + (a[i] + 1 - b[i]) * (a[i] + 1 - b[i]),
					dp[i - 1][j][k - 1] + (a[i] - 1 - b[i]) * (a[i] - 1 - b[i])});

				if (j >= 1 && k >= 1)
					dp[i][j][k] = min({dp[i][j][k], 
					dp[i - 1][j - 1][k - 1] + (a[i] - b[i]) * (a[i] - b[i]),
					dp[i - 1][j - 1][k - 1] + (a[i] - 2 - b[i]) * (a[i] - 2 - b[i]),
					dp[i - 1][j - 1][k - 1] + (a[i] + 2 - b[i]) * (a[i]) + 2 - b[i]});
			}

	for (int r = 1; r <= n; r++)
		for (int j = 0; j <= k1; j++)
			for (int k = 0; k <= k2; k++) {
				cout << r << " " << j << " " << k << " " << dp[r][j][k] << endl;
			}

	cout << dp[n][k1][k2] << endl;
	return 0;	
}
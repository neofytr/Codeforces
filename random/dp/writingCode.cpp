#include <bits/stdc++.h>
using namespace std;

#define int long long 
#define MAX (int)(5 * 1e2)

int dp[MAX + 1][MAX + 1][MAX + 1];
int arr[MAX + 1];

int32_t main() {
	int n, m, b, mod;
	cin >> n >> m >> b >> mod;

	for (int r = 1; r <= n; r++) cin >> arr[r];

	dp[0][0][0] = 1;
	for (int i = 1; i <= n; i++) {
		for (int k = 0; k <= b; k++)
			dp[i][0][k] = 1;

		for (int j = 1; j <= m; j++) {
			dp[i][j][0] = 0;
			for (int k = 1; k <= b; k++)
				for (int v = 0; v <= j; v++)
					dp[i][j][k] = (dp[i][j][k] + (k - arr[i] * v >= 0 ? dp[i - 1][j - v][k - arr[i] * v] : 0)) % mod;
		}
	}

	cout << dp[n][m][b] << endl;
	return 0;
}
#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MOD (int)(1e9 + 7)
#define MAX_N (int)(1e2)
#define MAX_K (int)(1e5)

int arr[MAX_N + 1];
int dp[MAX_N + 1][MAX_K + 1];
int p[MAX_K + 1];
 
int32_t main() {
	int n, k;
	cin >> n >> k;

	for (int r = 1; r <= n; r++) cin >> arr[r];

	for (int i = 0; i <= n; i++)
		for (int j = 0; j <= k; j++)
			dp[i][j] = 0;

	dp[0][0] = 1;
	p[0] = 1;
	for (int i = 1; i <= k; i++)
		p[i] = (p[i - 1] + dp[0][i]) % MOD;

	for (int i = 1; i <= n; i++) {
		dp[i][0] = 1;
		for (int j = 1; j <= k; j++) {
			dp[i][j] = dp[i - 1][j];

			int left = j - min(arr[i], j);
			int right = j - 1;
			
			if (!left) dp[i][j] = (dp[i][j] + p[right]) % MOD;
			else dp[i][j] = (dp[i][j] + p[right] - p[left - 1] + MOD) % MOD;
		}

		p[0] = 1;
		for (int j = 1; j <= k; j++)
			p[j] = (p[i - 1] + dp[i][j]) % MOD;
	}

	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= k; j++)
			cout << i << " " << j << " " << dp[i][j] << endl;

	cout << dp[n][k] << endl;
	return 0;
}
#include <bits/stdc++.h>
using namespace std;

#define int long long 


int32_t main() {
	int n, m, q;
	cin >> n >> m >> q;

	vector<vector<int>> mat(n + 1, vector<int>(m + 1));
	for (int r = 1; r <= n; r++)
		for (int c = 1; c <= m; c++)
			cin >> mat[r][c];

	vector<vector<int>> dp(n + 1, vector<int>(m + 1));
	for (int r = 1; r <= n; r++) {
		dp[r][0] = 0;
		for (int c = 1; c <= m; c++)
			if (!mat[r][c]) dp[r][c] = 0;
			else dp[r][c] = dp[r][c - 1] + 1;
	}

	vector<int> maxi(n + 1, LLONG_MIN);
	for (int r = 1; r <= n; r++)
		for (int c = 1; c <= m; c++)
			maxi[r] = max(maxi[r], dp[r][c]);

	int i, j;
	while (q--) {
		cin >> i >> j;
		mat[i][j] ^= 1;

		dp[i][0] = 0;
		for (int c = 1; c <= m; c++)
			if (!mat[i][c]) dp[i][c] = 0;
			else dp[i][c] = dp[i][c - 1] + 1;

		int k = LLONG_MIN;
		for (int c = 1; c <= m; c++)
			k = max(k, dp[i][c]);
		maxi[i] = k;

		for (int r = 1; r <= n; r++)
			k = max(k, maxi[r]);

		cout << k << endl;
	}
	return 0;
}
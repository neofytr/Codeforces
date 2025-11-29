#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MAX_N (777)
#define MAX_R (int)(7)
#define endl "\n";

int C(int n, int r) {
	if (r > n) return 0;
	int res = 1;
	for (int k = 0; k <= r - 1; k++)
		res = (res * (n - k)) / (k + 1);

	return res;
}

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

   	int n;
    cin >> n;

    // cout << C(n, 5) + C(n, 6) + C(n, 7) << endl;

    vector<vector<int>> dp(MAX_N + 1, vector<int>(MAX_R + 1, 0));
    dp[0][0] = 1;
  	for (int i = 1; i <= MAX_N; i++) {
  		dp[i][0] = 1;
  		for (int j = 1; j <= min(i, MAX_R); j++)
  			if (j <= i - 1)
  				dp[i][j] = dp[i - 1][j - 1] + dp[i - 1][j];
  			else 
  				dp[i][j] = 1;
  	}

    cout << dp[n][5] + dp[n][6] + dp[n][7] << endl;
    return 0;
}

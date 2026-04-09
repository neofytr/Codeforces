#include <bits/stdc++.h>
using namespace std;

#define int long long 
#define getnum(x) (int)(x - '0')

int pw(int base, int exp) {
	int res = 1;
	while (exp) {
		if (exp & 1)
			res = res * base;
		base = base * base;
		exp >>= 1;
	}
	return res;
}

int getlargest(string &num) {
	int n = num.length();

	// dp[r][x] = maximum number we can get in str[r, n - 1] using x digits for 0 <= r <= n - 1, 0 <= x <= 12
	vector<vector<int>> dp(n, vector<int>(13, 0));
	dp[n - 1][0] = 0, dp[n - 1][1] = getnum(num[n - 1]);
	for (int r = n - 2; r >= 0; r--) {
		dp[r][0] = 0;
		for (int x = 1; x <= min(12ll, n - r); x++) 
			// either we choose the current digit or not
			dp[r][x] = max(dp[r + 1][x - 1] + getnum(num[r]) * pw(10, x - 1), dp[r + 1][x]);	
	}

	return dp[0][12];
}

int32_t main() {
	int cnt = 0;
	string line;

	while (cin >> line)
		cnt += getlargest(line);
	cout << cnt << endl;
	return 0;
}
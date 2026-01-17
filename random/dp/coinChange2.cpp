#include <bits/stdc++.h>
using namespace std;

#define int long long 

int32_t main() {
	int n, target;
	cin >> n >> target;

	vector<int> c(n + 1); // all the values are distinct
	for (int r = 1; r <= n; r++) cin >> c[r];
	vector<int> dp(target + 1, 0);

	dp[0] = 1;
	for (int r = 1; r <= n; r++)
		for (int x = c[r]; x <= target; x++)
			dp[x] = (dp[x] + dp[x - c[r]]) % INT_MAX;

	cout << dp[target] << endl;
	return 0;
}
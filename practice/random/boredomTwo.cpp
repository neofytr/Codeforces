#include <bits/stdc++.h>
using namespace std;

#define int long long 
#define MAX (1e5)

int32_t main() {
	int n;
	cin >> n;

	int val;
	unordered_map<int, int> f;
	for (int r = 1; r <= n; r++) cin >> val, f[val]++;

	// dp[r] is the maximum score possible if we use the array elements
	// in the range [1, r] for 1 <= r <= 1e5
	vector<int> dp(MAX + 1, 0);	
	dp[1] = 1 * f[1];
	dp[2] = max(2 * f[2], 1 * f[1]);

	for (int r = 3; r <= MAX; r++)
		// we can either take the current number, or not
		dp[r] = max(dp[r - 2] + r * f[r], dp[r - 1]);

	cout << dp[MAX] << endl;
	return 0;
}
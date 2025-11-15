#include <bits/stdc++.h>
using namespace std;

#define int long long 

int32_t main() {
	int n; 
	cin >> n;

	vector<int> arr(n + 1);
	for (int r = 1; r <= n; r++) cin >> arr[r];

	// dp[r] is the maximum sum possible for any subarray ending at r, for 1 <= r <= n
	vector<int> dp(n + 1, 0);
	
	dp[1] = arr[1];
	int ans = dp[1];
	for (int r = 2; r <= n; r++)
		dp[r] = max(dp[r - 1] + arr[r], arr[r]), ans = max(ans, dp[r]);

	cout << max(ans, 0LL) << endl; // if picking an empty subarray is allowed
	return 0;
}
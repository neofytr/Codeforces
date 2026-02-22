#include <bits/stdc++.h>
using namespace std;

#define int long long
#define INF (int)(1e16)

int32_t main() {
	int n, c; cin >> n >> c;
	vector<int> arr(n + 1);
	for (int r = 1; r <= n; r++) cin >> arr[r];

	vector<int> dp(n + 1);
	dp[0] = 0;
	for (int i = 1; i <= n; i++) dp[i] = INF;
	for (int i = 1; i <= n; i++) 
		for (int j = i; j >= 1; j--)
			dp[i] = min(dp[i], dp[j - 1] + (arr[j] - arr[i]) * (arr[j] - arr[i]) + c);
	

	cout << dp[n] << endl;
	return 0;
}
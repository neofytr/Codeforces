#include <bits/stdc++.h>
using namespace std;

#define int long long 
#define dist(a, k) (abs(arr[a] - keys[k]) + abs(keys[k] - p))

int32_t main() {
	int n, k, p;
	cin >> n >> k >> p;

	vector<int> arr(n + 1);
	for (int r = 1; r <= n; r++) cin >> arr[r];

	vector<int> keys(k + 1);
	for (int r = 1; r <= k; r++) cin >> keys[r];

	sort(arr.begin() + 1, arr.end());
	sort(keys.begin() + 1, keys.end());

	// If we place a person arr[r] at some keys[s], then it is 
	// not optimal for person arr[r + 1] to be placed at keys[j] for j < s

	// dp[r][s] is the minimum time taken by people arr[1, r] to reach 
	// the office using keys[1, s]
	vector<vector<int>> dp(n + 1, vector<int>(k + 1, LLONG_MAX));

	for (int s = 1; s <= k; s++)
		dp[1][s] = min(dp[1][s - 1], dist(1, s));
	for (int r = 2; r <= n; r++)
		for (int s = 1; s <= k; s++)
			if (s >= r)
				dp[r][s] = min(max(dist(r, s), dp[r - 1][s - 1]), dp[r][s - 1]);
	

	cout << dp[n][k] << endl;
}
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
	sort(keys.begin() + 1, keys.end())
	vector<vector<int>> dp(n + 1, vector<int>(k + 1, LLONG_MAX));
	for (int s = 1; s <= k; s++)
		dp[1][s] = min(dp[1][s - 1], dist(1, s));

	for (int r = 2; r <= n; r++)
		for (int s = 1; s <= k; s++)
			if (s >= r)
				for (int m = r - 1; m <= s - 1; m++)
					dp[r][s] = min(dp[r][s], dp[r - 1][m] + dist(r, m + 1));

	cout << dp[n][k] << endl;
}
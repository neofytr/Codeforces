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

	// dp[r][s] is the minimum time needed for all of the people
	// in arr[1, r] to reach the office using the keys in keys[1, s]
	// with the last person using the key s
	vector<vector<int>> dp(n + 1, vector<int>(k + 1, LLONG_MAX));

	// hp[r][s] is the minimum time needed for all of the people in
	// arr[1, r] to reach the office using the keys in keys[1, s]
	vector<vector<int>> hp(n + 1, vector<int>(k + 1, LLONG_MAX));
	for (int s = 1; s <= k; s++)
		dp[1][s] = dist(1, s);

	hp[1][1] = dp[1][1];
	for (int s = 2; s <= k; s++)
		hp[1][s] = min(hp[1][s - 1], dp[1][s]);

	for (int r = 2; r <= n; r++) 
		for (int s = 1; s <= k; s++) 
			if (s >= r) {
				dp[r][s] = dist(r, s) + hp[r - 1][s - 1];
				hp[r][s] = min(hp[r][s - 1], dp[r][s]);
			}

	for (int r = 1; r <= n; r++)
		for (int s = 1; s <= k; s++)
			cout << "dp[" << r << "][" << s << "] = " << dp[r][s] << endl;
	
	cout << hp[n][k] << endl;
}
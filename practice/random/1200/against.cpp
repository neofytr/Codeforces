#include <bits/stdc++.h>
using namespace std;

#define int long long 

void solve() {
	int n;
	cin >> n;

	vector<int> arr(n + 1);
	for (int r = 1; r <= n; r++) cin >> arr[r];

	// dp[r] is the length of the longest neat subsequence ending at r for 1 <= r <= n
	// m[r] = max(dp[1], dp[2], ..., dp[r])
	vector<int> dp(n + 1, 0), m(n + 1, 0);
	if (arr[1] == 1) dp[1] = 1;
	else dp[1] = 0;
	m[0] = 0, m[1] = max(m[1], dp[1]);

	vector<vector<int>> idx(n + 1);
	idx[arr[1]].push_back(1);

	for (int r = 2; r <= n; r++) {
		idx[arr[r]].push_back(r);
		int sz = idx[arr[r]].size();
		if (sz >= arr[r])
			dp[r] = arr[r] + m[idx[arr[r]][sz - arr[r]] - 1];
		m[r] = max(m[r - 1], dp[r]);
	}

	int maxi = LLONG_MIN;
	for (int r = 1; r <= n; r++)
		maxi = max(dp[r], maxi);
	cout << maxi << endl;
}

int32_t main() {
	int t;
	cin >> t;

	while(t--) {
		solve();
	}
	return 0;
}
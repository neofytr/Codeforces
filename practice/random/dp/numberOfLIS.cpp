#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main() {
	int n;
	cin >> n;

	vector<int> arr(n + 1);
	for (int r = 1; r <= n; r++) cin >> arr[r];

	// dp[r] is the length of the longest increasing subsequence
	// ending at r for 1 <= r <= n;

	// cnt[r] is the number of subsequences ending at r with length 
	// dp[r]

	int maxi = LLONG_MIN;
	int res = 0;
	vector<int> dp(n + 1), cnt(n + 1);
	for (int r = 1; r <= n; r++) {
		dp[r] = 1;
		cnt[r] = 1;

		for (int i = 1; i < r; i++)
			if (arr[i] < arr[r]) {
				if (dp[i] + 1 > dp[r]) dp[r] = dp[i] + 1, cnt[r] = cnt[i];
				else if (dp[i] + 1 == dp[r]) cnt[r] += cnt[i];
			}
		
		if (dp[r] > maxi) res = cnt[r], maxi = dp[r];
		else if (dp[r] == maxi) res += cnt[r];
	}

	cout << res << endl;
	return 0;
}
#include <bits/stdc++.h>
using namespace std;

#define int long long 
#define MOD (998244353)

int32_t main() {
	int n, k;
	cin >> n >> k;

	int l, r;
	vector<pair<int, int>> segs;
	while(k--)
		cin >> l >> r, segs.push_back({l, r});

	// dp[r] is the number of ways to reach n, starting from 1
	vector<int> dp(n + 1, 0);
	vector<int> pref(n + 1, 0);
	dp[0] = 0;
	pref[0] = 0;
	dp[1] = 1;
	pref[1] = dp[1];

	for (int r = 2; r <= n; r++) {
		for (auto &[left, right] : segs) {
			int lft = max(r - right, 0LL);
			int rt = max(r - left, 0LL);

			if (lft > 0)
				dp[r] = (dp[r] + (pref[rt] - pref[lft - 1]) % MOD) % MOD;
			else 
				dp[r] = (dp[r] + pref[rt]) % MOD;
		}
		dp[r] = (dp[r] + MOD) % MOD;
		pref[r] = (pref[r - 1] + dp[r]) % MOD;
	}
	cout << dp[n] << endl;
	return 0;
}

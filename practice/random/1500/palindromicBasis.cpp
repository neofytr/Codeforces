#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MOD (int)(1e9 + 7)
#define MAX (int)(4 * 1e4)

vector<int> a(1);
int dp[MAX + 1][500 + 1];

void solve() {
	int n; cin >> n;
	cout << dp[n][a.size() - 1] << endl;
}

int32_t main() {
	for (int r = 1; r <= MAX; r++) {
		string num = to_string(r);
		string rev = num;
		reverse(rev.begin(), rev.end());
		if (num == rev) a.push_back(r);
	}

	// dp[i][j] is the number of ways to make the sum i using the first j numbers
	for (int j = 0; j <= a.size() - 1; j++) dp[0][j] = 1;
	for (int i = 1; i <= MAX; i++) {
		dp[i][0] = 0;
		for (int j = 1; j <= a.size() - 1; j++) {
			dp[i][j] = dp[i][j - 1];
			if (i >= a[j]) dp[i][j] = (dp[i][j] + dp[i - a[j]][j]) % MOD;
		}
	}

	int t; cin >> t;
	while (t--) solve();
	return 0;
}
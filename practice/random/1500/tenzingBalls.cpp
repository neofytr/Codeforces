#include <bits/stdc++.h>
using namespace std;

#define int long long
#define INF (int)(1e16)

void solve() {
	int n; cin >> n;
	vector<int> a(n + 1);
	for (int i = 1; i <= n; i++) cin >> a[i];

	vector<int> dp(n + 1, -INF), m(n + 1, -INF);
	dp[1] = 0, m[a[1]] = 0 - 1;
	for (int i = 2; i <= n; i++) 
		dp[i] = max(dp[i - 1], m[a[i]] + i + 1), m[a[i]] = max(m[a[i]], dp[i - 1] - i);

	cout << dp[n] << endl;	
}

int32_t main() {
	int t; cin >> t;
	while (t--) solve();
	return 0;
}
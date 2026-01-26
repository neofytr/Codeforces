#include <bits/stdc++.h>
using namespace std;

#define int long long
#define INF (int)(1e9)

void solve() {
	int n;
	cin >> n;

	int v;
	vector<bool> f(n + 1, false);
	for (int r = 1; r <= n; r++) {
		cin >> v;
		if (!f[v]) f[v] = true;
	}

	vector<int> dp(n + 1, INF);
	dp[1] = 0;
	for (int r = 2; r <= n; r++)
		for (int i = 1; i * i <= r; i++) 
			if (!(r % i)) {
				if (f[i]) dp[r] = min(dp[r], dp[r / i] + 1);
				if (f[r / i]) dp[r] = min(dp[r], dp[i] + 1);
			}

	cout << (f[1] ? 1 : -1) << " ";
	for (int r = 2; r <= n; r++)
		cout << (dp[r] >= INF ? -1 : dp[r]) << " ";
	cout << endl;
}

int32_t main() {
	int t;
	cin >> t;

	while (t--) {
		solve();
	}
	return 0;
}
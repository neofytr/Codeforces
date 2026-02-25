#include <bits/stdc++.h>
using namespace std;

#define int long long

int dp[1000][1000];

void solve() {
	int n, a, b; cin >> n >> a >> b;
	vector<int> x(n + 1);
	for (int r = 1; r <= n; r++) cin >> x[r];

	int c = 0;
	int cost = b * x[1];
	for (int r = 2; r <= n; r++) {
		int shift = a * (x[r - 1] - x[c]) + b * (x[r] - x[r - 1]);
		int dont = b * (x[r] - x[c]);
		if (shift <= dont) c = r - 1;
		cost += min(shift, dont);
	}

	cout << cost << endl;
}

int32_t main() {
	int t; cin >> t;
	while (t--) solve();
	return 0;
}
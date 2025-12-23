#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve() {
	int n, m;
	cin >> n >> m;

	vector<char> comm(n + 1);
	for (int r = 1; r <= n; r++) cin >> comm[r];

	vector<int> black(m + 1);
	for (int r = 1; r <= m; r++) cin >> black[r];
}

int32_t main() {
	int t;
	cin >> t;

	while (t--) {
		solve();
	}
	return 0;
}
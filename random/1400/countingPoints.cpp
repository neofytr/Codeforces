#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve() {
	int n, m; cin >> n >> m;
	vector<pair<int, int>> vec(n + 1);
	for (int i = 1; i <= n; i++) cin >> vec[i].first;
	for (int i = 1; i <= n; i++) cin >> vec[i].second;
}

int32_t main() {
	int t; cin >> t;
	while (t--) solve();
	return 0;

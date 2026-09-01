#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve() {
	int n, m; cin >> n >> m;
	vector<vector<char>> grid(n + 1, m + 1);
	for (int row = 1; row <= n; row++)
		for (int col = 1; col <= m; col++)
			cin >> grid[row][col];
}

int32_t main() {
	int t; cin >> t;
	while (t--) solve();
	return 0;
}
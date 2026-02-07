#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve() {
	int n, m; cin >> n >> m;
	string path; cin >> path;

	vector<vector<int>> grid(n + 1, vector<int>(m + 1));
	for (int r = 1; r <= n; r++)
		for (int c = 1; c <= m; c++)
			cin >> grid[r][c];

	vector<int> rowsums(n + 1, 0);
	vector<int> colsums(m + 1, 0);

	for (int r = 1; r <= n; r++) 
		for (int c = 1; c <= m; c++) {
			rowsums[r] += grid[r][c];
			colsums[c] += grid[r][c];
		}

}

int32_t main() {
	int t; cin >> t;
	while (t--) solve();
	return 0;
}
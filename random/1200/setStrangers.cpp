#include <bits/stdc++.h>
using namespace std;

#define int long long 

void solve() {
	int n, m;
	cin >> n >> m;

	vector<vector<int>> mat(n + 1, vector<int>(m + 1));
	for (int row = 1; row <= n; row++)
		for (int col = 1; col <= m; col++)
			cin >> mat[row][col];
	
	vector<int> colors(n * m + 1);	
}

int32_t main() {
	int t;
	cin >> t;

	while (t--) {
		solve();
	}
	return 0;
}
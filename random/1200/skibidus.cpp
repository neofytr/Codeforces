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

	vector<pair<int, int>> v;
	for (int row = 1; row <= n; row++) {
		int s = 0;
		for (int col = 1; col <= m; col++)
			s += (n * m - col + 1) * mat[row][col];
		v.push_back({s, row});
	}

	sort(v.rbegin(), v.rend());
	int coeff = n * m;
	int res = 0;
	for (auto &[s, row] : v) {
		for (int col = 1; col <= m; col++)
			res += mat[row][col] * (coeff--);
	}

	cout << res << endl;
}

int32_t main() {
	int t;
	cin >> t;

	while(t--) {
		solve();
	}
	return 0;
}
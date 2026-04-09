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

	int s1 = 0;
	for (int row = 1; row <= n; row++)
		for (int col = 1; col <= m; col++)
			s1 += mat[row][col];
	s1 *= (m * (n + 1) + 1);

	int s2 = 0;
	for (int col = 1; col <= m; col++) {
		int sum = 0;
		for (int row = 1; row <= n; row++)
			sum += mat[row][col];
		s2 += sum * col;
	}
	
	vector<int> sums (n + 1);
	for (int row = 1; row <= n; row++) {
		int sum = 0;
		for (int col = 1; col <= m; col++)
			sum += mat[row][col];
		sums[row] = sum;
	}

	sort(sums.rbegin(), sums.rend() - 1);
	int s3 = 0;
	for (int r = 1; r <= n; r++)
		s3 += sums[r] * r;

	cout << s1 - s2 - s3 * m << endl;
}

int32_t main() {
	int t;
	cin >> t;

	while(t--) {
		solve();
	}
	return 0;
}
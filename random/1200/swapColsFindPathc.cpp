#include <bits/stdc++.h>
using namespace std;

#define int long long 

void solve() {
	int n;
	cin >> n;

	vector<vector<int>> arr(2 + 1, vector<int>(n + 1));
	for (int row = 1; row <= 2; row++)
		for (int col = 1; col <= n; col++)
			cin >> arr[row][col];

	if (n == 1) {
		cout << arr[1][1] + arr[2][1] << endl;
		return;
	}

	if (n == 2) {
		cout << max(arr[1][1] + arr[1][2] + arr[2][2], arr[1][1] + arr[2][1] + arr[2][2]) << endl;
		return;
	}

	vector<int> up(n + 1, 0), down(n + 1, 0);
	for (int r = 1; r <= n; r++)
		up[r] += up[r - 1] + arr[1][r], down[r] += down[r - 1] + arr[2][r];


	vector<int> p(n + 1, 0);
	for (int r = 1; r <= n; r++)
		p[r] = arr[2][r] - arr[1][r];

	vector<int> pmax(n + 1, LLONG_MIN);
	for (int r = 1; r <= n; r++)
		pmax[r] = max(pmax[r - 1], p[r]);

	vector<int> smin(n + 2, LLONG_MAX);
	for (int r = n; r >= 1; r--)
		smin[r] = min(smin[r + 1], p[r]);

	int cost = LLONG_MIN;
	for (int r = 2; r <= n - 1; r++) {
		// 1 -> r
		//      r -> n 
		int c = up[r] + down[n] - down[r - 1];
		c = max(c, c + pmax[r - 1] - smin[r + 1]);
		cost = max(c, cost);
	}

	cout << up[n] + arr[2][n] << endl;
	cost = max(cost, max(up[1] + down[n], up[n] + arr[2][n]));
	cout << cost << endl;
}

int32_t main() {
	int t;
	cin >> t;

	while (t--) {
		solve();
	}
	return 0;
}
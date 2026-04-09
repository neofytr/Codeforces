#include <bits/stdc++.h>
using namespace std;

#define int long long 
#define MAX (1e5)

int32_t main() {
	int n, m;
	cin >> n >> m;

	vector<vector<int>> arr(n + 1, vector<int>(m + 1));
	for (int row = 1; row <= n; row++)
		for (int col = 1; col <= m; col++)
			cin >> arr[row][col];

	vector<vector<int>> x(MAX + 1), y(MAX + 1);
	for (int row = 1; row <= n; row++)
		for (int col = 1; col <= m; col++)
			x[arr[row][col]].push_back(col), y[arr[row][col]].push_back(row);

	int sum = 0;
	for (int color = 1; color <= MAX; color++) {
		vector<int> &vx = x[color];
		vector<int> &vy = y[color];

		sort(vx.begin(), vx.end());
		sort(vy.begin(), vy.end());

		vector<int> pvx(vx.size() + 1, 0), pvy(vy.size() + 1, 0);
		for (int r = 1; r <= vx.size(); r++)
			pvx[r] = pvx[r - 1] + vx[r - 1];
		for (int r = 1; r <= vy.size(); r++)
			pvy[r] = pvy[r - 1] + vy[r - 1];

		for (int r = 0; r < vx.size(); r++) 
			sum += ((pvx[vx.size()] - pvx[r]) - (vx.size() - r) * vx[r]);
		
		for (int r = 0; r < vy.size(); r++) 
			sum += ((pvy[vy.size()] - pvy[r]) - (vy.size() - r) * vy[r]);
	} 

	cout << sum << endl;
	return 0;
}

// 0 0 0 
// 0 0 0
// 0 0 0